#include "WinnerUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//�R���X�g���N�^
WinnerUI::WinnerUI(GameObject* parent)
	: GameObject(parent, "WinnerUI"), hPict_{-1,-1,-1,-1}, hWinnerPict_(-1)
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
	for (int i = 0; i < PLAYER_NUM; i++) {

		std::string dir = "Image/WinnerUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	hWinnerPict_ = Image::Load("Image/WinnerUI/P-WIN.png");

}

//�X�V
void WinnerUI::Update()
{

}

//�`��
void WinnerUI::Draw()
{
	//SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	Image::SetTransform(hWinnerPict_, transform_);
	Image::Draw(hWinnerPict_);

	Image::SetTransform(hPict_[winnerID_], transform_);
	Image::Draw(hPict_[winnerID_]);

}

//�J��
void WinnerUI::Release()
{
}
