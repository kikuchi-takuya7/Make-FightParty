#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"
#include "../Stage/CreateMode/StageSource/TestFloor.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1),pCreateMode_(nullptr), pStageSourceList_(0)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	//モデルデータのロード
	hModel_ = Model::Load("Stage/StageBrock.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = ZERO;
	transform_.position_.z = ZERO;



}

void Stage::Update()
{
	//pCreateMode_->Update();
}

void Stage::Draw()
{

	Transform blockTrans;

	for (int x = 0; x < STAGE_SIZE.x; x++) {
		for (int z = 0; z < STAGE_SIZE.z; z++) {
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(hModel_, blockTrans);
			Model::Draw(hModel_);
		}
	}

	for (int i = 0; i < pStageSourceList_.size(); i++) {

		//描画はそれぞれのソースに一任しちゃう。もしかしたら良くないのかもしれないけど
	}

	

}

void Stage::Release()
{
	//SAFE_DELETE(pCreateMode_);
}

XMFLOAT3 Stage::GetStageSize()
{
	return STAGE_SIZE;
}
