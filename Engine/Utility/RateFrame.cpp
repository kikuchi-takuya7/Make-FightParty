#include "RateFrame.h"
#include "../GameObject.h"

RateFrame::RateFrame(GameObject* parent)
	:GameObject(parent, "RateFrame"),rate_(0),frame_(0),isUpdate_(false)
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
	
	//�X�V���邩�ǂ����𕷂�
	if (isUpdate_) {
		frame_ += rate_;

		//1�ȏ�Ȃ�1�ɖ߂�
		if (frame_ > 1.0f) {
			frame_ = 1.0f;
		}
	}
	
}

void RateFrame::Release()
{
}
	
void RateFrame::SetData(float rate, bool isUpdate)
{
	rate_ = rate;
	isUpdate_ = isUpdate;
}

void RateFrame::SetRate(float rate)
{
}

void RateFrame::SetFlag(bool isUpdate)
{
	isUpdate_ = isUpdate;
}

float RateFrame::GetNowFrame()
{
	return frame_;
}

