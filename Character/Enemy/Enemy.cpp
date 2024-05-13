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

	//殴ってきた相手に狙いを変える確率(%)
	const int COUNTER_PROBABILITY = 50;
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

	pCharacterAI_->MoveEnemy(status_.moveSpeed);
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

void Enemy::ChangeTarget(GameObject* pTarget)
{
	//一定の確率で狙いを殴ってきた相手に変える
	if (rand() % 100 < COUNTER_PROBABILITY) {
		TargetInfo target;
		target.ID = pTarget->GetObjectID();
		target.mode = COUNTER;
		pCharacterAI_->SetTarget(target);

	}
}

// CharavterAIに移動する場所を聞いて移動する関数
void Enemy::MoveCharacter()
{
	pCharacterAI_->MoveEnemy(status_.moveSpeed);
}

// メタAIに現在のステータスを伝える関数
void Enemy::TellStatus()
{
	pCharacterAI_->TellStatus();
}
