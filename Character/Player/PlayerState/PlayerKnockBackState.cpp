#include "PlayerKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Player.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//��炢�d���t���[��
}

void PlayerKnockBackState::Update(Player* player)
{

	flame_++;

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 playerPos = player->GetPosition();

	//���[�g�łʂ�ʂ铮���悤��
	if (rate_ < 1.0f) { 
		rate_ += 0.1f;

		// �ςȐ����Ŏ~�܂�Ȃ��悤��
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

	//��炢�d�����I�������
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
	//�F�X������
	flame_ = ZERO;
	rate_ = 0.0f;
	player->ChangeKnockBack(true);


	//�G�̌����Ă�����ɉ�]�����邽�߉�]���t�ɂ���
	enemyRot_.y = enemyRot_.y - 180;
	player->SetRotateY(enemyRot_.y);


	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 floatPos = player->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//�ŏ��ɍŏI�I�Ȉʒu���m�F���Ă���
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO }; 

	//�ړ��x�N�g����ό` (�G�Ɠ��������ɉ�]) ������
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(enemyRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//�v���C���[��G�Ɣ��Ε����Ɉړ�������
	pos -= move;

	lastPoint_ = VectorToFloat3(pos);

	//player->SetPosition(VectorToFloat3(pos));

}

float PlayerKnockBackState::GetRateValue(float begin, float end, float rate)
{
	return (end - begin) * rate + begin;
}
