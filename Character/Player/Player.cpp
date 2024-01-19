#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:Character(parent, "Player")
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


	//addcollider�����珟��ɊJ������邩���
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER,false };

	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Player::ChildUpdate()
{

	/*if (Input::IsKey(DIK_L)) {
		attackCollisionCenter_.z += 1;
	}*/

	MovePlayer();

    pState_->Update(this);

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//�J��
void Player::Release()
{
	SAFE_DELETE(pState_);

}

//���������������̏���
void Player::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//���������Ƃ��̏���
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		KillMe();
	}

}

void Player::MovePlayer()
{

	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	//���ǌ�Ő��K�����Ă邩�炱���̒l�͑傫���Ă��Ӗ��Ȃ�
	if (Input::IsKey(DIK_A))
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D))
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W))
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S))
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//���x����
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;

	float length = Length(vMove);

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		transform_.rotate_.y = degree;

		pAttackCollision_->SetRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}