#include "KillScore.h"
#include "../../Engine/Image.h"



KillScore::KillScore(GameObject* parent)
	: GaugeBase(parent, "KillScore"), hPict_(-1)
{
}

KillScore::~KillScore()
{
}

void KillScore::ChildInitialize()
{
	hPict_ = Image::Load("Image/RankingUI/KillGauge2.png");
	assert(hPict_ >= 0);

}

void KillScore::ChildUpdate()
{
}

void KillScore::ChildDraw()
{
	Image::SetTransform(hPict_, transGaugeUI_);
	Image::Draw(hPict_);
}

void KillScore::ChildRelease()
{
}

bool KillScore::IsEndAnim()
{
	return false;
}
