#include "PlayerAttackState.h"
#include "../../BoxCollider.h"
#include "../Player.h"

namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

void PlayerAttackState::Update(Player* player)
{

	//攻撃アニメーションを始めて一定時間立ったらIdleに戻す
	time_++;

	//攻撃は殴る瞬間に少し前に出てジャンプできなくなるみたいな感じにしたい。スティックファイト座ゲームみたいな感じ

	//攻撃が終わったら攻撃用のコライダーを破棄してstateを戻す
	if (time_ >= 60) {
		player->DeleteCollider(ColliderAttackType::COLLIDER_ATTACK);
		PlayerStateManager::playerState_ = PlayerStateManager::playerIdleState_;
		PlayerStateManager::playerState_->Enter(player);
	}

	HandleInput(player);
}

void PlayerAttackState::HandleInput(Player* player)
{
}

void PlayerAttackState::Enter(Player* player)
{
	time_ = 0;
	player->SetAttackCollider();
}
