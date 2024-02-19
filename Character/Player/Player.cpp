#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"


//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Player::Player(GameObject* parent)
	:Character(parent, "Player"),pState_(new PlayerStateManager)
{
}

//デストラクタ
Player::~Player()
{
	SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);
}

//初期化
void Player::ChildInitialize()
{

	//開始地点に移動する
	SetPosition(startPos_);

	//addcolliderしたら勝手に開放されるからね
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);
	
}

//更新
void Player::ChildUpdate()
{

    pState_->Update(this);

}

//描画
void Player::ChildDraw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//開放
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);

}

//何か当たった時の処理
void Player::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//ノックバック中は当たり判定を無くす
	if (pState_->playerKnockBackState_ == pState_->playerState_)
		return;

	//攻撃に当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);
		
		//後で敵の方向に向きなおす
		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(PLAYER_KNOCKBACK, this);
	}

	//球に当たった時の処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

	}

	

}

void Player::ResetStatus()
{

	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//開始地点に移動する
	SetPosition(startPos_);
	
	//addcolliderしたら勝手に開放されるからね
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);
	
	status_.hp = PLAYER_HP;
	status_.dead = false;

	TellStatus();

	ChangeState(PLAYER_IDLE);

}

void Player::TellStatus()
{
	
	//どっちも違う気がする。どうやってプレイヤーからMetaAIに死んだことを伝える？名前検索しちゃっていい？

	//((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	//((MainGameScene*)GetParent())->CallStatus(GetObjectID(), GetStatus());

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ToCreateMode();
}


void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
