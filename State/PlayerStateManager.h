#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

class Player;

/// <summary>
/// player�̏�Ԃ��Ǘ�����
/// </summary>
class PlayerStateManager : public PlayerState
{

public:

	static PlayerState* playerState_;
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ�
	static PlayerAttackState* playerAttackState_;
	static PlayerDieState* playerDieState_;
	static PlayerIdleState* playerIdleState_;
	static PlayerJumpState* playerJumpState_;
	static PlayerRunState* playerRunState_;

	PlayerStateManager();

	virtual void Update(Player* player) override;

	virtual void HandleInput(Player* player) override;

	virtual void Enter(Player* player) override;

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(PlayerState* nextState, Player* player);
};

