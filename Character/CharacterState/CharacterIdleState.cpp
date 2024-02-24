#include "CharacterIdleState.h"
#include "CharacterStateManager.h"
#include "../Character.h"

CharacterIdleState::CharacterIdleState(Character* character) :CharacterState(character)
{
}

void CharacterIdleState::Update()
{



	HandleInput();
}


void CharacterIdleState::HandleInput()
{

	

	

}

void CharacterIdleState::Enter()
{

}

void CharacterIdleState::Leave()
{
}
