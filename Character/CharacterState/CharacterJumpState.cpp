#include "CharacterJumpState.h"
#include "CharacterStateManager.h"
#include "../Character.h"

namespace {
	const float JUMP_VELOCITY = 1.0f;
	const float GRAVITY = 0.1f;
}

void CharacterJumpState::Update(Character* character)
{
	//ジャンプさせる
	XMFLOAT3 characterPos = character->GetPosition();
	characterPos.y += velocity_;
	velocity_ -= GRAVITY;

	//もし地面に着いたらstateを変える
	if (characterPos.y <= ZERO) {
		characterPos.y = 0;

		character->ChangeState(character_IDLE);
	}

	character->SetPosition(characterPos);

	

	HandleInput(character);
}

void CharacterJumpState::HandleInput(Character* character)
{
	/*if (Input::IsKeyDown(DIK_Q)) {
		characterStateManager::characterState_ = characterStateManager::characterDieState_;
		characterStateManager::characterState_->Enter(character);
	}*/

	if (Input::IsKeyDown(DIK_F)) {
		character->ChangeState(ATTACK);
	}
}

void CharacterJumpState::Enter(Character* character)
{

	//メンバ変数を初期化する
	velocity_ = JUMP_VELOCITY;

}
