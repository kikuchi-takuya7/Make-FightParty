#include "CharacterAI.h"

CharacterAI::CharacterAI() :pNavigationAI_(new NavigationAI), pMetaAI_(nullptr), pEnemy_(nullptr)
{
}

CharacterAI::CharacterAI(Enemy* enemy) :pNavigationAI_(new NavigationAI),pMetaAI_(nullptr), pEnemy_(enemy)
{
}

CharacterAI::~CharacterAI()
{
}

void CharacterAI::Initialize()
{
	pNavigationAI_->Initialize();

	pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());
}

void CharacterAI::Release()
{

	pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());

}

//“®‚©‚·
void CharacterAI::MoveEnemy()
{
	pEnemy_->SetPosition(pEnemy_->GetPosition() + pNavigationAI_->Astar());
}
