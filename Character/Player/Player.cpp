#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

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
}

//初期化
void Player::ChildInitialize()
{


	//addcolliderしたら勝手に開放されるからね
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);
	
	
	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER, 0, false };

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
		
		pState_->SetEnemyRot(rotate);

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

		
		

	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		

	}

}

void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
