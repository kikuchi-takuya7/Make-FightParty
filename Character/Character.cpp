#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Engine/Audio.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"
#include "../Engine/VFX.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 25;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(0.9, 2, 0.9);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1.5, 0.5, 3);

	const int PLAYER_MAX_NUM = 4;
}

//コンストラクタ
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(nullptr), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), stopDraw_(false), hSoundEffect_{-1,-1}
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
	std::string fileName = "PlayerFbx/player" + std::to_string(GetObjectID()) + ".fbx";
	hModel_ = Model::Load(fileName);
	assert(hModel_ >= ZERO);

	pState_ = new CharacterStateManager(this, hModel_);

	pPlayerUI_->SetMaxHp(status_.hp, status_.hp);


	//音声データのロード
	std::string str[SE_NUM] = { "Damage","Dead", };

	for (int i = ZERO; i < SE_NUM; i++) {

		std::string dir = "Audio/SE/";
		std::string extention = ".wav";

		std::string fileName = dir + str[i] + extention;

		hSoundEffect_[i] = Audio::Load(fileName,false,PLAYER_MAX_NUM);
		assert(hSoundEffect_[i] >= ZERO);

		Audio::Stop(hSoundEffect_[i]);
	}
	
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
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(KNOCKBACK) && pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK) && status_.dead == false) {
		ChildUpdate();
	}


}

//描画
void Character::Draw()
{

	if (IsVisibled())
		return;

	ChildDraw();
}

//開放
void Character::Release()
{
	ChildRelease();

	//試合中以外、Collisionは消しているのでここでDELETEする。

	//コリジョンをcolliderListから外してるときは自動開放されないので、特定の条件の時のみ自分で開放する
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK)) {

		SAFE_DELETE(pAttackCollision_);
	}
	else if (pState_->characterState_ == pState_->pCharacterStateList_.at(DIE)) {
		SAFE_DELETE(pAttackCollision_);
		SAFE_DELETE(pBodyCollision_);
	}

	SAFE_DELETE(pState_);

	
	
}

// 別のcolliderに衝突したときに呼ばれる関数
void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//死んでいたら判定しない様に
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

	//攻撃に当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		//敵の方向に向きなおす
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

		//攻撃を食らったのがEnemyの場合、一定確率で狙いを攻撃してきた相手に変える
		ChangeTarget(pTarget);

		//その攻撃でやられたら、相手のキルポイントを増やす
		if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
			Status status = ((Character*)pTarget)->GetStatus();
			status.killPoint++;
			((Character*)pTarget)->SetStatus(status);
			((Character*)pTarget)->TellStatus();
			DieEffect();
		}
		else {
			HitEffect();
		}
	}
}

// 攻撃に当たった時にHPを減らす関数
// 引数：食らったダメージ量
// 戻り値：そのダメージで死亡したらtrue
bool Character::HitDamage(int damage)
{
	status_.hp -= damage;
	pPlayerUI_->SetNowHp(status_.hp);

	//HPが0になったら
	if (status_.hp <= 0) {
		status_.dead = true;
		Audio::Play(hSoundEffect_[DEAD]);
		return status_.dead;
	}

	Audio::Play(hSoundEffect_[HIT]);
	return status_.dead;
}

// ステータスをゲーム開始時にリセットする関数（winPointはそのまま）
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

//描画を止める
void Character::StopDraw()
{
	Visible();
	pPlayerUI_->StopDraw();
}

//描画を許可する
void Character::StartDraw()
{
	Invisible();
	pPlayerUI_->StartDraw();
}

//UIの描画を止める
void Character::StopDrawUI()
{
	pPlayerUI_->StopDraw();
}

//ステータスのdeadをtrueにする（未使用）
void Character::Dead()
{
	status_.dead = true;
}


// 現在のstateを変える
// 引数：次のstate
void Character::ChangeState(CharacterStateList nextState)
{
	pState_->ChangeState(nextState);
}

//プレイヤーUIの場所をセットする
void Character::SetUIPos(XMFLOAT3 pos)
{
	pPlayerUI_->SetPlayerUIPos(pos);
}

//キャラクターの名前をセットする
void Character::SetCharacterName(std::string name)
{
	status_.playerName = name;
	pPlayerUI_->SetPlayerName(name);
}

//攻撃を食らった時のエフェクト
void Character::HitEffect()
{

	//火の粉
	EmitterData data;
	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.delay = 0;
	data.speedRnd = 0.0;
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.color = XMFLOAT4(1, 1, 0, 1);
	data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
	data.number = 40;
	data.positionRnd = XMFLOAT3(0.5, 0.5, 0.5);
	data.direction = targetRot_;
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.size = XMFLOAT2(0.3, 0.3);
	data.scale = XMFLOAT2(0.9, 0.9);
	data.lifeTime = 15;
	data.speed = 0.2f;
	VFX::Start(data);
}

//死んだ時にでるエフェクト
void Character::DieEffect()
{
	EmitterData data;

	//炎（爆発本体）
	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 30;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.1f;
	data.speedRnd = 0.8;
	data.size = XMFLOAT2(1.2, 1.2);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.05, 1.05);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	VFX::Start(data);

	//火の粉
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedRnd = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.1, 0.1);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(0.99, 0.99);
	data.color = XMFLOAT4(1, 1, 0.1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	VFX::Start(data);

}


