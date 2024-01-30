#include "CharacterAI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"

CharacterAI::CharacterAI(GameObject* parent)
	:AI(parent, "CharacterAI"), pNavigationAI_(nullptr), pMetaAI_(nullptr), pEnemy_(nullptr)
{
}

CharacterAI::CharacterAI(GameObject* parent, Enemy* enemy, NavigationAI* naviAI)
	:AI(parent, "CharacterAI"), pNavigationAI_(naviAI), pMetaAI_(nullptr), pEnemy_(enemy)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	

}

void CharacterAI::Release()
{

}

void CharacterAI::AskTarget()
{
	//�_���G��ID�����߂Ă��炤
	targetID_ = pMetaAI_->Targeting(pEnemy_->GetObjectID());
}

//������
void CharacterAI::MoveEnemy()
{

	//NavigationAI�Ɍ������ׂ������𕷂�
	XMFLOAT3 fMove = pNavigationAI_->Astar(pEnemy_->GetObjectID(), targetID_);

	pEnemy_->SetPosition(Float3Add(pEnemy_->GetPosition(), fMove));

	if (fMove == ZERO_FLOAT3) {
		pEnemy_->ChangeState(ENEMY_IDLE);
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

		//pEnemy_->ChangeState(ENEMY_RUN);

	}

}

void CharacterAI::Attack()
{

}

void CharacterAI::IsAttack()
{
	float distance = pNavigationAI_->Distance(pEnemy_->GetObjectID(), targetID_);
	
	if (distance <= 2.0f) {
		pEnemy_->ChangeState(ENEMY_ATTACK);
	}
}

void CharacterAI::TellStatus()
{
	pMetaAI_->ChangeStatus(pEnemy_->GetObjectID(), pEnemy_->GetStatus());
}
