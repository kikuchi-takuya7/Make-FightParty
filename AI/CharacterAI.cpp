#include "CharacterAI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/CharacterState/CharacterState.h"
#include "../Engine/Text.h"

namespace {
	//�\�����錻�݂�AI�̏��
	XMFLOAT3 TEXT_POS = { -70,50,ZERO };
	std::string text[TEXT_NUM] = { ":Randam",":No1",":Counter"};

	//�f�t�H���g�̍U������˒�
	const float DEFAULT_ATTACK_RANGE = 2.0f;

	//�f�t�H���g�̍U������m��(��)
	const int DEFAULT_ATTACE_PROBABILITY = 10;

	//�f�t�H���g�̖��t���[�����ɒǉ������U���m��
	const int DEFAULT_ADD_PROBABILITY = 2;

	//�X�e�[�W�ɐݒu����ő���W�A�Z�b�e�B���O���[�h�Ŏg��
	const int SETTING_MAXPOS_X = 29;
	const int SETTING_MAXPOS_Y = 29;
}

CharacterAI::CharacterAI(GameObject* parent)
	:AI(parent, "CharacterAI"), pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr), attackRange_(DEFAULT_ATTACK_RANGE), attackProbability_(DEFAULT_ATTACE_PROBABILITY), pText_(new Text)
{
}

CharacterAI::CharacterAI(GameObject* parent, Enemy* enemy, NavigationAI* naviAI)
	:AI(parent, "CharacterAI"), pNavigationAI_(naviAI), pMetaAI_(nullptr), pEnemy_(enemy), attackRange_(DEFAULT_ATTACK_RANGE), attackProbability_(DEFAULT_ATTACE_PROBABILITY), pText_(new Text)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	//pEnemy_->GetStatus().playerName;
	pText_->Initialize();
}

void CharacterAI::Draw()
{
	std::string str = pEnemy_->GetStatus().playerName + text[target_.mode];
	int tmp = pEnemy_->GetObjectID();

	pText_->Draw(TEXT_POS.x, TEXT_POS.y * tmp, str.c_str());
}

void CharacterAI::Release()
{

}

// �_���ׂ��G��MetaAI�ɕ����֐�
void CharacterAI::AskTarget()
{
	//�_���G��ID�����߂Ă��炤
	target_ = pMetaAI_->Targeting(pEnemy_->GetObjectID());
}

// MetaAI�ɏ���`����֐�
void CharacterAI::TellStatus()
{
	pMetaAI_->ChangeStatus(pEnemy_->GetObjectID(), pEnemy_->GetStatus());
	pMetaAI_->DecidedWinner();
}


// NavigationAI�ɍs���ׂ��ꏊ�𕷂��A�ړ�����֐�
void CharacterAI::MoveEnemy()
{

	//NavigationAI�Ɍ������ׂ������𕷂�
	XMFLOAT3 fMove = pNavigationAI_->Astar(pEnemy_->GetObjectID(), target_.ID);

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

	if (fMove == ZERO_FLOAT3) {
		pEnemy_->ChangeState(IDLE);
	}

	//�����������x�N�g�����m�F
	XMVECTOR vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);
	float length = Length(vMove);

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		pEnemy_->SetRotateY(degree);

		pEnemy_->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

		pEnemy_->ChangeState(RUN);

	}
}

// �U�����邩�ǂ������w������֐�
void CharacterAI::IsAttack()
{
	//�_�����Ƃ��Ă�G������ł���A�^�[�Q�b�g��ς���
	if (pMetaAI_->GetCharacterStatus(target_.ID).dead) {
		AskTarget();
	}

	float distance = pNavigationAI_->Distance(pEnemy_->GetObjectID(), target_.ID);
	
	//�^�[�Q�b�g���˒����Ȃ�
	if (distance <= attackRange_) {
		
		//�m���ōU������(�P�ʂ����̈�100���g��)
		if (rand() % 100 < attackProbability_) {
			pEnemy_->ChangeState(ATTACK);
			attackProbability_ = startAttackProbability_;
			return;
		}
		
		//�U������Ȃ������玟�U������m���𑝂₷
		attackProbability_ += DEFAULT_ADD_PROBABILITY;
	}
}

// �N���G�C�g���[�h�őI�������I�u�W�F�N�g���ړ�������֐�
// �߂�l�F�����������Transform
Transform CharacterAI::MoveSelectObject()
{
	//�X�e�[�W���̂ǂ����Ƀ����_���Œu��
	Transform objTrans;
	objTrans.position_.x = rand() % SETTING_MAXPOS_X;
	objTrans.position_.z = rand() % SETTING_MAXPOS_Y;

	//360�x�̂����㉺���E�����_���ȕ����ɂȂ�悤�ɂ��邽�߁A0~3�̒l��90�������Ă��܂�
	objTrans.rotate_.y = rand() % 4 * 90;

	return objTrans;
}

