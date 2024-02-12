#include "Timer.h"
#include "Text.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj)
	: GameObject(obj, "Timer"), flame_(0), startFlame_(0), activeUpdate_(false), activeDraw_(false), drawX_(0), drawY_(0)
{
	num_ = new Text;
	num_->Initialize();
}

Timer::~Timer()
{
	//delete num_;
}

void Timer::Initialize()
{
	flame_ = 0;
	startFlame_ = 0;
	activeUpdate_ = false;
	activeDraw_ = false;
}

void Timer::Update()
{
	if (activeUpdate_) {
		if (flame_ > 0) {
			flame_--;
		}
	}
}

void Timer::Draw()
{

	if (!activeDraw_) {
		return;
	}

	num_->SetScale(1.0f);
	num_->Draw(drawX_, drawY_, "Time");
	if (flame_ % FPS < 10)
		num_->SetScale((flame_ % FPS) * 0.2f + 1.0f);
	else
		num_->SetScale(1.0f);
	int sec = flame_ / FPS;
	num_->Draw(drawX_ + 100, drawY_, sec);
}

void Timer::Release()
{
}

void Timer::SetLimit(float seconds)
{
	flame_ = (int)(seconds * FPS);
	startFlame_ = flame_;
}

void Timer::Start()
{
	activeUpdate_ = true;
}

void Timer::Stop()
{
	activeUpdate_ = false;
}

void Timer::Reset()
{
	flame_ = startFlame_;
	activeUpdate_ = false;
}

void Timer::StartDraw()
{
	activeDraw_ = true;
}

void Timer::StopDraw()
{
	activeDraw_ = false;
}

bool Timer::IsFinished()
{
	return (flame_ == 0);
}
