#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"


//定数
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"),pState_(new EnemyStateManager), pCharacterAI_(nullptr)

{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::ChildInitialize()
{

	//開始地点に移動する
	SetPosition(startPos_);

	//pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	//pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, XMFLOAT3(0, 180, 0));
	//AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

}

//更新
void Enemy::ChildUpdate()
{


	pCharacterAI_->MoveEnemy();

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
	SAFE_RELEASE(pCharacterAI_);
	SAFE_DELETE(pState_);
}

//何か当たった時の処理
void Enemy::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//ノックバック中は当たり判定を無くす
	if (pState_->enemyKnockBackState_ == pState_->enemyState_)
		return;

	//当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);

		//後で敵の方向に向きなおす
		SetTargetRotate(pTarget->GetRotate());

		//ノックバックさせる
		pState_->ChangeState(ENEMY_KNOCKBACK, this, pCharacterAI_);

		//一定の確率で狙いを殴ってきた相手に変える
		if (rand() % 2 == ZERO) {
			pCharacterAI_->SetTargetID(pTarget->GetObjectID());
		}

	}

	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(ENEMY_KNOCKBACK, this, pCharacterAI_);

	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
	}

}

void Enemy::ResetStatus()
{
	//コライダーを一旦消す。消さないと勝ってるプレイヤーのコライダーが重なる
	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//開始地点に移動する
	SetPosition(startPos_);

	//体の当たり判定を復活させる
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.hp = ENEMY_HP;
	status_.dead = false;

	pPlayerUI_->SetMaxHp(status_.hp, ENEMY_HP);

	pCharacterAI_->TellStatus();

	ChangeState(ENEMY_IDLE);
}

void Enemy::MoveCharacter()
{
	pCharacterAI_->MoveEnemy();
}

void Enemy::ChangeState(EnemyStatePattern nextState)
{
	pState_->ChangeState(nextState, this, pCharacterAI_);
}
