#include "PlayerDieState.h"
#include "../Player/Player.h"

void PlayerDieState::Update(Player* player)
{

	player->ClearCollider();
	
	
	HandleInput(player);
}

void PlayerDieState::HandleInput(Player* player)
{
}

void PlayerDieState::Enter(Player* player)
{
}
