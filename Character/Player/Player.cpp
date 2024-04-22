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

//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);

	const float PLAYER_SPEED = 0.2;

	//移動できる最大の位置
	const float MAX_MOVE_X = 29.0f;
	const float MAX_MOVE_Z = 29.0f;
	const float MIN_MOVE_X = ZERO;
	const float MIN_MOVE_Z = ZERO;
}

//コンストラクタ
Player::Player(GameObject* parent)
	:Character(parent, "Player")
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::ChildInitialize()
{

	//開始地点に移動する
	SetPosition(startPos_);

	//addcolliderしたら勝手に開放される
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

}

//更新
void Player::ChildUpdate()
{

	//移動キーが押されているなら
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

//描画
void Player::ChildDraw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


#ifdef _DEBUG
	CollisionDraw();
#endif

	
}

//開放
void Player::ChildRelease()
{

}

// 入力によって移動する関数
void Player::MoveCharacter()
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = GetPosition();

	//結局後で正規化してるからここの値は大きくても意味なし
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

	//斜めの移動でも早くならないように
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//速度調整
	fMove.x *= PLAYER_SPEED;
	fMove.z *= PLAYER_SPEED;

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	SetPosition(characterPos);

	float length = Length(vMove);

	

	//動いているなら角度を求めて回転する
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//内積から角度を求める
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//外積が-になる角度なら向きを逆にする
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		SetRotateY(degree);

		//SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));
	}
}

/// メタAIにステータスを伝える関数
void Player::TellStatus()
{

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->DecidedWinner();
}