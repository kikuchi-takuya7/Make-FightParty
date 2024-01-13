#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//定数
namespace {
	const int PLAYER_HP = 100;
	const int PLAYER_ATTACK_POWER = 20;

}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), XMFLOAT3(ZERO, ZERO, ZERO));
	AddCollider(pBodyCollision_);

}

//更新
void Enemy::Update()
{



	pState_->Update(this);

}

//描画
void Enemy::Draw()
{

}

//開放
void Enemy::Release()
{
	SAFE_DELETE(pState_);

}

//何か当たった時の処理
void Enemy::OnCollision(GameObject* pTarget)
{


}

void Enemy::Move()
{
}
