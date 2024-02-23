#include "PlayerStateManager.h"
#include "../Player.h"

PlayerStateManager::PlayerStateManager()
{
	playerAttackState_ = new PlayerAttackState;
	playerDieState_ = new PlayerDieState;
	playerIdleState_ = new PlayerIdleState;
	playerJumpState_ = new PlayerJumpState;
	playerKnockBackState_ = new PlayerKnockBackState;
	playerRunState_ = new PlayerRunState;

	playerState_ = playerIdleState_;
}

void PlayerStateManager::Update(Player* player)
{

	//攻撃してる時に攻撃喰らった時に攻撃判定を消す用。それぞれのEnterに置いた方がいいかな
	if (playerState_ != playerAttackState_) {
		player->EraseCollider(COLLIDER_ATTACK);
	}

	//行動不能状態なら移動はしない
	if (playerState_ == playerKnockBackState_ || playerState_ == playerDieState_) {
		playerState_->Update(player);
		return;
	}

	//死ぬ処理
	if (player->GetStatus().dead) {
		ChangeState(PLAYER_DIE, player);
	}

	//移動キーが押されているなら
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D)|| Input::IsKey(DIK_W) || Input::IsKey(DIK_S)){
		//Runstateで移動中なら速度早くして、他のstateなら移動速度遅くするとかが良い気がする
		MovePlayer(player);
		//ChangeState(PLAYER_RUN, player);
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

	//状態を変更して、その状態の初期化処理を行う
	switch (nextState)
	{
	case PLAYER_ATTACK:
		playerState_ = playerAttackState_;
		break;

	case PLAYER_DIE:
		playerState_ = playerDieState_;
		break;

	case PLAYER_IDLE:
		playerState_ = playerIdleState_;
		break;

	case PLAYER_JUMP:
		playerState_ = playerJumpState_;
		break;

	case PLAYER_KNOCKBACK:
		playerState_ = playerKnockBackState_;
		break;

	case PLAYER_RUN:
		playerState_ = playerRunState_;
		break;

	default:
		return;
		break;
	}

	playerState_->Enter(player);
	
}

void PlayerStateManager::MovePlayer(Player* player)
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////ここの引数でプレイヤー数を指定する
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 playerPos = player->GetPosition();

	//結局後で正規化してるからここの値は大きくても意味なし
	if (Input::IsKey(DIK_A) && playerPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && playerPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && playerPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && playerPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//斜めの移動でも早くならないように(必要か？)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//速度調整
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	playerPos.x += fMove.x;
	playerPos.z += fMove.z;

	player->SetPosition(playerPos);

	float length = Length(vMove);

	//動いているなら角度を求めて回転する
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//内積から角度を求める
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//外積が-になる角度なら
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		player->SetRotateY(degree);

		player->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}
}
