#include "CharacterDieState.h"
#include "../Character.h"

namespace {
	const int DIE_START_FRAME = 250;
	const int DIE_END_FRAME = 340 + 9999999;//死んだあとずっと止まっててもらう。if文を使わなくてもいいように

	//アニメーションの1フレーム毎に進む速度
	const int ANIMATION_SPEED = 1;
}

CharacterDieState::CharacterDieState(Character* character, int model) :CharacterState(character, model)
{
}

void CharacterDieState::Update()
{

	/*int nowFrame = Model::GetAnimFrame(hCharacterModel_);
	if (nowFrame >= DIE_END_FRAME) {
		pCharacter_->Leave();
		Model::SetAnimFrame(hCharacterModel_, DIE_END_FRAME, DIE_END_FRAME, 0);
	}*/
}

void CharacterDieState::HandleInput()
{
}

void CharacterDieState::Enter()
{
	pCharacter_->EraseCollider(COLLIDER_ATTACK);
	pCharacter_->EraseCollider(COLLIDER_BODY);

	pCharacter_->TellStatus();

	Model::SetAnimFrame(hCharacterModel_, DIE_START_FRAME, DIE_END_FRAME, ANIMATION_SPEED);
	
	
}

void CharacterDieState::Leave()
{
	int i = 0;
}
