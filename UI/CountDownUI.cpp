#include "CountDownUI.h"
#include "../Engine/Timer.h"
#include "../Engine/Image.h"

namespace {
	const int COUNT = 4;
	const int FPS = 60;
}

//�R���X�g���N�^
CountDownUI::CountDownUI(GameObject* parent)
    :GameObject(parent, "CountDownUI"), timer_(Instantiate<Timer>(this))
{
}

//�f�X�g���N�^
CountDownUI::~CountDownUI()
{
}

//������
void CountDownUI::Initialize()
{
	std::string str[COUNT_NUM] = { "Count-GO","Count-1","Count-2","Count-3" };


	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/CountDownUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	transform_.position_ = XMFLOAT3(ZERO, SpriteToFloatY(200), ZERO);

	timer_->SetLimit(COUNT);
	timer_->StopDraw();
}

//�X�V
void CountDownUI::Update()
{
}

//�`��
void CountDownUI::Draw()
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
		if (flame % FPS < 10)//�]��͈̔͂�60�܂ł��邩��Aflame������Ό���قǗ]�肪������̂ōŏ������ł����Ȃ�
			SetScale((flame % FPS) * 0.2f + 1.0f);
		else
			SetScale(1.0f);
	}
#else

	SetScale(1.0f);
	if (flame % FPS < 10)//�]��͈̔͂�60�܂ł��邩��Aflame������Ό���قǗ]�肪������̂ōŏ������ł����Ȃ�
		SetScale((flame % FPS) * 0.2f + 1.0f);
	else
		SetScale(1.0f);

#endif

	

	//-1�ȉ��ɂȂ�ƕ\������Ȃ��Ȃ��
	Image::SetTransform(hPict_[sec], transform_);
	Image::Draw(hPict_[sec]);
}

//�J��
void CountDownUI::Release()
{
}

void CountDownUI::Reset()
{
	timer_->Reset();

}

void CountDownUI::Start()
{
	timer_->Start();
}

bool CountDownUI::IsFinished()
{
	return timer_->IsFinished();
}
