#include "CharacterAttackState.h"
#include "../../BoxCollider.h"
#include "../Character.h"

//定数
namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
	const int ATTACK_RIGIDITYFLAME = 60;//攻撃持続フレーム

}

CharacterAttackState::CharacterAttackState(Character* character) :CharacterState(character)
{
}

void CharacterAttackState::Update()
{

	//攻撃アニメーションを始めて一定時間立ったらIdleに戻す
	flame_++;

	//攻撃は殴る瞬間に少し前に出てジャンプできなくなるみたいな感じにしたい。スティックファイト座ゲームみたいな感じ

	//攻撃が終わったら攻撃用のコライダーを破棄してstateを戻す
	if (flame_ >= ATTACK_RIGIDITYFLAME) {
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
	flame_ = ZERO;
	pCharacter_->SetAttackCollider();
}

void CharacterAttackState::Leave()
{
	pCharacter_->EraseCollider(COLLIDER_ATTACK);
}
