#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
	const int STAGE_COST = 1;
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

	//width分の行を先にheight列分だけ確保しておく
	for (int i = ZERO; i < STAGE_SIZE.z; i++) {
		map_.emplace_back(STAGE_SIZE.x);
	}

	//ステージの初期コストを入れる
	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {

			map_.at(z).at(x) = STAGE_COST;

		}
	}

}

void Stage::Update()
{
	//pCreateMode_->Update();
}

void Stage::Draw()
{

	Transform blockTrans;

	for (int z = 0; z < STAGE_SIZE.z; z++) {
		for (int x = 0; x < STAGE_SIZE.x; x++) {
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(hModel_, blockTrans);
			Model::Draw(hModel_);
		}
	}


}

void Stage::Release()
{
	//SAFE_DELETE(pCreateMode_);
}

void Stage::AllStartUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Enter();
	}
}

void Stage::AllStopUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Leave();
	}
}

void Stage::SetStageCost(XMFLOAT3 pos, int cost)
{
	map_.at(pos.z).at(pos.x) = cost;
}

XMFLOAT3 Stage::GetStageSize()
{
	return STAGE_SIZE;
}
