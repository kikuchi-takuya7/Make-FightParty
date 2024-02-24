#include "RankingUI.h"
#include "RankingGaugeUI.h"
#include "../Engine/Image.h"
#include <assert.h>

namespace {
	const int MAX_PLAYER = 4;
	const XMFLOAT3 FIRST_GAUGE_POS = { 200,100,ZERO };
	const float GAUGE_Y_DIFF = 100;
	const int VICTORY_POINT = 100;
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
		pGauge->SetPosition(XMFLOAT3(FIRST_GAUGE_POS.x, FIRST_GAUGE_POS.y + GAUGE_Y_DIFF * i, ZERO));
		pGauge->SetGauge(ZERO, VICTORY_POINT);
		pGaugeList_.emplace_back(pGauge);
	}




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

	SetScale(XMFLOAT3(0.8f,0.6f,1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

}

//開放
void RankingUI::Release()
{
}

void RankingUI::AddGaugeValue(int ID, int value)
{
	pGaugeList_.at(ID)->AddValue(value);
}

bool RankingUI::IsAllEndAnim()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		if(pGaugeList_.at(i)->IsEndAnim() == false)
			return false;
	}
	return true;
}

void RankingUI::StopDraw()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		pGaugeList_.at(i)->Visible();
	}
	Visible();
}

void RankingUI::StartDraw()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		pGaugeList_.at(i)->Invisible();
	}
	Invisible();
}

void RankingUI::StopUpdate()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		pGaugeList_.at(i)->Leave();
	}
	Leave();
}

void RankingUI::StartUpdate()
{
	for (int i = 0; i < pGaugeList_.size(); i++) {
		pGaugeList_.at(i)->Enter();
	}
	Enter();
}
