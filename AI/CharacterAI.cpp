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

}

//動かす
void CharacterAI::MoveEnemy()
{

	//浮動小数点分もしっかり考えておこう
	pNavigationAI_->SetEnemyPos(pEnemy_->GetPosition());

	XMFLOAT3 test = Float3Add(pEnemy_->GetPosition(), pNavigationAI_->Astar());

	pEnemy_->SetPosition(test);

}
