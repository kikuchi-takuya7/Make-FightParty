#include "TrapKillScore.h"
#include "../../Engine/Image.h"

TrapKillScore::TrapKillScore(GameObject* parent)
	: GaugeBase(parent, "TrapKillScore"), hPict_(-1)
{
}

TrapKillScore::~TrapKillScore()
{
}

void TrapKillScore::ChildInitialize()
{
	hPict_ = Image::Load("Image/RankingUI/TrapKillGauge2.png");
	assert(hPict_ >= 0);
}

void TrapKillScore::ChildUpdate()
{
}

void TrapKillScore::ChildDraw()
{
	Image::SetTransform(hPict_, transGaugeUI_);
	Image::Draw(hPict_);
}

void TrapKillScore::ChildRelease()
{
}
