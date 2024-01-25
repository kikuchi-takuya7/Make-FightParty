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

}

//開放
void Character::Release()
{

}

void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		
	}

	//攻撃を当てた時の処理
	if (myType == COLLIDER_ATTACK && targetType == COLLIDER_BODY)
	{
		((Character*)pTarget)->HitDamage(status_.attackPower);
	}
}

void Character::HitDamage(int damage)
{
	status_.hp -= damage;



}

