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

	

	if (Input::IsKeyDown(DIK_F)) {
		pCharacter_->ChangeState(ATTACK);
	}
	
	if (Input::IsKeyDown(DIK_SPACE)) {
		pCharacter_->ChangeState(JUMP);
	}

}

void CharacterIdleState::Enter()
{

}

void CharacterIdleState::Leave()
{
}
