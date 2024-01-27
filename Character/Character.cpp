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
	isKnockBack_ = false;

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


