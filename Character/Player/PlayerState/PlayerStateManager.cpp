#include "PlayerStateManager.h"
#include "../Player.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��
//PlayerAttackState* PlayerStateManager::playerAttackState_ = new PlayerAttackState;
//PlayerDieState* PlayerStateManager::playerDieState_ = new PlayerDieState;
//PlayerIdleState* PlayerStateManager::playerIdleState_ = new PlayerIdleState;
//PlayerJumpState* PlayerStateManager::playerJumpState_ = new PlayerJumpState;
//PlayerRunState* PlayerStateManager::playerRunState_ = new PlayerRunState;

//PlayerState* PlayerStateManager::playerState_ = playerIdleState_;

PlayerStateManager::PlayerStateManager()
{
	playerAttackState_ = new PlayerAttackState;
	playerDieState_ = new PlayerDieState;
	playerIdleState_ = new PlayerIdleState;
	playerJumpState_ = new PlayerJumpState;
	playerKnockBackState_ = new PlayerKnockBackState;
	playerRunState_ = new PlayerRunState;

	playerState_ = playerIdleState_;

	nowState_ = IDLE;
}

void PlayerStateManager::Update(Player* player)
{

	//�����ɋ��ʏ����������Bstate�̏��������s���Ă��炩���s����O���͌�Ō��߂�

	//�m�b�N�o�b�N������Ȃ���Έړ��ł���悤��
	if (player->IsKnockBack() == false) {

		player->MoveCharacter();
	}

	playerState_->Update(player);

}

void PlayerStateManager::HandleInput(Player* player)
{
}

void PlayerStateManager::Enter(Player* player)
{
}

void PlayerStateManager::ChangeState(PlayerStatePattern nextState, Player* player)
{

	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	switch (nextState)
	{
	case ATTACK:
		playerState_ = playerAttackState_;
		break;

	case DIE:
		playerState_ = playerDieState_;
		break;

	case IDLE:
		playerState_ = playerIdleState_;
		break;

	case JUMP:
		playerState_ = playerJumpState_;
		break;

	case KNOCKBACK:
		playerState_ = playerKnockBackState_;
		break;

	case RUN:
		playerState_ = playerRunState_;
		break;

	case NUM:

	default:
		return;
		break;
	}

	playerState_->Enter(player);
	
}
