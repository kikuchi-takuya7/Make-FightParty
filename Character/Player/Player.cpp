#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"
#include "../../Engine/VFX.h"
#include "../../AI/MetaAI.h"
#include "../../Scene/MainGameScene.h"
#include "../../Stage/CreateMode/StageSource/Bullet.h"
#include "../../UI/PlayerUI.h"
#include "../CharacterState/CharacterStateManager.h"

//�萔
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);

	const float PLAYER_SPEED = 0.2;

	//�ړ��ł���ő�̈ʒu
	const float MAX_MOVE_X = 29.0f;
	const float MAX_MOVE_Z = 29.0f;
	const float MIN_MOVE_X = ZERO;
	const float MIN_MOVE_Z = ZERO;
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	:Character(parent, "Player")
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

	//addcollider�����珟��ɊJ�������
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

}

//�X�V
void Player::ChildUpdate()
{

	//�ړ��L�[��������Ă���Ȃ�
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D) || Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
	{

		MoveCharacter();
		ChangeState(RUN);
	}
	else {
		ChangeState(IDLE);
	}

	if (Input::IsKeyDown(DIK_F)) {
		//ChangeState(ATTACK);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		//ChangeState(JUMP);
		ChangeState(ATTACK);
	}

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

}

// ���͂ɂ���Ĉړ�����֐�
void Player::MoveCharacter()
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = GetPosition();

	//���ǌ�Ő��K�����Ă邩�炱���̒l�͑傫���Ă��Ӗ��Ȃ�
	if (Input::IsKey(DIK_A) && characterPos.x >= MIN_MOVE_X)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && characterPos.x <= MAX_MOVE_X)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && characterPos.z <= MAX_MOVE_Z)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && characterPos.z >= MIN_MOVE_Z)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//���x����
	fMove.x *= PLAYER_SPEED;
	fMove.z *= PLAYER_SPEED;

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	SetPosition(characterPos);

	float length = Length(vMove);

	

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�������t�ɂ���
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		SetRotateY(degree);

		//SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));
	}
}

/// ���^AI�ɃX�e�[�^�X��`����֐�
void Player::TellStatus()
{

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->DecidedWinner();
}