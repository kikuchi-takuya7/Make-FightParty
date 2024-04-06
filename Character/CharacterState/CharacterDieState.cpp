#include "CharacterDieState.h"
#include "../Character.h"

namespace {
	const int DIE_START_FRAME = 250;
	const int DIE_END_FRAME = 340 + 9999999;//���񂾂��Ƃ����Ǝ~�܂��ĂĂ��炤�Bif�����g��Ȃ��Ă������悤��

	//�A�j���[�V������1�t���[�����ɐi�ޑ��x
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
