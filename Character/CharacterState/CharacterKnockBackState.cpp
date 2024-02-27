#include "CharacterKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Character.h"

namespace {

	const float KNOCKBACK_DISTANCE = 4.0f;//ノックバック距離
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
	const float KNOCKBACK_SPEED = 0.05f;//どのくらいの速度でノックバックするか
	const int KNOCKBACK_START_FRAME = 210;
	const int KNOCKBACK_END_FRAME = 240;
}

CharacterKnockBackState::CharacterKnockBackState(Character* character, int model):CharacterState(character, model)
{
}

void CharacterKnockBackState::Update()
{

	flame_++;

	//敵の向いている方向が欲しい.できればEnterの時点で飛ばされる座標を取っておいて、そこに着いたら動けるって感じにしたい。緩急付けて

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 playerPos = pCharacter_->GetPosition();

	pCharacter_->RateMovePosition(playerPos, lastPoint_, KNOCKBACK_SPEED);

	pCharacter_->SetPosition(playerPos);

	/*if (characterPos == lastPoint_) {
		pCharacter_->ChangeState(character_IDLE);
		pCharacter_->ChangeKnockBack(false);
	}*/


	int nowFrame = Model::GetAnimFrame(hCharacterModel_);

	//喰らい硬直が終わったら
	if (nowFrame >= KNOCKBACK_END_FRAME) {
		pCharacter_->ChangeState(IDLE);
	}

	HandleInput();
}

void CharacterKnockBackState::HandleInput()
{
}

void CharacterKnockBackState::Enter()
{
	flame_ = 0;
	//色々初期化
	knockBackRate_ = 0.0f;

	Model::SetAnimFrame(hCharacterModel_, KNOCKBACK_START_FRAME, KNOCKBACK_END_FRAME, 1);

	XMFLOAT3 targetRot = pCharacter_->GetTargetRot();

	//敵の向いてる方向に回転させるため回転を逆にする
	targetRot.y = targetRot.y - 180;
	pCharacter_->SetRotateY(targetRot.y);


	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 floatPos = pCharacter_->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//最初に最終的な位置を確認しておく
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO };

	//移動ベクトルを変形 (敵と同じ向きに回転) させる
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(targetRot.y));
	move = XMVector3TransformCoord(move, rotY);

	//プレイヤーを敵と反対方向に移動させる
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	if (lastPoint_.x <= 0.5) {
		lastPoint_.x = 0;
	}
	if (lastPoint_.x >= 28.5) {
		lastPoint_.x = 28.5;
	}
	if (lastPoint_.z <= 0.5) {
		lastPoint_.z = 0.5;
	}
	if (lastPoint_.z >= 28.5) {
		lastPoint_.z = 28.5;
	}

}

void CharacterKnockBackState::Leave()
{
}

float CharacterKnockBackState::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}