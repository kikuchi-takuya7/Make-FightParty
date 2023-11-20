#include "Timer.h"
#include "Text.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj): GameObject(obj, "Timer"), 
	frame(0), active(false), drawX(0), drawY(0)
{
	num = new Text;
	num->Initialize();
}

Timer::~Timer()
{
	delete num;
}

void Timer::Initialize()
{
	frame = 0;
	active = false;
}

void Timer::Update()
{
	if (active) {
		if (frame > 0) {
			frame--;
		}
	}
}

void Timer::Draw()
{
	num->SetScale(1.0f);
	num->Draw(drawX, drawY, "Time");
	if (frame % FPS < 10)
		num->SetScale((frame%FPS)*0.2f+1.0f);
	else
		num->SetScale(1.0f);
	int sec = frame / FPS;
	num->Draw(drawX+100, drawY, sec);
}

void Timer::Release()
{
}

void Timer::SetLimit(float seconds)
{
	frame = (int)(seconds * FPS);
}

void Timer::Start()
{
	active = true;
}

void Timer::Stop()
{
	active = false;
}

bool Timer::IsFinished()
{
	return (frame == 0);
}
