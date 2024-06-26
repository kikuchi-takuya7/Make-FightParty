#include "CharacterKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Utility/LinearInterpolate.h"
#include "../../../Engine/Utility/RateFrame.h"
#include "../../../AI/MetaAI.h"
#include "../Character.h"

namespace {

	const float KNOCKBACK_DISTANCE = 4.0f;//ノックバック距離
	const int KNOCKBACK_RIGIDITYFLAME = 30;//喰らい硬直フレーム
	const float KNOCKBACK_SPEED = 0.05f;//どのくらいの速度でノックバックするか
	const int KNOCKBACK_START_FRAME = 210;
	const int KNOCKBACK_END_FRAME = 240;

	//アニメーションの1フレーム毎に進む速度
	const int ANIMATION_SPEED = 1;

	const float MAX_KNOCKBACK_X = 29.0f;
	const float MAX_KNOCKBACK_Z = 29.0f;
	const float MIN_KNOCKBACK_X = ZERO;
	const float MIN_KNOCKBACK_Z = ZERO;
}

CharacterKnockBackState::CharacterKnockBackState(Character* character, int model):CharacterState(character, model)
{
}

void CharacterKnockBackState::Update()
{

	//RateFrameが使えないので自分でレートを管理
	knockBackRate_ += KNOCKBACK_SPEED;
	if (knockBackRate_ > 1.0f) {
		knockBackRate_ = 1.0f;
	}

	//プレイヤーの現在の位置をベクトル型に変換
	XMFLOAT3 playerPos = pCharacter_->GetPosition();

	playerPos = LinearInterpolate::RateMovePosition(playerPos, lastPoint_, knockBackRate_);

	pCharacter_->SetPosition(playerPos);

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
	//色々初期化
	knockBackRate_ = ZERO;

	Model::SetAnimFrame(hCharacterModel_, KNOCKBACK_START_FRAME, KNOCKBACK_END_FRAME, ANIMATION_SPEED);

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

	if (lastPoint_.x <= MIN_KNOCKBACK_X) {
		lastPoint_.x = MIN_KNOCKBACK_X;
	}
	if (lastPoint_.x >= MAX_KNOCKBACK_X) {
		lastPoint_.x = MAX_KNOCKBACK_X;
	}
	if (lastPoint_.z <= MIN_KNOCKBACK_Z) {
		lastPoint_.z = MIN_KNOCKBACK_X;
	}
	if (lastPoint_.z >= MAX_KNOCKBACK_Z) {
		lastPoint_.z = MAX_KNOCKBACK_Z;
	}

}

void CharacterKnockBackState::Leave()
{
}
