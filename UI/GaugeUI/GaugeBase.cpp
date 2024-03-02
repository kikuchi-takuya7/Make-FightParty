#include "GaugeBase.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include<assert.h>

namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;
}


//�R���X�g���N�^
GaugeBase::GaugeBase(GameObject* parent, std::string name)
	: GameObject(parent, name), maxGauge_(ZERO), nowGauge_(ZERO)
{
}

//�f�X�g���N�^
GaugeBase::~GaugeBase()
{
}

//������
void GaugeBase::Initialize()
{
	ChildInitialize();
}

//�X�V
void GaugeBase::Update()
{
	if (!IsEntered()) {
		return;
	}

	ChildUpdate();

	animGauge_ = (animGauge_ * 9 + nowGauge_) / 10;
	if (animGauge_ >= nowGauge_ - 0.1f && animGauge_ <= nowGauge_) {
		animGauge_ = nowGauge_;
	}

	if (Input::IsKeyDown(DIK_P)) {
		nowGauge_ = maxGauge_;
	}
}

//�`��
void GaugeBase::Draw()
{

	if (IsVisibled()) {
		return;
	}

	transGaugeUI_ = transform_;
	transGaugeUI_.scale_.x = ((float)animGauge_ / (float)maxGauge_) * transform_.scale_.x;

	ChildDraw();

}

//�J��
void GaugeBase::Release()
{
}

// �Q�[�W�̒l���Z�b�g����
// �����P�F���̒l
// �����Q�F�l�̍ő�l
void GaugeBase::SetGauge(int nowGaugeBase, int maxGaugeBase)
{
	nowGauge_ = nowGaugeBase;
	maxGauge_ = maxGaugeBase;
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���
	
}

// ���̃Q�[�W�̒l��ς���
// �����F���̒l
void GaugeBase::SetNowGauge(int nowGaugeBase)
{
	nowGauge_ = nowGaugeBase;

	//���炩��HP�𓮂������߂ɏ��X�ɒl��ς���
	animGauge_ = (animGauge_ * 9 + nowGaugeBase) / 10; //animHp��9��nowHp��1�����瑫����10�Ŋ���

}

// �l�������Z����
// �����F���Z�������l
void GaugeBase::AddValue(float v)
{
	nowGauge_ += v;
	if (nowGauge_ < ZERO)
		nowGauge_ = ZERO;
	else if (nowGauge_ > maxGauge_)
		nowGauge_ = maxGauge_;
}

// �l�������̒l�ɕύX����
// �����F�ύX��̒l
void GaugeBase::SetValue(float v)
{
	assert(v >= MIN && v <= MAX);

	nowGauge_ = v;
	if (nowGauge_ < ZERO)
		nowGauge_ = ZERO;
	else if (nowGauge_ > maxGauge_)
		nowGauge_ = maxGauge_;
}

//���݂̃Q�[�W�̒l���擾
//�߂�l�FnowGauge�̒l
float GaugeBase::GetValue()
{
	return nowGauge_;
}
// �A�j���[�V�������I��������ǂ���
// �߂�l�F�I����Ă�����turue
bool GaugeBase::IsEndAnim()
{
	return (animGauge_ == nowGauge_);
}

//�A�j���[�V�����𑦍��ɏI��点��֐�
void GaugeBase::EndAnim()
{
	nowGauge_ = maxGauge_;
	animGauge_ = maxGauge_;
}
