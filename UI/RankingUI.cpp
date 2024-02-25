#include "RankingUI.h"
#include "GaugeUI/RankingGaugeUI.h"
#include "../Engine/Image.h"
#include <assert.h>

namespace {
	const int MAX_PLAYER = 4;
	const XMFLOAT3 FIRST_GAUGE_POS = { 263,170,ZERO };
	const float GAUGE_Y_DIFF = 150;
	const int VICTORY_POINT = 100;
	const XMFLOAT3 GAUGE_SIZE = { 2.85f,0.5f,ZERO };

	const XMFLOAT3 START_POS = { ZERO, -5,ZERO };
	const float MOVE_RATE = 0.1f;
}

//コンストラクタ
RankingUI::RankingUI(GameObject* parent)
	: GameObject(parent, "RankingUI"),hPict_(-1)
{
}

//デストラクタ
RankingUI::~RankingUI()
{
}

//初期化
void RankingUI::Initialize()
{
	hPict_ = Image::Load("Image/RankingUI/RankingPaper.png");

	for (int i = 0; i < MAX_PLAYER; i++) {
		RankingGaugeUI* pGauge = Instantiate<RankingGaugeUI>(this);
		pGauge->SetPosition(XMFLOAT3(FIRST_GAUGE_POS.x, FIRST_GAUGE_POS.y + (GAUGE_Y_DIFF * i), ZERO));
		pGauge->SetGauge(ZERO, VICTORY_POINT);
		//pGauge->SetScale(GAUGE_SIZE);
		pGaugeList_.emplace_back(pGauge);
	}

	transform_.position_ = START_POS;

	//誰が勝ったか、誰のオブジェクトが敵をキルしたか、誰かをキルしたか、相打ちならどうするか
}

//更新
void RankingUI::Update()
{

}

//描画
void RankingUI::Draw()
{

	if (IsVisibled()) {
		return;
	}

	RateMovePosition(transform_.position_, ZERO_FLOAT3, MOVE_RATE);

	SetScale(XMFLOAT3(0.8f,0.6f,1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

}

//開放
void RankingUI::Release()
{
	
}

bool RankingUI::IsAllEndAnim()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		if(pGaugeList_.at(i)->IsEndAnim() == false)
			return false;
	}
	return true;
}

void RankingUI::ResetPos()
{
	transform_.position_ = START_POS;
}

void RankingUI::SetPlayerName(int ID, std::string str)
{
	pGaugeList_.at(ID)->SetName(str);
}

void RankingUI::SetScore(int ID, SCOREGAUGELIST score)
{
	pGaugeList_.at(ID)->PushScore(score);
}
