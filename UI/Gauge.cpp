#include "Gauge.h"
#include "../Engine/Image.h"
#include<assert.h>

//コンストラクタ
Gauge::Gauge(GameObject* parent)
	: GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
	maxHp_(0), nowHp_(0)
{
	transform_.position_.x = -0.95f;
	transform_.position_.y = 0.7f;
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
	hPictGauge_ = Image::Load("Image/PlayerUI/HPGauge5.png");
	assert(hPictGauge_ >= 0);

	ImageWidth_ = 256;
	ImageHeight_ = 64;

	hPictFrame_ = Image::Load("Image/PlayerUI/HPFlame2.png");
	assert(hPictFrame_ >= 0);

	

}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{
	//同じ変数で管理するとフレームまで伸び縮みして見栄えが悪い
	Transform transGauge = transform_;
	transGauge.scale_.x = (float)nowHp_ / (float)maxHp_;

	//int left = ImageWidth_ / 2 - ImageWidth_ / 2 * nowHp_; //画像的に左端じゃなくて真ん中から
	//int width = ImageWidth_ * nowHp_;
	//Image::SetRect(hPictGauge_, left, 0, width, ImageHeight_);
	

	Image::SetTransform(hPictFrame_, transform_);
	Image::Draw(hPictFrame_);

	Image::SetTransform(hPictGauge_, transGauge);
	Image::Draw(hPictGauge_);
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
