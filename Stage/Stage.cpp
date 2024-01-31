#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"

Stage::Stage(GameObject* parent):hModel_(-1),pCreateMode_(nullptr)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	//モデルデータのロード
	hModel_ = Model::Load("Stage/Stage.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 15.0f;
	transform_.position_.z = 15.0f;



}

void Stage::Update()
{
	pCreateMode_->Update();
}

void Stage::Draw()
{

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	pCreateMode_->Draw();

}

void Stage::Release()
{
	SAFE_DELETE(pCreateMode_);
}
