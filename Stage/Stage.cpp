#include "Stage.h"
#include "../Engine/Model.h"


Stage::Stage(GameObject* parent):hModel_(-1)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	//モデルデータのロード
	hModel_ = Model::Load("Map/Stage.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 15.0f;
	transform_.position_.z = 15.0f;

}

void Stage::Update()
{
}

void Stage::Draw()
{

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Stage::Release()
{
}
