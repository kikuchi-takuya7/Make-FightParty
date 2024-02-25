#include "HpGaugeUI.h"
#include "../../Engine/Image.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float PINCH = 20.0f;
}


//�R���X�g���N�^
HpGaugeUI::HpGaugeUI(GameObject* parent)
	: GaugeBase(parent, "HpGaugeUI")
{
}

//�f�X�g���N�^
HpGaugeUI::~HpGaugeUI()
{
}

//������
void HpGaugeUI::ChildInitialize()
{

	std::string str[HPIMAGE_NUM] = { "HPFlame","HPGauge","HPGaugeLow", "HPGaugeLowWhite"};

	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < HPIMAGE_NUM; i++) {

		std::string dir = "Image/PlayerUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	Enter();
}

//�X�V
void HpGaugeUI::ChildUpdate()
{
	/*animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;*/
}

//�`��
void HpGaugeUI::ChildDraw()
{

	//�t���[���̈ʒu�������
	Transform transFlame = transform_;
	transFlame.position_.y -= 0.01f;
	transFlame.scale_.y += 0.05f;

	Image::SetTransform(hPict_[FLAME], transFlame);
	Image::Draw(hPict_[FLAME]);

	

	if (nowGauge_ <= PINCH) {
		Image::SetTransform(hPict_[GaugeLOW], transGaugeUI_);
		Image::Draw(hPict_[GaugeLOW]);
	}
	else {
		Image::SetTransform(hPict_[GaugeMAIN], transGaugeUI_);
		Image::Draw(hPict_[GaugeMAIN]);
	}


}

//�J��
void HpGaugeUI::ChildRelease()
{
}