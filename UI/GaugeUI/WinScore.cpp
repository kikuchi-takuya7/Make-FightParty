#include "WinScore.h"
#include "../../Engine/Image.h"



WinScore::WinScore(GameObject* parent)
	: GaugeBase(parent, "WinScore"),hPict_(-1)
{
}

WinScore::~WinScore()
{
}

void WinScore::ChildInitialize()
{
	hPict_ = Image::Load("Image/RankingUI/WinGauge.png");
	assert(hPict_ >= 0);
}

void WinScore::ChildUpdate()
{
}

void WinScore::ChildDraw()
{
	Image::SetTransform(hPict_, transGaugeUI_);
	Image::Draw(hPict_);
}

void WinScore::ChildRelease()
{
}

bool WinScore::IsEndAnim()
{
	return false;
}
