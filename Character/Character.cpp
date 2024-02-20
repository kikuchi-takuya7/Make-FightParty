#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"

namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),pBodyCollision_(nullptr),pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3),stopDraw_(false)
{
}

//デストラクタ
Character::~Character()
{
}

//初期化
void Character::Initialize()
{
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	status_ = { CHARACTER_HP,CHARACTER_ATTACK_POWER, 0, false };



	ChildInitialize();
}

//更新
void Character::Update()
{
	//動いてほしくないとき
	if (IsEntered() == false) {
		return;
	}


	//今いる位置をprevPosに置いておく
	prevPos_ = transform_.position_;

	


	ChildUpdate();


}

//描画
void Character::Draw()
{

	if (stopDraw_ == true)
		return;

	ChildDraw();
}

//開放
void Character::Release()
{
	ChildRelease();

	//試合中以外、Collisionは消しているのでここでDELETEする。尚実行中に消すとエラーになる
	//ていうかnullptr入れてるはずなのになぜ例外が出るのか
	SAFE_DELETE(pAttackCollision_);
	SAFE_DELETE(pBodyCollision_);
	
}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	
	if (status_.dead) {
		return;
	}

	//壁にぶつかったら前にいた座標に戻す
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BROCK) {
		SetPosition(prevPos_);
	}

	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		//HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

	}

	ChildOnCollision(pTarget, myType, targetType);
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;

	//HPが0になったら
	if (status_.hp <= 0) {
		status_.dead = true;
	}
}

void Character::StopDraw()
{
	stopDraw_ = true;
}

void Character::StartDraw()
{
	stopDraw_ = false;
}

void Character::Dead()
{
	status_.dead = true;
}

void Character::KnockBackEnter(float distance)
{
	//色々初期化
	knockBackRate_ = 0.0f;


	//敵の向いてる方向に回転させるため回転を逆にする
	targetRot_.y = targetRot_.y - 180;
	this->SetRotateY(targetRot_.y);


	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 floatPos = this->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//最初に最終的な位置を確認しておく
	XMVECTOR move = { ZERO, ZERO, distance, ZERO };

	//移動ベクトルを変形 (敵と同じ向きに回転) させる
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(targetRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//プレイヤーを敵と反対方向に移動させる
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	if (lastPoint_.x <= 0.5) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 28.5) {
		lastPoint_.x = 28.5;
	}
	if (lastPoint_.z <= 0.5) {
		lastPoint_.z = 0.5;
	}
	if (lastPoint_.z >= 28.5) {
		lastPoint_.z = 28.5;
	}

}

void Character::KnockBackUpdate(float knockBackSpeed)
{

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 playerPos = GetPosition();

	RateMovePosition(playerPos, lastPoint_, knockBackSpeed);

	SetPosition(playerPos);

}

float Character::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}


