#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

void PlayerKnockBackState::Update(Player* player)
{

	time_++;

	//“G‚ÌŒü‚¢‚Ä‚¢‚é•ûŒü‚ª—~‚µ‚¢.‚Å‚«‚ê‚ÎEnter‚ÌŽž“_‚Å”ò‚Î‚³‚ê‚éÀ•W‚ðŽæ‚Á‚Ä‚¨‚¢‚ÄA‚»‚±‚É’…‚¢‚½‚ç“®‚¯‚é‚Á‚ÄŠ´‚¶‚É‚µ‚½‚¢BŠÉ‹}•t‚¯‚Ä

	XMFLOAT3 playerPos = player->GetPosition();
	playerPos.x += 0.1f;
	player->SetPosition(playerPos);

	if (time_ >= 30) {
		player->ChangeState(PLAYER_IDLE);
		player->ChangeKnockBack(false);
	}

	HandleInput(player);
}

void PlayerKnockBackState::HandleInput(Player* player)
{
}

void PlayerKnockBackState::Enter(Player* player)
{
	time_ = ZERO;
	player->ChangeKnockBack(true);
}
