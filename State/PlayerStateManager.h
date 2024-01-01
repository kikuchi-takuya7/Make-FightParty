#pragma once
#include "../Player/Player.h"
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

	PlayerState playerState_;
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ�
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerRunState* playerRunState_;

	virtual void Update(Player* player) override;

	virtual void HandleInput(Player* player) override;

	virtual void Enter(Player* player) override;
};

