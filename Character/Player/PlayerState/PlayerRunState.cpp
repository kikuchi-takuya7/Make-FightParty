#include "PlayerRunState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

void PlayerRunState::Update(Player* player)
{


	//MoveCharacter(player);

	HandleInput(player);
}

void PlayerRunState::HandleInput(Player* player)
{
	if (Input::IsKeyDown(DIK_F)) {
		player->ChangeState(PLAYER_ATTACK);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		player->ChangeState(PLAYER_JUMP);
	}
}

void PlayerRunState::Enter(Player* player)
{
}

void PlayerRunState::MoveCharacter(Player* player)
{

	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 playerPos = player->GetPosition();

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

	playerPos.x += fMove.x;
	playerPos.z += fMove.z;

	player->SetPosition(playerPos);

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

		player->SetRotateY(degree);

		player->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}
