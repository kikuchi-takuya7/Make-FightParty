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
	: GameObject(parent, "Gauge"),maxHp_(ZERO), nowHp_(ZERO)
{
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{

	std::string str[HPIMAGE_NUM] = { "HPFlame","HPGauge","HPGaugeLow", "HPGaugeLowWhite"};

	//画像データのロード
	for (int i = 0; i < HPIMAGE_NUM; i++) {

		std::string dir = "Image/PlayerUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

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

	Image::SetTransform(hPict_[FLAME], transFlame);
	Image::Draw(hPict_[FLAME]);


	Transform transGauge = transform_;
	transGauge.scale_.x = ((float)animHp_ / (float)maxHp_) * transform_.scale_.x;

	if (nowHp_ <= PINCH) {
		Image::SetTransform(hPict_[GAUGELOW], transGauge);
		Image::Draw(hPict_[GAUGELOW]);
	}
	else {
		Image::SetTransform(hPict_[GAUGEMAIN], transGauge);
		Image::Draw(hPict_[GAUGEMAIN]);
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
