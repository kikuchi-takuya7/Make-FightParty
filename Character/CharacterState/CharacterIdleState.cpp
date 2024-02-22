#include "CharacterIdleState.h"
#include "CharacterStateManager.h"
#include "../Character.h"

void CharacterIdleState::Update(Character* character)
{



	HandleInput(character);
}


void CharacterIdleState::HandleInput(Character* character)
{

	

	if (Input::IsKeyDown(DIK_F)) {
		character->ChangeState(ATTACK);
	}
	
	if (Input::IsKeyDown(DIK_SPACE)) {
		character->ChangeState(JUMP);
	}

}

void CharacterIdleState::Enter(Character* character)
{

}
