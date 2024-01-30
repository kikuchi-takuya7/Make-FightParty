#include "PlayerDieState.h"
#include "../Player.h"

void PlayerDieState::Update(Player* player)
{

	//player->SetPosition(1, 1, 0);
	
	//HandleInput(player);
}

void PlayerDieState::HandleInput(Player* player)
{
}

void PlayerDieState::Enter(Player* player)
{

	player->ClearCollider();
	Status status = player->GetStatus();
	status.dead = true;
	player->SetStatus(status);
}
