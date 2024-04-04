#include "CharacterAttackState.h"
#include "../../BoxCollider.h"
#include "../Character.h"
#include "../../Engine/Audio.h"

//θ
namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
	const int ATTACK_RIGIDITYFLAME = 60;//U±t[

	const int MOTION_START_FRAME = 60;
	const int MOTION_END_FRAME = 130;
	const int ATTACK_START_FRAME = 90;
	const int ATTACK_END_FRAME = 110;
}

CharacterAttackState::CharacterAttackState(Character* character, int model) :CharacterState(character, model), settedCollision_(false),hAudio_(-1)
{
	hAudio_ = Audio::Load("Audio/SE/Attack.wav", false);
	assert(hAudio_ >= ZERO);
	Audio::Stop(hAudio_);
}

void CharacterAttackState::Update()
{

	int nowFrame = Model::GetAnimFrame(hCharacterModel_);

	if (nowFrame >= ATTACK_START_FRAME && settedCollision_ == false) {
		settedCollision_ = true;
		pCharacter_->SetAttackCollider();
		Audio::Play(hAudio_);
	}

	if (nowFrame >= ATTACK_END_FRAME) {
		pCharacter_->EraseCollider(ColliderAttackType::COLLIDER_ATTACK);
	}

	//UͺIνΑ½ηUpΜRC_[πjό΅Δstateπί·
	if (nowFrame >= MOTION_END_FRAME) {
		pCharacter_->EraseCollider(ColliderAttackType::COLLIDER_ATTACK);
		pCharacter_->ChangeState(IDLE);
	}

	HandleInput();
}

void CharacterAttackState::HandleInput()
{
}

void CharacterAttackState::Enter()
{
	settedCollision_ = false;
	Model::SetAnimFrame(hCharacterModel_, MOTION_START_FRAME, MOTION_END_FRAME, 1);
}

void CharacterAttackState::Leave()
{
	pCharacter_->EraseCollider(COLLIDER_ATTACK);
}
