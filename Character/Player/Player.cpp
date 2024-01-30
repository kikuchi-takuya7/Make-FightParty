#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

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
}

//������
void Player::ChildInitialize()
{


	//addcollider�����珟��ɊJ������邩���
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);
	
	
	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER, 0, false };

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
		
		pState_->SetEnemyRot(rotate);

		pState_->ChangeState(PLAYER_KNOCKBACK, this);

		
		

	}

	//�U���𓖂Ă����̏���
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		

	}

}

void Player::ChangeState(PlayerStatePattern nextState)
{
	pState_->ChangeState(nextState, this);
}
