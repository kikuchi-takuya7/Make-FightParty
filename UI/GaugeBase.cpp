#include "GaugeBase.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;
}


//コンストラクタ
GaugeBase::GaugeBase(GameObject* parent, std::string name)
	: GameObject(parent, name), maxGauge_(ZERO), nowGauge_(ZERO)
{
}

//デストラクタ
GaugeBase::~GaugeBase()
{
}

//初期化
void GaugeBase::Initialize()
{
	ChildInitialize();
}

//更新
void GaugeBase::Update()
{
	/*if (IsEntered()) {
		return;
	}*/

	ChildUpdate();

	animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;
}

//描画
void GaugeBase::Draw()
{

	if (IsVisibled()) {
		return;
	}

	ChildDraw();



	//フレームの位置を微調整
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

//開放
void GaugeBase::Release()
{
}

void GaugeBase::SetGauge(int nowGaugeBase, int maxGaugeBase)
{
	nowGauge_ = nowGaugeBase;
	maxGauge_ = maxGaugeBase;
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHpが9とnowHpが1だから足して10で割る
}

void GaugeBase::SetNowGauge(int nowGaugeBase)
{
	nowGauge_ = nowGaugeBase;

	//滑らかにHPを動かすために徐々に値を変える
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHpが9とnowHpが1だから足して10で割る

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
