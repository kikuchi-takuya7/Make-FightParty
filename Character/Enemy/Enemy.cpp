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
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
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

	//pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	//pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, XMFLOAT3(0, 180, 0));
	//AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

}

//�X�V
void Enemy::ChildUpdate()
{

	pCharacterAI_->MoveEnemy();
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

//���������������̏���
void Enemy::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//�U���ɓ��������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{

		//��œG�̕����Ɍ����Ȃ���
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

		//���̍U���ł��ꂽ��A����̃L���|�C���g�𑝂₷
		if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
			Status status = ((Character*)pTarget)->GetStatus();
			status.killPoint++;
			((Character*)pTarget)->SetStatus(status);
			((Character*)pTarget)->TellStatus();
		}

		

		//���̊m���ő_���������Ă�������ɕς���
		if (rand() % 2 == ZERO) {
			pCharacterAI_->SetTargetID(pTarget->GetObjectID());
		}

	}

	//�U���𓖂Ă����̏���
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
