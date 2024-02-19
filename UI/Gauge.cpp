#include "Gauge.h"
#include "../Engine/Image.h"
#include<assert.h>

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
	: GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
	maxHp_(0), nowHp_(0)
{
	transform_.position_.x = -0.95f;
	transform_.position_.y = 0.7f;
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

	ImageWidth_ = 256;
	ImageHeight_ = 64;

	hPictFrame_ = Image::Load("Image/PlayerUI/HPFlame2.png");
	assert(hPictFrame_ >= 0);

	

}

//�X�V
void Gauge::Update()
{
}

//�`��
void Gauge::Draw()
{
	//�����ϐ��ŊǗ�����ƃt���[���܂ŐL�яk�݂��Č��h��������
	Transform transGauge = transform_;
	transGauge.scale_.x = (float)nowHp_ / (float)maxHp_;

	//int left = ImageWidth_ / 2 - ImageWidth_ / 2 * nowHp_; //�摜�I�ɍ��[����Ȃ��Đ^�񒆂���
	//int width = ImageWidth_ * nowHp_;
	//Image::SetRect(hPictGauge_, left, 0, width, ImageHeight_);
	

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
	if (nowHp_ < 0.0f)
		nowHp_ = 0.0f;
	else if (nowHp_ > maxHp_)
		nowHp_ = maxHp_;
}

void Gauge::SetValue(float v)
{
	assert(v >= 0.0f && v <= 1.0f);

	nowHp_ = v;
	if (nowHp_ < 0.0f)
		nowHp_ = 0.0f;
	else if (nowHp_ > maxHp_)
		nowHp_ = maxHp_;
}

float Gauge::GetValue()
{
	return nowHp_;
}
