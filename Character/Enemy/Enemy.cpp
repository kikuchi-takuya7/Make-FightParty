#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"


//�萔
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
}

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"),pState_(new EnemyStateManager), pCharacterAI_(nullptr)

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
	SAFE_RELEASE(pCharacterAI_);
	SAFE_DELETE(pState_);
}

//���������������̏���
void Enemy::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//�m�b�N�o�b�N���͓����蔻��𖳂���
	if (pState_->enemyKnockBackState_ == pState_->enemyState_)
		return;

	//���������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);

		//��œG�̕����Ɍ����Ȃ���
		SetTargetRotate(pTarget->GetRotate());

		//�m�b�N�o�b�N������
		pState_->ChangeState(ENEMY_KNOCKBACK, this, pCharacterAI_);

		//���̊m���ő_���������Ă�������ɕς���
		if (rand() % 2 == ZERO) {
			pCharacterAI_->SetTargetID(pTarget->GetObjectID());
		}

	}

	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(ENEMY_KNOCKBACK, this, pCharacterAI_);

	}

	//�U���𓖂Ă����̏���
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
	}

}

void Enemy::ResetStatus()
{
	//�R���C�_�[����U�����B�����Ȃ��Ə����Ă�v���C���[�̃R���C�_�[���d�Ȃ�
	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	//�̂̓����蔻��𕜊�������
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
