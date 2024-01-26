#include "PlayerIdleState.h"
#include "PlayerStateManager.h"
#include "../Player.h"

void PlayerIdleState::Update(Player* player)
{



	HandleInput(player);
}


void PlayerIdleState::HandleInput(Player* player)
{

	

	if (Input::IsKeyDown(DIK_F)) {
		player->ChangeState(PLAYER_ATTACK);
	}
	
	if (Input::IsKeyDown(DIK_SPACE)) {
		player->ChangeState(PLAYER_JUMP);
	}

}

void PlayerIdleState::Enter(Player* player)
{
}
