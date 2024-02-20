#include "Gauge.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float PINCH = 20.0f;
}


//コンストラクタ
Gauge::Gauge(GameObject* parent)
	: GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
	maxHp_(0), nowHp_(0)
{
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
	hPictGauge_ = Image::Load("Image/PlayerUI/HPGauge.png");
	assert(hPictGauge_ >= 0);

	hPictGaugeLow_ = Image::Load("Image/PlayerUI/HPGaugeLow.png");
	assert(hPictGaugeLow_ >= 0);

	hPictFrame_ = Image::Load("Image/PlayerUI/HPFlame.png");
	assert(hPictFrame_ >= 0);
}

//更新
void Gauge::Update()
{
	animHp_ = (animHp_ * 9 + nowHp_) / 10;
}

//描画
void Gauge::Draw()
{

	if (IsVisibled()) {
		return;
	}

	//フレームの位置を微調整
	Transform transFlame = transform_;
	transFlame.position_.y -= 0.01f;
	transFlame.scale_.y += 0.05f;

	Image::SetTransform(hPictFrame_, transFlame);
	Image::Draw(hPictFrame_);


	Transform transGauge = transform_;
	transGauge.scale_.x = ((float)animHp_ / (float)maxHp_) * transform_.scale_.x;

	if (nowHp_ <= PINCH) {
		Image::SetTransform(hPictGaugeLow_, transGauge);
		Image::Draw(hPictGaugeLow_);
	}
	else {
		Image::SetTransform(hPictGauge_, transGauge);
		Image::Draw(hPictGauge_);
	}
}

//開放
void Gauge::Release()
{
}

void Gauge::SetGauge(int nowGauge, int maxGauge)
{
	nowHp_ = nowGauge;
	maxHp_ = maxGauge;
	animHp_ = (animHp_ * 9 + nowGauge) / 10; //animHpが9とnowHpが1だから足して10で割る
}

void Gauge::SetNowGauge(int nowGauge)
{
	nowHp_ = nowGauge;
	
	//滑らかにHPを動かすために徐々に値を変える
	animHp_ = (animHp_ * 9 + nowGauge) / 10; //animHpが9とnowHpが1だから足して10で割る

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
