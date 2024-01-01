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
/// player‚Ìó‘Ô‚ğŠÇ—‚·‚é
/// </summary>
class PlayerStateManager : public PlayerState
{

public:

	PlayerState playerState_;
	
	//‚¢‚¿‚¢‚¿state‚ğnew‚µ‚Ä•Ï‚¦‚é‚æ‚è–‘O‚ÉÃ“I‚É•Û‚µ‚Ä‚¨‚¯‚Îƒƒ‚ƒŠ‚Ìß–ñ‚É‚È‚é
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerRunState* playerRunState_;

	virtual void Update(Player* player) override;

	virtual void HandleInput(Player* player) override;

	virtual void Enter(Player* player) override;
};

