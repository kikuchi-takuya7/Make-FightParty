#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;

}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
	pState_ = new PlayerStateManager;
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("PlayerFbx/player.fbx");
    assert(hModel_ >= 0);

	pBodyCollision_ = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 2, 1));
	AddCollider(pBodyCollision_);

	pAttackCollision_ = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 2, 1));

	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER,false };

}

//�X�V
void Player::Update()
{
	
	MovePlayer();

    pState_->Update(this);
    

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

	CollisionDraw();
}

//�J��
void Player::Release()
{
	SAFE_DELETE(pState_);
	SAFE_DELETE(pBodyCollision_);
	SAFE_DELETE(pAttackCollision_);
}

//���������������̏���
void Player::OnCollision(GameObject* pTarget)
{

	//���������Ƃ��̏���
	if (pTarget->GetObjectName() == "PlayerAttack")
	{
		KillMe();
	}

}

void Player::MovePlayer()
{

	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	if (Input::IsKey(DIK_A))
	{
		fMove.x = -0.1f;
	}
	if (Input::IsKey(DIK_D))
	{
		fMove.x = 0.1f;
	}
	if (Input::IsKey(DIK_W))
	{
		fMove.z = 0.1f;
	}
	if (Input::IsKey(DIK_S))
	{
		fMove.z = -0.1f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;

	float length = Length(vMove);

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != 0) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < 0) {

			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

}
