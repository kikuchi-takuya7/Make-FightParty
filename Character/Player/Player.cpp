#include "Player.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Player::Player(GameObject* parent)
	:Character(parent, "Player")
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
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

	status_ = { PLAYER_HP,PLAYER_ATTACK_POWER,false };

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 10.0f;
	transform_.position_.z = 15.0f;

}

//更新
void Player::ChildUpdate()
{

	/*if (Input::IsKey(DIK_L)) {
		attackCollisionCenter_.z += 1;
	}*/

	MovePlayer();

    pState_->Update(this);

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//開放
void Player::Release()
{
	SAFE_DELETE(pState_);

}

//何か当たった時の処理
void Player::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{

	//当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		//KillMe();
	}

}

void Player::MovePlayer()
{

	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	

	//結局後で正規化してるからここの値は大きくても意味なし
	if (Input::IsKey(DIK_A) && transform_.position_.x >= 0)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && transform_.position_.x <= 29)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && transform_.position_.z <= 29)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && transform_.position_.z >= 0)
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

		pAttackCollision_->SetRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}
