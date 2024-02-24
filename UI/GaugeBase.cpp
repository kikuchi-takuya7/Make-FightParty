#include "GaugeBase.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;
}


//�R���X�g���N�^
GaugeBase::GaugeBase(GameObject* parent, std::string name)
	: GameObject(parent, name), maxGauge_(ZERO), nowGauge_(ZERO)
{
}

//�f�X�g���N�^
GaugeBase::~GaugeBase()
{
}

//������
void GaugeBase::Initialize()
{
	ChildInitialize();
}

//�X�V
void GaugeBase::Update()
{
	/*if (IsEntered()) {
		return;
	}*/

	ChildUpdate();

	animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;
}

//�`��
void GaugeBase::Draw()
{

	if (IsVisibled()) {
		return;
	}

	ChildDraw();



	//�t���[���̈ʒu�������
	/*Transform transFlame = transform_;
	transFlame.position_.y -= 0.01f;
	transFlame.scale_.y += 0.05f;

	Image::SetTransform(hPict_[FLAME], transFlame);
	Image::Draw(hPict_[FLAME]);

	Transform transGaugeBase = transform_;
	transGaugeBase.scale_.x = ((float)animGauge_ / (float)maxGauge_) * transform_.scale_.x;

	if (nowGauge_ <= PINCH) {
		Image::SetTransform(hPict_[GaugeLOW], transGaugeBase);
		Image::Draw(hPict_[GaugeLOW]);
	}
	else {
		Image::SetTransform(hPict_[GaugeMAIN], transGaugeBase);
		Image::Draw(hPict_[GaugeMAIN]);
	}*/


}

//�J��
void GaugeBase::Release()
{
}

void GaugeBase::SetGauge(int nowGaugeBase, int maxGaugeBase)
{
	nowGauge_ = nowGaugeBase;
	maxGauge_ = maxGaugeBase;
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���
}

void GaugeBase::SetNowGauge(int nowGaugeBase)
{
	nowGauge_ = nowGaugeBase;

	//���炩��HP�𓮂������߂ɏ��X�ɒl��ς���
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���

}

void GaugeBase::AddValue(float v)
{
	nowGauge_ += v;
	if (nowGauge_ < ZERO)
		nowGauge_ = ZERO;
	else if (nowGauge_ > maxGauge_)
		nowGauge_ = maxGauge_;
}

void GaugeBase::SetValue(float v)
{
	assert(v >= MIN && v <= MAX);

	nowGauge_ = v;
	if (nowGauge_ < ZERO)
		nowGauge_ = ZERO;
	else if (nowGauge_ > maxGauge_)
		nowGauge_ = maxGauge_;
}

float GaugeBase::GetValue()
{
	return nowGauge_;
}
