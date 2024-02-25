#include "RankingGaugeUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include<assert.h>


namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float PINCH = 20.0f;
}


//�R���X�g���N�^
RankingGaugeUI::RankingGaugeUI(GameObject* parent)
	: GaugeBase(parent, "RankingGaugeUI")
{
}

//�f�X�g���N�^
RankingGaugeUI::~RankingGaugeUI()
{
}

//������
void RankingGaugeUI::ChildInitialize()
{

	std::string str[GAUGE_NUM] = { "WinGauge","KillGauge","TrapKillGauge"};

	//�摜�f�[�^�̃��[�h
	for (int i = 0; i < GAUGE_NUM; i++) {

		std::string dir = "Image/RankingUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	pText_ = new Text;
	pText_->Initialize();
}

//�X�V
void RankingGaugeUI::ChildUpdate()
{
	/*animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;*/
}

//�`��
void RankingGaugeUI::ChildDraw()
{

	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);

	pText_->Draw(transform_.position_.x, transform_.position_.y, name_.c_str());
}

//�J��
void RankingGaugeUI::ChildRelease()
{
}

bool RankingGaugeUI::IsEndAnim()
{
	return (animGauge_ == nowGauge_);
}
