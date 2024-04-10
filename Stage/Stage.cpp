#include "Stage.h"
#include "../Engine/Model.h"
#include "../Engine/Global.h"
#include "CreateMode/CreateMode.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"


namespace {
	XMFLOAT3 STAGE_SIZE = XMFLOAT3(30.0f, ZERO, 30.0f);
	const int STAGE_COST = 1;

	//追加したオブジェクトの周囲に追加するコスト。完全な壁だった場合敵が止まってしまうため
	const int ADD_COST = 10;

	const int moveZ[4] = { ZERO,ZERO,   1,  -1};
	const int moveX[4] = { 1,   -1,  ZERO,ZERO};

	//上下左右に移動（探索）するための配列
	/*const int moveZ[8] = { ZERO,ZERO,	1,	-1, 1, 1,-1,-1 };
	const int moveX[8] = { 1,  -1,ZERO,ZERO, 1,-1, 1,-1 };*/
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage"),hModel_(-1),debugModel_(-1), pCreateMode_(nullptr), pStageSourceList_(ZERO)
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{

	//モデルデータのロード
	hModel_ = Model::Load("Stage/StageBrock.fbx");
	assert(hModel_ >= ZERO);

	//debug用のモデルデータのロード
	debugModel_ = Model::Load("Stage/DebugBrock.fbx");
	assert(hModel_ >= ZERO);

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

	

	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {
			Transform blockTrans;
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(stageModel_.at(z).at(x), blockTrans);
			Model::Draw(stageModel_.at(z).at(x));
		}
	}

	//描画し終わったら次のAstar経路を表示する為にモデルを全て初期化する
	for (int z = ZERO; z < STAGE_SIZE.z; z++) {
		for (int x = ZERO; x < STAGE_SIZE.x; x++) {
			stageModel_.at(z).at(x) = hModel_;
		}
	}

}

void Stage::Release()
{
	//SAFE_DELETE(pCreateMode_);
}

// 全てのupdateを許可
void Stage::AllStartUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Enter();
	}
}

//全てのupdateを止める
void Stage::AllStopUpdate()
{
	for (auto it = pStageSourceList_.begin(); it != pStageSourceList_.end(); it++) {
		(*it)->Leave();
	}
}

// ステージのコストをセットする
// 引数１：そのオブジェクトの位置
// 引数２：オブジェクトのコスト
// 引数３：x方向の大きさ
// 引数４：y方向の大きさ
void Stage::SetStageCost(XMFLOAT3 pos, int cost, int xSize, int zSize)
{
	XMFLOAT3 stagePos = pos;

	//xとzのサイズ分コストをつける
	for (int x = ZERO; x < xSize; x++) {
		for (int z = ZERO; z < zSize; z++) {

			//座標のの位置にコストをつける
			stageCost_.at(stagePos.z).at(stagePos.x) = cost;

			//一マスだけ壁にすると斜め移動するときに引っかかるから上下もコストを反映させる
			for (int i = ZERO; i < ARRAYSIZE(moveZ); i++) {

				int sz = stagePos.z + moveZ[i];
				int sx = stagePos.x + moveX[i];

				//画面外だったらやめる
				if (sx >= STAGE_SIZE.x || sx < ZERO || sz >= STAGE_SIZE.z || sz < ZERO) {
					continue;
				}

				//実際に壁というわけではないので壁にはしないけどコストを重くする
				stageCost_.at(sz).at(sx) = cost + ADD_COST;
			}

			stagePos.z++;
		}
		stagePos.x++;
	}

	
}

// Astarアルゴリズムで出た経路を表示する為にモデルを変える為の関数
// 引数：経路探索ででた経路
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
