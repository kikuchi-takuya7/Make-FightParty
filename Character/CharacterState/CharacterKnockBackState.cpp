#include "CharacterKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../Character.h"

namespace {

	const float KNOCKBACK_DISTANCE = 4.0f;//�m�b�N�o�b�N����
	const int KNOCKBACK_RIGIDITYFLAME = 30;//��炢�d���t���[��
	const float KNOCKBACK_SPEED = 0.05f;//�ǂ̂��炢�̑��x�Ńm�b�N�o�b�N���邩
	const int KNOCKBACK_START_FRAME = 210;
	const int KNOCKBACK_END_FRAME = 240;
}

CharacterKnockBackState::CharacterKnockBackState(Character* character, int model):CharacterState(character, model)
{
}

void CharacterKnockBackState::Update()
{

	flame_++;

	//�G�̌����Ă���������~����.�ł����Enter�̎��_�Ŕ�΂������W������Ă����āA�����ɒ������瓮������Ċ����ɂ������B�ɋ}�t����

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 playerPos = pCharacter_->GetPosition();

	pCharacter_->RateMovePosition(playerPos, lastPoint_, KNOCKBACK_SPEED);

	pCharacter_->SetPosition(playerPos);

	/*if (characterPos == lastPoint_) {
		pCharacter_->ChangeState(character_IDLE);
		pCharacter_->ChangeKnockBack(false);
	}*/


	int nowFrame = Model::GetAnimFrame(hCharacterModel_);

	//��炢�d�����I�������
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
	//�F�X������
	knockBackRate_ = 0.0f;

	Model::SetAnimFrame(hCharacterModel_, KNOCKBACK_START_FRAME, KNOCKBACK_END_FRAME, 1);

	XMFLOAT3 targetRot = pCharacter_->GetTargetRot();

	//�G�̌����Ă�����ɉ�]�����邽�߉�]���t�ɂ���
	targetRot.y = targetRot.y - 180;
	pCharacter_->SetRotateY(targetRot.y);


	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 floatPos = pCharacter_->GetPosition();
	XMVECTOR pos = XMLoadFloat3(&floatPos);

	//�ŏ��ɍŏI�I�Ȉʒu���m�F���Ă���
	XMVECTOR move = { ZERO, ZERO, KNOCKBACK_DISTANCE, ZERO };

	//�ړ��x�N�g����ό` (�G�Ɠ��������ɉ�]) ������
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(targetRot.y));
	move = XMVector3TransformCoord(move, rotY);

	//�v���C���[��G�Ɣ��Ε����Ɉړ�������
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