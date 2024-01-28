#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"

//定数
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"), hModel_(-1),pState_(new EnemyStateManager), characterAI_(nullptr)

{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::ChildInitialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, XMFLOAT3(0, 180, 0));
	//AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

	status_ = { ENEMY_HP,ENEMY_ATTACK_POWER, 0, false};

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	//characterAI_->Initialize();

	

}

//更新
void Enemy::ChildUpdate()
{

	//MoveCharacter();

	pState_->Update(this, characterAI_);

}

//描画
void Enemy::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

#ifdef _DEBUG
	CollisionDraw();
#endif
}

//開放
void Enemy::ChildRelease()
{
	SAFE_DELETE(characterAI_);
	SAFE_DELETE(pState_);
}

//何か当たった時の処理
void Enemy::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//ノックバック中は当たり判定を無くす
	if (isKnockBack_)
		return;

	//当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);

		XMFLOAT3 rotate = pTarget->GetRotate();

		pState_->SetPlayerRot(rotate);

		pState_->ChangeState(ENEMY_KNOCKBACK, this);


		if (status_.hp <= 0) {
			pState_->ChangeState(ENEMY_DIE, this);
		}

	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{


	}

}

void Enemy::MoveCharacter()
{
	characterAI_->MoveEnemy();
}

void Enemy::ChangeState(EnemyStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
