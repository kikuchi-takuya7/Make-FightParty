#include "CharacterJumpState.h"
#include "CharacterStateManager.h"
#include "../Character.h"

namespace {
	const float JUMP_VELOCITY = 1.0f;
	const float GRAVITY = 0.1f;
}

CharacterJumpState::CharacterJumpState(Character* character):CharacterState(character)
{
}

void CharacterJumpState::Update()
{
	//�W�����v������
	XMFLOAT3 characterPos = pCharacter_->GetPosition();
	characterPos.y += velocity_;
	velocity_ -= GRAVITY;

	//�����n�ʂɒ�������state��ς���
	if (characterPos.y <= ZERO) {
		characterPos.y = 0;

		pCharacter_->ChangeState(IDLE);
	}

	pCharacter_->SetPosition(characterPos);

	

	HandleInput();
}

void CharacterJumpState::HandleInput()
{
	/*if (Input::IsKeyDown(DIK_Q)) {
		characterStateManager::characterState_ = characterStateManager::characterDieState_;
		characterStateManager::characterState_->Enter(pCharacter_);
	}*/

	if (Input::IsKeyDown(DIK_F)) {
		pCharacter_->ChangeState(ATTACK);
	}
}

void CharacterJumpState::Enter()
{

	//�����o�ϐ�������������
	velocity_ = JUMP_VELOCITY;

}

void CharacterJumpState::Leave()
{
}
