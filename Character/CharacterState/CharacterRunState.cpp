#include "CharacterRunState.h"
#include "../../../Engine/Input.h"
#include "../Character.h"

namespace {
	//130~150：歩行推移 150~190：歩行モーション 190~210：Idle推移
	const float RUN_TRANSITION_START_FRAME = 130;
	const float RUN_TRANSITION_END_FRAME = 210;
	const float RUN_START_FRAME = 150;
	const float RUN_END_FRAME = 190;
}

CharacterRunState::CharacterRunState(Character* character, int model):CharacterState(character, model)
{
}

void CharacterRunState::Update()
{


	//Movecharacter(character);

	int nowFrame = Model::GetAnimFrame(hCharacterModel_);
	if (nowFrame >= RUN_TRANSITION_END_FRAME) {
		Model::SetAnimFrame(hCharacterModel_, RUN_START_FRAME, RUN_END_FRAME, 1);
	}

	HandleInput();
}

void CharacterRunState::HandleInput()
{
}

void CharacterRunState::Enter()
{
	Model::SetAnimFrame(hCharacterModel_, RUN_START_FRAME, RUN_END_FRAME, 1);
}

void CharacterRunState::Leave()
{
}