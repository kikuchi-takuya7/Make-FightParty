#include "EnemyKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Enemy.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
}

void EnemyKnockBackState::Update(Enemy* enemy, CharacterAI* AI)
{

	flame_++;

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 enemyPos = enemy->GetPosition();

	//レートでぬるぬる動くように
	if (rate_ < 1.0f) {
		rate_ += 0.05f;

		// 変な数字で止まらないように
		if (rate_ > 1.0f)
			rate_ = 1.0f;

		enemyPos.x = GetRateValue(enemyPos.x, lastPoint_.x, rate_);
		enemyPos.z = GetRateValue(enemyPos.z, lastPoint_.z, rate_);

		enemy->SetPosition(enemyPos);

	}

	/*if (enemyPos == lastPoint_) {
		enemy->ChangeState(PLAYER_IDLE);
		enemy->ChangeKnockBack(false);
	}*/

	//喰らい硬直が終わったら
	if (flame_ >= KNOCKBACK_RIGIDITYFLAME) {
		enemy->ChangeState(ENEMY_IDLE);
		enemy->ChangeKnockBack(false);
	}

	HandleInput(enemy,AI);
}

void EnemyKnockBackState::HandleInput(Enemy* enemy, CharacterAI* AI)
{
}

void EnemyKnockBackState::Enter(Enemy* enemy)
{
	//色々初期化
	flame_ = ZERO;
	rate_ = 0.0f;
	enemy->ChangeKnockBack(true);


	//敵の向いてる方向に回転させるため回転を逆にする
	playerRot_.y = playerRot_.y - 180;
	enemy->SetRotateY(playerRot_.y);


	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 floatPos = enemy->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//最初に最終的な位置を確認しておく
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO };

	//移動ベクトルを変形 (敵と同じ向きに回転) させる
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(playerRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//プレイヤーを敵と反対方向に移動させる
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	if (lastPoint_.x <= 0) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 29) {
		lastPoint_.x = 29;
	}
	if (lastPoint_.z <= 0) {
		lastPoint_.z = 0;
	}
	if (lastPoint_.z >= 29) {
		lastPoint_.z = 29;
	}

	//enemy->SetPosition(VectorToFloat3(pos));

}

float EnemyKnockBackState::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}
