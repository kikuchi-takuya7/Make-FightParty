#include "CharacterAI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"

CharacterAI::CharacterAI() :pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr)
{
}

CharacterAI::CharacterAI(Enemy* enemy, NavigationAI* naviAI) :pNavigationAI_(naviAI),pMetaAI_(nullptr), pEnemy_(enemy)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	//pNavigationAI_->Initialize();

	//pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());
	isStay_ = false;
	stayTime_ = 0;
}

void CharacterAI::Release()
{

}

//������
void CharacterAI::MoveEnemy()
{

	//��莞�Ԏ~�܂�
	if (isStay_) {
		stayTime_++;
		if (stayTime_ <= 60) {
			return;
		}
	}

	//NavigationAI�Ɍ������ׂ������𕷂�
	XMFLOAT3 fMove = pNavigationAI_->Astar();

	//�ڕW�n�_�ɒ������ꍇ�A��莞�Ԏ~�܂�.�U���������ɂ��~�܂肽��
	if (fMove == ZERO_FLOAT3) {
		Stay();
	}

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

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

	}

}

void CharacterAI::Stay()
{
	isStay_ = true;//����U�����肪�L�������Ŗ������[�v����Ƃ�����
	stayTime_ = 0;
}

void CharacterAI::Attack()
{
}
