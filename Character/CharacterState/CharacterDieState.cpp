#include "CharacterDieState.h"
#include "../Character.h"

CharacterDieState::CharacterDieState(Character* character) :CharacterState(character)
{
}

void CharacterDieState::Update()
{

}

void CharacterDieState::HandleInput()
{
}

void CharacterDieState::Enter()
{
	pCharacter_->EraseCollider(COLLIDER_ATTACK);
	pCharacter_->EraseCollider(COLLIDER_BODY);

	pCharacter_->TellStatus();
	
}

void CharacterDieState::Leave()
{
}
