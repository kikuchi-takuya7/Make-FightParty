#include "CharacterDieState.h"
#include "../Character.h"

void CharacterDieState::Update(Character* character)
{

	//Character->SetPosition(1, 1, 0);
	
	//HandleInput(Character);
}

void CharacterDieState::HandleInput(Character* character)
{
}

void CharacterDieState::Enter(Character* character)
{
	character->EraseCollider(ATTACK);
	character->EraseCollider(BODY);

	character->TellStatus();
	
}
