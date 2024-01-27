#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
}

void PlayerKnockBackState::Update(Player* player)
{

	flame_++;

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 playerPos = player->GetPosition();

	//レートでぬるぬる動くように
	if (rate_ < 1.0f) { 
		rate_ += 0.1f;

		// 変な数字で止まらないように
		if (rate_ > 1.0f) 
			rate_ = 1.0f;

		playerPos.x = GetRateValue(playerPos.x, lastPoint_.x, rate_);
		playerPos.z = GetRateValue(playerPos.z, lastPoint_.z, rate_);

		player->SetPosition(playerPos);

	}

	/*if (playerPos == lastPoint_) {
		player->ChangeState(PLAYER_IDLE);
		player->ChangeKnockBack(false);
	}*/

	//喰らい硬直が終わったら
	if (flame_ >= KNOCKBACK_RIGIDITYFLAME) {
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
	//色々初期化
	flame_ = ZERO;
	rate_ = 0.0f;
	player->ChangeKnockBack(true);


	//敵の向いてる方向に回転させるため回転を逆にする
	enemyRot_.y = enemyRot_.y - 180;
	player->SetRotateY(enemyRot_.y);


	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 floatPos = player->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//最初に最終的な位置を確認しておく
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO }; 

	//移動ベクトルを変形 (敵と同じ向きに回転) させる
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(enemyRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//プレイヤーを敵と反対方向に移動させる
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	//player->SetPosition(VectorToFloat3(pos));

}

float PlayerKnockBackState::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}
