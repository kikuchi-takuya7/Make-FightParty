#include "Gauge.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

}


//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
	: GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
	maxHp_(0), nowHp_(0)
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
	hPictGauge_ = Image::Load("Image/PlayerUI/HPGauge5.png");
	assert(hPictGauge_ >= 0);

	hPictFrame_ = Image::Load("Image/PlayerUI/HPFlame2.png");
	assert(hPictFrame_ >= 0);

	

}

//�X�V
void Gauge::Update()
{
	animHp_ = (animHp_ * 9 + nowHp_) / 10;
}

//�`��
void Gauge::Draw()
{
	//�����ϐ��ŊǗ�����ƃt���[���܂ŐL�яk�݂��Ă��܂�
	Transform transGauge = transform_;
	transGauge.scale_.x = ((float)animHp_ / (float)maxHp_) * transform_.scale_.x;

	Image::SetTransform(hPictFrame_, transform_);
	Image::Draw(hPictFrame_);

	Image::SetTransform(hPictGauge_, transGauge);
	Image::Draw(hPictGauge_);
}

//�J��
void Gauge::Release()
{
}

void Gauge::SetGauge(int nowGauge, int maxGauge)
{
	nowHp_ = nowGauge;
	maxHp_ = maxGauge;
	animHp_ = (animHp_ * 9 + nowGauge) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���
}

void Gauge::SetNowGauge(int nowGauge)
{
	nowHp_ = nowGauge;
	
	//���炩��HP�𓮂������߂ɏ��X�ɒl��ς���
	animHp_ = (animHp_ * 9 + nowGauge) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���

}

void Gauge::AddValue(float v)
{
	nowHp_ += v;
	if (nowHp_ < ZERO)
		nowHp_ = ZERO;
	else if (nowHp_ > maxHp_)
		nowHp_ = maxHp_;
}

void Gauge::SetValue(float v)
{
	assert(v >= MIN && v <= MAX);

	nowHp_ = v;
	if (nowHp_ < ZERO)
		nowHp_ = ZERO;
	else if (nowHp_ > maxHp_)
		nowHp_ = maxHp_;
}

float Gauge::GetValue()
{
	return nowHp_;
}
