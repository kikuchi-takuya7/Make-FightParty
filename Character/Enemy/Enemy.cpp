#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"
#include "../CharacterState/CharacterStateManager.h"

//定数
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"), pCharacterAI_(nullptr)

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
	pCharacterAI_->IsAttack();

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
	//SAFE_RELEASE(pCharacterAI_);
}

//何か当たった時の処理
void Enemy::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//攻撃に当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{

		//後で敵の方向に向きなおす
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

		//その攻撃でやられたら、相手のキルポイントを増やす
		if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
			Status status = ((Character*)pTarget)->GetStatus();
			status.killPoint++;
			((Character*)pTarget)->SetStatus(status);
			((Character*)pTarget)->TellStatus();
		}

		

		//一定の確率で狙いを殴ってきた相手に変える
		if (rand() % 2 == ZERO) {
			pCharacterAI_->SetTargetID(pTarget->GetObjectID());
		}

	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
	}

}

void Enemy::MoveCharacter()
{
	pCharacterAI_->MoveEnemy();
}

void Enemy::TellStatus()
{
	pCharacterAI_->TellStatus();
}
