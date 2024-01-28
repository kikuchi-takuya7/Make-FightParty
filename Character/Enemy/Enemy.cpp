#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/CharacterAI.h"

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
	:Character(parent, "Enemy"), hModel_(-1),pState_(new EnemyStateManager), characterAI_(nullptr)

{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::ChildInitialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, XMFLOAT3(0, 180, 0));
	//AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

	status_ = { ENEMY_HP,ENEMY_ATTACK_POWER, 0, false};

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	//characterAI_->Initialize();

	

}

//�X�V
void Enemy::ChildUpdate()
{

	//MoveCharacter();

	pState_->Update(this, characterAI_);

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
	SAFE_DELETE(characterAI_);
	SAFE_DELETE(pState_);
}

//���������������̏���
void Enemy::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//�m�b�N�o�b�N���͓����蔻��𖳂���
	if (isKnockBack_)
		return;

	//���������Ƃ��̏���
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

	//�U���𓖂Ă����̏���
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
