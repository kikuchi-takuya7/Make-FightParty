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
	const int PLAYER_ATTACK_POWER = 100;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);


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

	//addcolliderしたら勝手に開放されるからね
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.attackPower = PLAYER_ATTACK_POWER;

	//モデルデータのロード
	//hModel_ = Model::Load("PlayerFbx/playerTest.fbx");
	//assert(hModel_ >= 0);

	

	
	
}

//更新
void Player::ChildUpdate()
{

	

	//移動キーが押されているなら
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D) || Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
	{

		//Runstateで移動中なら速度早くして、他のstateなら移動速度遅くするとかが良い気がする
		MoveCharacter();
		ChangeState(RUN);
	}
	else {
		ChangeState(IDLE);
	}

	if (Input::IsKeyDown(DIK_F)) {
		ChangeState(ATTACK);
	}

	if (Input::IsKeyDown(DIK_SPACE)) {
		//ChangeState(JUMP);
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

//何か当たった時の処理
void Player::ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//攻撃に当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{

		////敵の方向に向きなおす
		//SetTargetRotate(pTarget->GetRotate());
		//pState_->ChangeState(KNOCKBACK);

		////その攻撃でやられたら、相手のキルポイントを増やす
		//if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
		//	Status status = ((Character*)pTarget)->GetStatus();
		//	status.killPoint++;
		//	((Character*)pTarget)->SetStatus(status);
		//	((Character*)pTarget)->TellStatus();
		//}

		
	}

}

void Player::MoveCharacter()
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = GetPosition();

	//結局後で正規化してるからここの値は大きくても意味なし
	if (Input::IsKey(DIK_A) && characterPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && characterPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && characterPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && characterPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//速度調整
	fMove.x *= 0.2;
	fMove.z *= 0.2;

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

		//外積が-になる角度なら
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		SetRotateY(degree);

		SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));
	}
}

void Player::TellStatus()
{
	
	//どっちも違う気がする。どうやってプレイヤーからMetaAIに死んだことを伝える？名前検索しちゃっていい？

	//((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	//((MainGameScene*)GetParent())->CallStatus(GetObjectID(), GetStatus());

	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ChangeStatus(GetObjectID(), GetStatus());
	((MetaAI*)GetParent()->FindChildObject("MetaAI"))->ToCreateMode();
}