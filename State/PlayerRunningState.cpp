#include "PlayerRunningState.h"
#include "../Engine/Input.h"

void PlayerRunningState::Update(Player* player)
{
	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

	//�����̈����Ńv���C���[�����w�肷��
	fMove.x = Input::GetPadStickL(0).x;
	fMove.z = Input::GetPadStickL(0).y;

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	
	XMFLOAT3 pos;
	pos.x += fMove.x;
	pos.z += fMove.z;

	player->SetPosition(pos);

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

void PlayerRunningState::HandleInput(Player* player)
{
}

void PlayerRunningState::Enter(Player* player)
{
}
