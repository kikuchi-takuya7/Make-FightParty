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

