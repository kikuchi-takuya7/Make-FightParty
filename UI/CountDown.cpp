#include "CountDown.h"
#include "../Engine/Timer.h"
#include "../Engine/Image.h"

namespace {
	const int COUNT = 4;
	const int FPS = 60;
}

//コンストラクタ
CountDown::CountDown(GameObject* parent)
    :GameObject(parent, "CountDown"), timer_(Instantiate<Timer>(this))
{
}

//デストラクタ
CountDown::~CountDown()
{
}

//初期化
void CountDown::Initialize()
{
	std::string str[COUNT_NUM] = { "Count-GO","Count-1","Count-2","Count-3" };


	//画像データのロード
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/CountDown/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	transform_.position_ = XMFLOAT3(ZERO, 0.5f, ZERO);

	timer_->SetLimit(COUNT);
	timer_->StopDraw();
}

//更新
void CountDown::Update()
{
}

//描画
void CountDown::Draw()
{

	int flame = timer_->GetNowFlame();

	int sec = flame / FPS;

#if 0
	if (sec == 0) {

		SetScale(1.0f);
		if (flame % FPS < 10)
			SetScale(1.0f);
		else
			SetScale((flame % FPS) * 0.2f + 1.0f);
}
	else {

		SetScale(1.0f);
		if (flame % FPS < 10)//余りの範囲が60まであるから、flameが減れば減るほど余りが増えるので最初だけでかくなる
			SetScale((flame % FPS) * 0.2f + 1.0f);
		else
			SetScale(1.0f);
	}
#else

	SetScale(1.0f);
	if (flame % FPS < 10)//余りの範囲が60まであるから、flameが減れば減るほど余りが増えるので最初だけでかくなる
		SetScale((flame % FPS) * 0.2f + 1.0f);
	else
		SetScale(1.0f);

#endif

	

	//-1以下になると表示されなくなるよ
	Image::SetTransform(hPict_[sec], transform_);
	Image::Draw(hPict_[sec]);
}

//開放
void CountDown::Release()
{
}

void CountDown::Reset()
{
	timer_->Reset();

}

void CountDown::Start()
{
	timer_->Start();
}

bool CountDown::IsFinished()
{
	return timer_->IsFinished();
}
