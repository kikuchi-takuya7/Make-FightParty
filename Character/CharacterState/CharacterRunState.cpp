#include "CharacterRunState.h"
#include "../../../Engine/Input.h"
#include "../Character.h"

CharacterRunState::CharacterRunState(Character* character, int model):CharacterState(character, model)
{
}

void CharacterRunState::Update()
{


	//Movecharacter(character);

	HandleInput();
}

void CharacterRunState::HandleInput()
{
	if (Input::IsKeyDown(DIK_F)) {
		pCharacter_->ChangeState(ATTACK);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		pCharacter_->ChangeState(JUMP);
	}
}

void CharacterRunState::Enter()
{
}

void CharacterRunState::Leave()
{
}

void CharacterRunState::MoveCharacter()
{

	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = pCharacter_->GetPosition();

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

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	pCharacter_->SetPosition(characterPos);

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

		pCharacter_->SetRotateY(degree);

		pCharacter_->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}
