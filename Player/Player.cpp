#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),hModel_(-1)
{
	pState_ = new PlayerStateManager;
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("PlayerFbx/player.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
	
	MovePlayer();

    pState_->Update(this);
    

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
	SAFE_DELETE(pState_);
}

void Player::MovePlayer()
{

	XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

	////ここの引数でプレイヤー数を指定する
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

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;

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
