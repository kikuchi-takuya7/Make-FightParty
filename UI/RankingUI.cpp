#include "RankingUI.h"
#include "GaugeUI/RankingGaugeUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include <assert.h>

namespace {

	const XMFLOAT3 PAPER_SIZE = { 0.8f, 0.6f, 1 };
	const int MAX_PLAYER = 4;

	//ゲージが開始する初期位置、そこから4プレイヤー分の座標差
	const XMFLOAT3 FIRST_GAUGE_POS = { 266.5f,170,ZERO };
	const float GAUGE_Y_DIFF = 150;
	const int VICTORY_POINT = 100;
	const XMFLOAT3 GAUGE_SIZE = { 2.85f,0.5f,ZERO };

	const XMFLOAT3 START_POS = { ZERO, -5,ZERO };
	const float MOVE_RATE = 0.2f;

	const XMFLOAT3 TEXT_POS = { 550,700,ZERO };

	const int SCORE[GAUGE_NUM] = { 20,10,5 };
}

//コンストラクタ
RankingUI::RankingUI(GameObject* parent)
	: GameObject(parent, "RankingUI"),hPict_(-1),pText_(nullptr)
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

	for (int i = ZERO; i < MAX_PLAYER; i++) {
		RankingGaugeUI* pGauge = Instantiate<RankingGaugeUI>(this);
		float tes = FIRST_GAUGE_POS.y + (GAUGE_Y_DIFF * i);
		pGauge->SetPosition(XMFLOAT3(FIRST_GAUGE_POS.x, FIRST_GAUGE_POS.y + (GAUGE_Y_DIFF * i), ZERO));
		pGauge->SetGauge(ZERO, VICTORY_POINT);
		pGauge->SetScale(GAUGE_SIZE);
		pGaugeList_.emplace_back(pGauge);
	}

	transform_.position_ = START_POS;

	//誰が勝ったか、誰のオブジェクトが敵をキルしたか、誰かをキルしたか、相打ちならどうするか


	pText_ = new Text;
	pText_->Initialize();
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

	SetScale(PAPER_SIZE);

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	if (IsAllEndAnim()) {
		pText_->Draw(TEXT_POS.x, TEXT_POS.y, "Please Space");
	}

}

//開放
void RankingUI::Release()
{
	
}

bool RankingUI::IsAllEndAnim()
{
	for (int i = ZERO; i < pGaugeList_.size(); i++) {
		if(pGaugeList_.at(i)->IsAllEndAnim() == false)
			return false;
	}
	return true;
}

void RankingUI::EndAnim()
{
	for (int i = ZERO; i < pGaugeList_.size(); i++) {
		pGaugeList_.at(i)->AllEndAnim();
	}
}

void RankingUI::ResetPos()
{
	transform_.position_ = START_POS;
}

void RankingUI::SetPlayerName(int ID, std::string str)
{
	pGaugeList_.at(ID)->SetName(str);
}

void RankingUI::SetScore(int ID, SCOREGAUGELIST score, int num)
{
	for (int i = ZERO; i < num; i++) {
		pGaugeList_.at(ID)->PushScore(score);
	}
}

