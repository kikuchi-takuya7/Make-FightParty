#include "TitleUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"

//�R���X�g���N�^
TitleUI::TitleUI(GameObject* parent)
    :GameObject(parent, "TitleUI")
{
}

//�f�X�g���N�^
TitleUI::~TitleUI()
{
}

//������
void TitleUI::Initialize()
{
	std::string str[NUM] = { "Make","&","Fight Party" };


	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < NUM; i++) {

		std::string dir = "Image/TitleUI/";
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
void TitleUI::Update()
{
}

//�`��
void TitleUI::Draw()
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
void TitleUI::Release()
{
}