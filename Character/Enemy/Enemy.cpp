#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//�萔
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"), hModel_(-1)
{
	pState_ = new EnemyStateManager;
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), XMFLOAT3(ZERO, ZERO, ZERO));
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

}

//�X�V
void Enemy::ChildUpdate()
{



	pState_->Update(this);

}

//�`��
void Enemy::Draw()
{

}

//�J��
void Enemy::Release()
{
	SAFE_DELETE(pState_);

}

//���������������̏���
void Enemy::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetTypee)
{


}

void Enemy::Move()
{
}
