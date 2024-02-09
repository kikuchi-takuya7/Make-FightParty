#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 100;
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:Character(parent, "Player"),pState_(new PlayerStateManager)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::ChildInitialize()
{

	//�J�n�n�_�Ɉړ�����
	SetPosition(startPos_);

	//addcollider�����珟��ɊJ������邩���
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	
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
void Player::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//�m�b�N�o�b�N���͓����蔻��𖳂���
	if (pState_->playerKnockBackState_ == pState_->playerState_)
		return;

	//���������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		HitDamage(((Character*)pTarget)->GetStatus().attackPower);

		XMFLOAT3 rotate = pTarget->GetRotate();
		
		SetTargetRotate(rotate);

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

		
		

	}

	//�U���𓖂Ă����̏���
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		

	}

}

void Player::ResetStatus()
{

	//�R���C�_�[����U�����B�����Ȃ��Ə����Ă�v���C���[�̃R���C�_�[���d�Ȃ�
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
}


void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
