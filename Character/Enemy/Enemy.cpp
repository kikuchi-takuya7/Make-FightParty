#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"
#include "../CharacterState/CharacterStateManager.h"

//�萔
namespace {

	//�����Ă�������ɑ_����ς���m��(%)
	const int COUNTER_PROBABILITY = 50;
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"), pCharacterAI_(nullptr)

{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::ChildInitialize()
{
	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);
}

//�X�V
void Enemy::ChildUpdate()
{

	pCharacterAI_->MoveEnemy(status_.moveSpeed);
	pCharacterAI_->IsAttack();

}

//�`��
void Enemy::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

#ifdef _DEBUG
	CollisionDraw();
#endif
}

//�J��
void Enemy::ChildRelease()
{
	//SAFE_RELEASE(pCharacterAI_);
}

void Enemy::ChangeTarget(GameObject* pTarget)
{
	//���̊m���ő_���������Ă�������ɕς���
	if (rand() % 100 < COUNTER_PROBABILITY) {
		TargetInfo target;
		target.ID = pTarget->GetObjectID();
		target.mode = COUNTER;
		pCharacterAI_->SetTarget(target);

	}
}

// CharavterAI�Ɉړ�����ꏊ�𕷂��Ĉړ�����֐�
void Enemy::MoveCharacter()
{
	pCharacterAI_->MoveEnemy(status_.moveSpeed);
}

// ���^AI�Ɍ��݂̃X�e�[�^�X��`����֐�
void Enemy::TellStatus()
{
	pCharacterAI_->TellStatus();
}
