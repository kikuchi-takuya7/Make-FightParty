#include "RankingGaugeUI.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float PINCH = 20.0f;
}


//コンストラクタ
RankingGaugeUI::RankingGaugeUI(GameObject* parent)
	: GaugeBase(parent, "RankingGaugeUI")
{
}

//デストラクタ
RankingGaugeUI::~RankingGaugeUI()
{
}

//初期化
void RankingGaugeUI::ChildInitialize()
{

	

}

//更新
void RankingGaugeUI::ChildUpdate()
{
	/*animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;*/
}

//描画
void RankingGaugeUI::ChildDraw()
{

	////フレームの位置を微調整
	//Transform transFlame = transform_;
	//transFlame.position_.y -= 0.01f;
	//transFlame.scale_.y += 0.05f;

	//Image::SetTransform(hPict_[FLAME], transFlame);
	//Image::Draw(hPict_[FLAME]);

	//Transform transRankingGaugeUI = transform_;
	//transRankingGaugeUI.scale_.x = ((float)animGauge_ / (float)maxGauge_) * transform_.scale_.x;

	//if (nowGauge_ <= PINCH) {
	//	Image::SetTransform(hPict_[GaugeLOW], transRankingGaugeUI);
	//	Image::Draw(hPict_[GaugeLOW]);
	//}
	//else {
	//	Image::SetTransform(hPict_[GaugeMAIN], transRankingGaugeUI);
	//	Image::Draw(hPict_[GaugeMAIN]);
	//}


}

//開放
void RankingGaugeUI::ChildRelease()
{
}