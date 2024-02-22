#include "CharacterKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Character.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
	const float KNOCKBACK_SPEED = 0.05f;//どのくらいの速度でノックバックするか
}

void CharacterKnockBackState::Update(Character* character)
{

	flame_++;

	character->KnockBackUpdate(KNOCKBACK_SPEED);

	/*if (characterPos == lastPoint_) {
		character->ChangeState(character_IDLE);
		character->ChangeKnockBack(false);
	}*/

	//喰らい硬直が終わったら
	if (flame_ >= KNOCKBACK_RIGIDITYFLAME) {
		character->ChangeState(character_IDLE);
	}

	HandleInput(character);
}

void CharacterKnockBackState::HandleInput(Character* character)
{
}

void CharacterKnockBackState::Enter(Character* character)
{
	flame_ = 0;
	character->KnockBackEnter(KNOCKBACK_DISTANCE);

}

