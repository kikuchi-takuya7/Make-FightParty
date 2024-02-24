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

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	pText_->Draw(transform_.position_.x, transform_.position_.y, "test");
}

//�J��
void RankingGaugeUI::ChildRelease()
{
}

bool RankingGaugeUI::IsEndAnim()
{
	return (animGauge_ == nowGauge_);
}
