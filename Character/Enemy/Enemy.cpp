#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;

}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), XMFLOAT3(ZERO, ZERO, ZERO));
	AddCollider(pBodyCollision_);

}

//�X�V
void Enemy::Update()
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
void Enemy::OnCollision(GameObject* pTarget)
{


}

void Enemy::Move()
{
}
