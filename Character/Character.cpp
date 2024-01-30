#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"


//コンストラクタ
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),pBodyCollision_(nullptr),pAttackCollision_(nullptr)
{
}

//デストラクタ
Character::~Character()
{
}

//初期化
void Character::Initialize()
{

	ChildInitialize();
}

//更新
void Character::Update()
{

	//死んでる時とかアップデートしたくないときにここで止めちゃえばいい

	ChildUpdate();
}

//描画
void Character::Draw()
{
	ChildDraw();
}

//開放
void Character::Release()
{
	ChildRelease();
}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;



}

void Character::SetAttackCollider()
{
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);
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

	if (lastPoint_.x <= 0) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 29) {
		lastPoint_.x = 29;
	}
	if (lastPoint_.z <= 0) {
		lastPoint_.z = 0;
	}
	if (lastPoint_.z >= 29) {
		lastPoint_.z = 29;
	}

	//player->SetPosition(VectorToFloat3(pos));
}

void Character::KnockBackUpdate(int rigidityFlame)
{

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 playerPos = this->GetPosition();

	//レートでぬるぬる動くように
	if (knockBackRate_ < 1.0f) {
		knockBackRate_ += 0.05f;

		// 変な数字で止まらないように
		if (knockBackRate_ > 1.0f)
			knockBackRate_ = 1.0f;

		playerPos.x = GetRateValue(playerPos.x, lastPoint_.x, knockBackRate_);
		playerPos.z = GetRateValue(playerPos.z, lastPoint_.z, knockBackRate_);

		this->SetPosition(playerPos);

	}
}

float Character::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}


