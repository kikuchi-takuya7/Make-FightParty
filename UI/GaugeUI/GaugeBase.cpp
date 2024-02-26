#include "GaugeBase.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
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
	if (!IsEntered()) {
		return;
	}

	ChildUpdate();

	animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;
	if (animGauge_ >= nowGauge_ - 0.1f && animGauge_ <= nowGauge_) {
		animGauge_ = nowGauge_;
	}

	if (Input::IsKeyDown(DIK_P)) {
		nowGauge_ = maxGauge_;
	}
}

//描画
void GaugeBase::Draw()
{

	if (IsVisibled()) {
		return;
	}

	transGaugeUI_ = transform_;
	transGaugeUI_.scale_.x = ((float)animGauge_ / (float)maxGauge_) * transform_.scale_.x;

	ChildDraw();

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

bool GaugeBase::IsEndAnim()
{
	return (animGauge_ == nowGauge_);
}
