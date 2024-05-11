#include "CharacterKnockBackState.h"
#include "../../../Engine/Input.h"
#include "../../../AI/MetaAI.h"
#include "../Character.h"

namespace {

	const float KNOCKBACK_DISTANCE = 4.0f;//�m�b�N�o�b�N����
	const int KNOCKBACK_RIGIDITYFLAME = 30;//��炢�d���t���[��
	const float KNOCKBACK_SPEED = 0.05f;//�ǂ̂��炢�̑��x�Ńm�b�N�o�b�N���邩
	const int KNOCKBACK_START_FRAME = 210;
	const int KNOCKBACK_END_FRAME = 240;

	//�A�j���[�V������1�t���[�����ɐi�ޑ��x
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

	flame_++;

	//�v���C���[�̌��݂̈ʒu���x�N�g���^�ɕϊ�
	XMFLOAT3 playerPos = pCharacter_->GetPosition();

	pCharacter_->RateMovePosition(playerPos, lastPoint_, KNOCKBACK_SPEED);

	pCharacter_->SetPosition(playerPos);

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
	flame_ = ZERO;
	//�F�X������
	knockBackRate_ = ZERO;

	Model::SetAnimFrame(hCharacterModel_, KNOCKBACK_START_FRAME, KNOCKBACK_END_FRAME, ANIMATION_SPEED);

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
