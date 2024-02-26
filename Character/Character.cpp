#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(new CharacterStateManager(this)), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), stopDraw_(false)
	,pPlayerUI_(Instantiate<PlayerUI>(this))
{
}

//デストラクタ
Character::~Character()
{
}

//初期化
void Character::Initialize()
{
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	//status_ = { CHARACTER_HP,CHARACTER_ATTACK_POWER, false ,ZERO,ZERO,ZERO,"NONE" };
	pPlayerUI_->SetMaxHp(status_.hp, status_.hp);

	ChildInitialize();
}

//更新
void Character::Update()
{
	//動いてほしくないとき
	if (IsEntered() == false) {
		return;
	}

	//今いる位置をprevPosに置いておく
	prevPos_ = transform_.position_;

	

	pState_->Update();

	

	//ノックバック中は移動の処理をしない
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(KNOCKBACK) && pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK)) {
		ChildUpdate();
	}


}

//描画
void Character::Draw()
{

	if (stopDraw_ == true)
		return;

	ChildDraw();
}

//開放
void Character::Release()
{
	ChildRelease();

	SAFE_DELETE(pState_);

	//試合中以外、Collisionは消しているのでここでDELETEする。尚実行中に消すとエラーになる
	//ていうかnullptr入れてるはずなのになぜ例外が出るのか
	
	//最悪今のstateの状態によってdeleteするかしないかを決める。
	//pAttackCollision_ = nullptr;

	/*SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);*/
	
}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	
	if (status_.dead) {
		return;
	}

	//壁にぶつかったら前にいた座標に戻す
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BROCK) {
		SetPosition(prevPos_);
	}

	//ノックバック中は当たり判定を無くす
	if (pState_->pCharacterStateList_.at(KNOCKBACK) == pState_->characterState_)
		return;

	//球に当たった時の処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(KNOCKBACK);

	}

	//トゲに当たった時の処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_OBSTRYCTION) {
		HitDamage(static_cast<Needle*>(pTarget)->GetNeedlePower());
	}

	ChildOnCollision(pTarget, myType, targetType);
}

bool Character::HitDamage(int damage)
{
	status_.hp -= damage;

	pPlayerUI_->SetNowHp(status_.hp);

	//HPが0になったら
	if (status_.hp <= 0) {
		status_.dead = true;
	}

	return status_.dead;
}

void Character::StopDraw()
{
	stopDraw_ = true;
	pPlayerUI_->StopDraw();
}

void Character::StartDraw()
{
	stopDraw_ = false;
	pPlayerUI_->StartDraw();
}

void Character::StopDrawUI()
{
	pPlayerUI_->StopDraw();
}

void Character::Dead()
{
	status_.dead = true;
}



void Character::MoveCharacter()
{
}

void Character::ResetStatus()
{
	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//開始地点に移動する
	SetPosition(startPos_);

	//addcolliderしたら勝手に開放されるからね
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.hp = CHARACTER_HP;
	status_.dead = false;
	status_.killPoint = ZERO;
	status_.trapKillPoint = ZERO;

	pPlayerUI_->SetMaxHp(status_.hp, CHARACTER_HP);

	TellStatus();

	ChangeState(IDLE);
}

void Character::ChangeState(CharacterStateList nextState)
{
	pState_->ChangeState(nextState);
}

void Character::SetUIPos(XMFLOAT3 pos)
{
	pPlayerUI_->SetPlayerUIPos(pos);
}

void Character::SetCharacterName(std::string name)
{
	status_.playerName = name;
	pPlayerUI_->SetPlayerName(name);
}


