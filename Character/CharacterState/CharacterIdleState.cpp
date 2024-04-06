#include "CharacterIdleState.h"
#include "CharacterStateManager.h"
#include "../Character.h"

namespace {
	const int WAIT_START_FRAME = ZERO;
	const int WAIT_END_FRAME = 60;

	//�A�j���[�V������1�t���[�����ɐi�ޑ��x
	const int ANIMATION_SPEED = 1;
}

CharacterIdleState::CharacterIdleState(Character* character, int model) :CharacterState(character, model)
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
	Model::SetAnimFrame(hCharacterModel_, WAIT_START_FRAME, WAIT_END_FRAME, ANIMATION_SPEED);
}

void CharacterIdleState::Leave()
{
}
