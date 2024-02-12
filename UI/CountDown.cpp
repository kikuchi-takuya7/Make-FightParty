#include "CountDown.h"
#include "../Engine/Timer.h"
#include "../Engine/Image.h"

//�R���X�g���N�^
CountDown::CountDown(GameObject* parent)
    :GameObject(parent, "CountDown")
{
}

//�f�X�g���N�^
CountDown::~CountDown()
{
}

//������
void CountDown::Initialize()
{
	std::string str[COUNT_NUM] = { "Count-GO","Count-1","Count-2","Count-3" };


	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/CountDown";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	transform_.position_ = XMFLOAT3(ZERO, 0.5f, ZERO);

}

//�X�V
void CountDown::Update()
{
}

//�`��
void CountDown::Draw()
{
}

//�J��
void CountDown::Release()
{
}