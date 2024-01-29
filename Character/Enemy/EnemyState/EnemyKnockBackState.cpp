#include "EnemyKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Enemy.h"

namespace {

	const float KNOCKBACK_DISTANCE = 3.0f;
	const int KNOCKBACK_RIGIDITYFLAME = 30;//��炢�d���t���[��
}

void EnemyKnockBackState::Update(Enemy* enemy, CharacterAI* AI)
{

	flame_++;

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 enemyPos = enemy->GetPosition();

	//���[�g�łʂ�ʂ铮���悤��
	if (rate_ < 1.0f) {
		rate_ += 0.05f;

		// �ςȐ����Ŏ~�܂�Ȃ��悤��
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

	//��炢�d�����I�������
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
	//�F�X������
	flame_ = ZERO;
	rate_ = 0.0f;
	enemy->ChangeKnockBack(true);


	//�G�̌����Ă�����ɉ�]�����邽�߉�]���t�ɂ���
	playerRot_.y = playerRot_.y - 180;
	enemy->SetRotateY(playerRot_.y);


	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 floatPos = enemy->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//�ŏ��ɍŏI�I�Ȉʒu���m�F���Ă���
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO };

	//�ړ��x�N�g����ό` (�G�Ɠ��������ɉ�]) ������
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(playerRot_.y));
	move = XMVector3TransformCoord(move, rotY);

	//�v���C���[��G�Ɣ��Ε����Ɉړ�������
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
