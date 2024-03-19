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
}

CharacterAI::CharacterAI(GameObject* parent)
	:AI(parent, "CharacterAI"), pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr),pText_(new Text)
{
}

CharacterAI::CharacterAI(GameObject* parent, Enemy* enemy, NavigationAI* naviAI)
	:AI(parent, "CharacterAI"), pNavigationAI_(naviAI), pMetaAI_(nullptr), pEnemy_(enemy), pText_(new Text)
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
	
	if (distance <= 2.0f) {
		pEnemy_->ChangeState(ATTACK);
	}
}

// �N���G�C�g���[�h�őI�������I�u�W�F�N�g���ړ�������֐�
// �߂�l�F�����������Transform
Transform CharacterAI::MoveSelectObject()
{
	//�X�e�[�W���̂ǂ����Ƀ����_���Œu��
	Transform objTrans;
	objTrans.position_.x = rand() % 29;
	objTrans.position_.z = rand() % 29;

	objTrans.rotate_.y = rand() % 4 * 90;

	return objTrans;
}

