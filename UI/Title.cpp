#include "Title.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"

//�R���X�g���N�^
Title::Title(GameObject* parent)
    :GameObject(parent, "Title")
{
}

//�f�X�g���N�^
Title::~Title()
{
}

//������
void Title::Initialize()
{
	std::string str[NUM] = { "Make","&","Fight Party" };


	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/Title/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	make_Trans_.position_ = XMFLOAT3(0, 0.7, 0);
	and_Trans_.position_ = XMFLOAT3(0, 0.5, 0);
	fight_Trans_.position_ = XMFLOAT3(0, 0.3, 0);

	pText_ = new Text;
	pText_->Initialize();
}

//�X�V
void Title::Update()
{
}

//�`��
void Title::Draw()
{
	Image::SetTransform(hPict_[MAKE], make_Trans_);
	Image::Draw(hPict_[MAKE]);

	Image::SetTransform(hPict_[AND], and_Trans_);
	Image::Draw(hPict_[AND]);

	Image::SetTransform(hPict_[FIGHT], fight_Trans_);
	Image::Draw(hPict_[FIGHT]);

	float textX = Direct3D::screenWidth_ / 2;
	float textY = Direct3D::screenHeight_ / 2 + 200;

	pText_->Draw(500, 600, "PleaseSpace");
}

//�J��
void Title::Release()
{
}