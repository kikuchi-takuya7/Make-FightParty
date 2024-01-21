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

	XMFLOAT3 test = Float3Add(pEnemy_->GetPosition(), pNavigationAI_->Astar());

	pEnemy_->SetPosition(test);

}
