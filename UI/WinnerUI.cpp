#include "WinnerUI.h"
#include "../Engine/Image.h"
#include "../Engine/Audio.h"
#include<assert.h>

namespace {
	const XMFLOAT3 WINNER_POS = { 625, 180,ZERO };
	const XMFLOAT3 NUMBER_POS = { 585, 125,ZERO };
}

//�R���X�g���N�^
WinnerUI::WinnerUI(GameObject* parent)
	: GameObject(parent, "WinnerUI"), hPict_{-1,-1,-1,-1}, hWinnerPict_(-1),winnerID_(0),hAudio_(-1)
{
}

//�f�X�g���N�^
WinnerUI::~WinnerUI()
{
}

//������
void WinnerUI::Initialize()
{
	std::string str[PLAYER_NUM] = { "One","Two","Three", "Four" };

	//�摜�f�[�^�̃��[�h
	for (int i = ZERO; i < PLAYER_NUM; i++) {

		std::string dir = "Image/WinnerUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= ZERO);
	}

	hWinnerPict_ = Image::Load("Image/WinnerUI/P-WIN.png");
	assert(hWinnerPict_ >= ZERO);

	hAudio_ = Audio::Load("Audio/SE/Winner.wav", false, 1);

	isSound_ = false;
}

//�X�V
void WinnerUI::Update()
{

}

//�`��
void WinnerUI::Draw()
{
	//SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	if (IsVisibled()) {
		isSound_ = false;
		Audio::Stop(hAudio_);
		return;
	}

	if (isSound_ == false) {
		Audio::Play(hAudio_);
		isSound_ = true;
	}
	

	Transform winnerTrans = transform_;
	winnerTrans.position_.x = SpriteToFloatX(WINNER_POS.x);
	winnerTrans.position_.y = SpriteToFloatY(WINNER_POS.y);

	Image::SetTransform(hWinnerPict_, winnerTrans);
	Image::Draw(hWinnerPict_);

	Transform numberTrans = transform_;
	numberTrans.position_.x = SpriteToFloatX(NUMBER_POS.x);
	numberTrans.position_.y = SpriteToFloatY(NUMBER_POS.y);

	Image::SetTransform(hPict_[winnerID_], numberTrans);
	Image::Draw(hPict_[winnerID_]);

}

//�J��
void WinnerUI::Release()
{
}
