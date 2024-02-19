#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"


//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:Character(parent, "Player"),pState_(new PlayerStateManager)
{
}

//�f�X�g���N�^
Player::~Player()
{
	SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);
}

//������
void Player::ChildInitialize()
{

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	//addcollider�����珟��ɊJ������邩���
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);
	
}

//�X�V
void Player::ChildUpdate()
{

    pState_->Update(this);

}

//�`��
void Player::ChildDraw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//�J��
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);

}

//���������������̏���
void Player::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//�m�b�N�o�b�N���͓����蔻��𖳂���
	if (pState_->playerKnockBackState_ == pState_->playerState_)
		return;

	//�U���ɓ��������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);
		
		//��œG�̕����Ɍ����Ȃ���
		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(PLAYER_KNOCKBACK, this);
	}

	//���ɓ����������̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

	}

	

}

void Player::ResetStatus()
{

	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);
	
	//addcollider�����珟��ɊJ������邩���
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);
	
	status_.hp = PLAYER_HP;
	status_.dead = false;

	TellStatus();

	ChangeState(PLAYER_IDLE);

}

void Player::TellStatus()
{
	
	//�ǂ������Ⴄ�C������B�ǂ�����ăv���C���[����MetaAI�Ɏ��񂾂��Ƃ�`����H���O������������Ă����H

	//((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	//((MainGameScene*)GetParent())->CallStatus(GetObjectID(), GetStatus());

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ToCreateMode();
}


void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
