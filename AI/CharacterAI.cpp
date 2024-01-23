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
}

void CharacterAI::Release()
{

}

//������
void CharacterAI::MoveEnemy()
{

	//���������_������������l���Ă�����
	/*pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());*/

	XMFLOAT3 fMove = Float3Add(pEnemy_->GetPosition(), pNavigationAI_->Astar());

	pEnemy_->SetPosition(fMove);

	//�����������x�N�g�����m�F
	XMVECTOR vMove = XMLoadFloat3(&fMove);

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

		//pAttackCollision_->SetRotate(XMFLOAT3(ZERO, degree, ZERO));

	}

}
