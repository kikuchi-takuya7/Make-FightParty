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

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 playerPos = player->GetPosition();

	//結局後で正規化してるからここの値は大きくても意味なし
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

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//速度調整
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	playerPos.x += fMove.x;
	playerPos.z += fMove.z;

	player->SetPosition(playerPos);

	float length = Length(vMove);

	//動いているなら角度を求めて回転する
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//内積から角度を求める
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//外積が-になる角度なら
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		player->SetRotateY(degree);

		player->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}
