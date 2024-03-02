#include "RankingGaugeUI.h"
#include "../../Engine/Image.h"
#include "../../Engine/Text.h"
#include "../../Engine/Input.h"
#include "WinScore.h"
#include "KillScore.h"
#include "TrapKillScore.h"
#include<assert.h>


namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float ONE_GAUGE_LENGTH = 184;

	//�X�R�A���̃Q�[�W�̑傫��������
	const float SCORE_DIFF[GAUGE_NUM] = { ONE_GAUGE_LENGTH,ONE_GAUGE_LENGTH / 2,ONE_GAUGE_LENGTH / 4 };

	const float START_DIFF[GAUGE_NUM] = { ZERO,ONE_GAUGE_LENGTH / 2,ONE_GAUGE_LENGTH - ONE_GAUGE_LENGTH / 4 };

	//���ꂢ�݂˂���
	const int TEST_SCORE = 100;

	const XMFLOAT3 GAUGE_SIZE = { 0.72f,0.5f,ZERO };
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

	gaugePos_ = transGaugeUI_.position_;

	pText_ = new Text;
	pText_->Initialize();
}

//�X�V
void RankingGaugeUI::ChildUpdate()
{

	if (gauge_.empty()) {
		return;
	}

	// ���̃X�R�A�Q�[�W�̃A�j���[�V�������I������玟�����\��̃Q�[�W��ǉ�����
	if (gauge_.back().first->IsEndAnim() == true && nextScore_.empty() == false) {
		CreateScore(nextScore_.front());
		nextScore_.pop();
	}
}

//�`��
void RankingGaugeUI::ChildDraw()
{
	XMFLOAT3 textPos = transform_.position_;
	textPos.x -= 130;
	pText_->Draw(textPos.x, textPos.y, name_.c_str());
}

//�J��
void RankingGaugeUI::ChildRelease()
{
}

// �ǉ�����X�R�A������
// �����F�ǉ�����X�R�A�Q�[�W
void RankingGaugeUI::PushScore(SCOREGAUGELIST score)
{
	//�ŏ����������ɓ����
	if (gauge_.empty()) {
		CreateScore(score);
		return;
	}

	nextScore_.push(score);
}

// �S�ẴQ�[�W�̃A�j���[�V�������I����Ă��邩�ǂ���
// �߂�l�F�S�ďI����Ă�����true
bool RankingGaugeUI::IsAllEndAnim()
{
	for (int i = 0; i < gauge_.size(); i++) {
		if (gauge_.at(i).first->IsEndAnim() == false) {
			return false;
		}
	}

	if (nextScore_.empty() == false)
		return false;

	return true;
}

// �Q�[�W�̃A�j���[�V�����𑦍��ɏI��点��i��Q�[�W�������j
void RankingGaugeUI::AllEndAnim()
{
	for (int i = ZERO; i < gauge_.size(); i++) {
		gauge_.at(i).first->EndAnim();
	}
}

// �\������X�R�A�̃C���X�^���X�����
// �����F�C���X�^���X�����X�R�A�Q�[�W
void RankingGaugeUI::CreateScore(SCOREGAUGELIST score)
{
	//�ŏ��̃Q�[�W�����摜�̌��ԕ��𖄂߂�
	if (gauge_.empty())
		gaugePos_.x -= START_DIFF[score];
	else
		gaugePos_.x += SCORE_DIFF[score];

	switch (score)
	{
	case WIN_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<WinScore>(this), score));
		break;

	case KILL_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<KillScore>(this), score));
		break;

	case TRAP_KILL_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<TrapKillScore>(this), score));
		break;

	default:
		return;
	}

	gauge_.back().first->SetGauge(TEST_SCORE, TEST_SCORE);
	gauge_.back().first->Enter();
	gauge_.back().first->SetScale(GAUGE_SIZE);
	gauge_.back().first->SetPosition(SpriteToFloatX(transform_.position_.x + gaugePos_.x), SpriteToFloatY(transform_.position_.y), ZERO);
}
