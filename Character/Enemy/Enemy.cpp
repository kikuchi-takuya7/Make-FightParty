#include "Enemy.h"
#include "../../Engine/Model.h"
#include "../../Engine/Input.h"
#include "../../Engine/Global.h"

//定数
namespace {
	const int ENEMY_HP = 100;
	const int ENEMY_ATTACK_POWER = 20;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(1, 2, 1);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:Character(parent, "Enemy"), hModel_(-1),pState_(new EnemyStateManager), CharacterAI_(new CharacterAI(this))

{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{

	pBodyCollision_ = new BoxCollider(XMFLOAT3(ZERO, 1, ZERO), XMFLOAT3(1, 2, 1), ZERO_FLOAT3);
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, XMFLOAT3(0, 180, 0));
	AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK);

	status_ = { ENEMY_HP,ENEMY_ATTACK_POWER,false };

	//モデルデータのロード
	hModel_ = Model::Load("PlayerFbx/player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.z = 25.0f;
	transform_.position_.x = 255.0f;

	CharacterAI_->Initialize();


}

//更新
void Enemy::ChildUpdate()
{

	CharacterAI_->MoveEnemy();

	//pState_->Update(this);

}

//描画
void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

#ifdef _DEBUG
	CollisionDraw();
#endif
}

//開放
void Enemy::Release()
{
	SAFE_DELETE(CharacterAI_);
	SAFE_DELETE(pState_);
}

//何か当たった時の処理
void Enemy::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetTypee)
{


}

void Enemy::Move()
{
}
