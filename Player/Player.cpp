#include "Player.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;

}

//コンストラクタ
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), attackCollisionCenter_(ZERO, 1, 1), attackCollisionSize_(1, 0.5, 2)
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


	//addcolliderしたら勝手に開放されるからね
	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1));
	AddCollider(pBodyCollision_);

	pAttackCollision_ = new BoxCollider(attackCollisionCenter_, attackCollisionSize_);
	AddCollider(pAttackCollision_);

	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER,false };

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

	CollisionDraw();
}

//開放
void Player::Release()
{
	SAFE_DELETE(pState_);

}

//何か当たった時の処理
void Player::OnCollision(GameObject* pTarget)
{

	//当たったときの処理
	if (pTarget->GetObjectName() == "PlayerAttack")
	{
		KillMe();
	}

}

void Player::MovePlayer()
{

	XMFLOAT3 fMove = XMFLOAT3(ZERO, ZERO, ZERO);

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

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

	transform_.position_.x += fMove.x;
	transform_.position_.z += fMove.z;

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

		transform_.rotate_.y = degree;

		//攻撃時の当たり判定を回転させる
		XMVECTOR collisionVec = XMLoadFloat3(&attackCollisionCenter_);
		
		XMMATRIX rotY = XMMatrixRotationY(degree);

		XMVector3TransformCoord(collisionVec, rotY);

		attackCollisionCenter_ = VectorToFloat3(collisionVec);
		
		pAttackCollision_->SetCenter(attackCollisionCenter_);

	}

}
