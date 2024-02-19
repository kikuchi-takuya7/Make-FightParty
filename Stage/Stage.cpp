#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
	const int STAGE_COST = 1;
	const int moveZ[4] = { ZERO,ZERO,   1,  -1};
	const int moveX[4] = { 1,   -1,  ZERO,ZERO};
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1),debugModel_(-1), pCreateMode_(nullptr), pStageSourceList_(0)
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

	//debug用のモデルデータのロード
	debugModel_ = Model::Load("Stage/DebugBrock.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = ZERO;
	transform_.position_.z = ZERO;

	//width分の行を先にheight列分だけ確保しておく
	for (int i = ZERO; i < STAGE_SIZE.z; i++) {
		stageCost_.emplace_back(STAGE_SIZE.x);
		stageModel_.emplace_back(STAGE_SIZE.x);
	}

	//ステージの諸々を初期化
	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {

			stageCost_.at(z).at(x) = STAGE_COST;
			stageModel_.at(z).at(x) = hModel_;
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
			Model::SetTransform(stageModel_.at(z).at(x), blockTrans);
			Model::Draw(stageModel_.at(z).at(x));
		}
	}

	//描画し終わったら次のAstar経路を表示する為にモデルを全て初期化する
	for (int z = 0; z < STAGE_SIZE.z; z++) {
		for (int x = 0; x < STAGE_SIZE.x; x++) {
			stageModel_.at(z).at(x) = hModel_;
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
	stageCost_.at(pos.z).at(pos.x) = cost;

	//一マスだけ壁にすると斜め移動するときに引っかかるから上下もコストを反映させてみる
	for (int i = 0; i < 4; i++) {
		stageCost_.at(pos.z + moveZ[i]).at(pos.x + moveX[i]) = cost;
	}

}

void Stage::SetDebugModel(std::stack<std::pair<int, int>> pair)
{

	

	//Astarの経路探索で出た場所のモデルを変える
	while (!pair.empty())
	{
		stageModel_.at(pair.top().first).at(pair.top().second) = debugModel_;
		pair.pop();
	}
}

XMFLOAT3 Stage::GetStageSize()
{
	return STAGE_SIZE;
}
