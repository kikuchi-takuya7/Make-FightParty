#include "RateFrame.h"
#include "../GameObject.h"

RateFrame::RateFrame(GameObject* parent)
	:GameObject(parent, "RateFrame"),rate_(0),startRate_(0), frame_(0), isUpdate_(false), type_(CONSTANT)
{
}

RateFrame::~RateFrame()
{
}

void RateFrame::Initialize()
{
}

void RateFrame::Update()
{
	
	if (isUpdate_ == false)
		return;

	switch (type_)
	{
	case CONSTANT://“™‘¬
		
		frame_ += rate_;
		break;

	case ACCELERATION://‰Á‘¬

		rate_ += rate_;
		frame_ = rate_;
		break;

	default:
		break;
	}

	//1ˆÈã‚È‚ç1‚É–ß‚·
	if (frame_ > 1.0f) {
		frame_ = 1.0f;
	}
	
}

void RateFrame::Draw()
{
}

void RateFrame::Release()
{
}

void RateFrame::Reset()
{
	frame_ = 0.0f;
	rate_ = startRate_;
}
	
void RateFrame::SetData(float rate, bool isUpdate, ADDTYPE type)
{
	startRate_ = rate;
	rate_ = rate;
	isUpdate_ = isUpdate;
	type_ = type;
	frame_ = 0.0f;

}

void RateFrame::SetRate(float rate)
{
	rate_ = rate;
}

void RateFrame::SetFlag(bool isUpdate)
{
	isUpdate_ = isUpdate;
}

float RateFrame::GetNowFrame()
{
	return frame_;
}

