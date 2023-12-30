#include "PlayerRunningState.h"
#include "../Engine/Input.h"

void PlayerRunningState::Update(Player* player)
{
	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

	//ここの引数でプレイヤー数を指定する
	fMove.x = Input::GetPadStickL(0).x;
	fMove.z = Input::GetPadStickL(0).y;

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	
	XMFLOAT3 pos;
	pos.x += fMove.x;
	pos.z += fMove.z;

	player->SetPosition(pos);

	float length = Length(vMove);

	//動いているなら角度を求めて回転する
	if (length != 0) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//内積から角度を求める
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//外積が-になる角度なら
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
