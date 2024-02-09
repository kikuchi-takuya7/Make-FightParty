#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"

//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 100;
}

//コンストラクタ
Player::Player(GameObject* parent)
	:Character(parent, "Player"),pState_(new PlayerStateManager)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::ChildInitialize()
{

	//開始地点に移動する
	SetPosition(startPos_);

	//addcolliderしたら勝手に開放されるからね
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	
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
void Player::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//ノックバック中は当たり判定を無くす
	if (pState_->playerKnockBackState_ == pState_->playerState_)
		return;

	//当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);

		XMFLOAT3 rotate = pTarget->GetRotate();
		
		SetTargetRotate(rotate);

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

		
		

	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		

	}

}

void Player::ResetStatus()
{

	//コライダーを一旦消す。消さないと勝ってるプレイヤーのコライダーが重なる
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
}


void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
