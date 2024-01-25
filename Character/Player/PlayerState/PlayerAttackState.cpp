#include "PlayerAttackState.h"
#include "../../BoxCollider.h"
#include "../Player.h"

namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
}

void PlayerAttackState::Update(Player* player)
{

	//�U���A�j���[�V�������n�߂Ĉ�莞�ԗ�������Idle�ɖ߂�
	time_++;

	//�U���͉���u�Ԃɏ����O�ɏo�ăW�����v�ł��Ȃ��Ȃ�݂����Ȋ����ɂ������B�X�e�B�b�N�t�@�C�g���Q�[���݂����Ȋ���

	//�U�����I�������U���p�̃R���C�_�[��j������state��߂�
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
