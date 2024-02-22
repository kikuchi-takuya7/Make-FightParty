#include "CharacterStateManager.h"
#include "../Character.h"

//�estatic�ϐ�������������Bstatic������O���[�o���Ȉʒu�ōŏ��ɏ��������Ȃ��ƃ_��
//CharacterAttackState* CharacterStateManager::CharacterAttackState_ = new CharacterAttackState;
//CharacterDieState* CharacterStateManager::CharacterDieState_ = new CharacterDieState;
//CharacterIdleState* CharacterStateManager::CharacterIdleState_ = new CharacterIdleState;
//CharacterJumpState* CharacterStateManager::CharacterJumpState_ = new CharacterJumpState;
//CharacterRunState* CharacterStateManager::CharacterRunState_ = new CharacterRunState;

//CharacterState* CharacterStateManager::CharacterState_ = CharacterIdleState_;

CharacterStateManager::CharacterStateManager()
{
	characterAttackState_ = new CharacterAttackState;
	characterDieState_ = new CharacterDieState;
	characterIdleState_ = new CharacterIdleState;
	characterJumpState_ = new CharacterJumpState;
	characterKnockBackState_ = new CharacterKnockBackState;
	characterRunState_ = new CharacterRunState;

	characterState_ = characterIdleState_;
}

void CharacterStateManager::Update(Character* character)
{

	//�U�����Ă鎞�ɍU�����������ɍU������������p�B���ꂼ���Enter�ɒu����������������
	if (characterState_ != characterAttackState_) {

		character->EraseCollider(COLLIDER_ATTACK);
	}

	//�s���s�\��ԂȂ�ړ��͂��Ȃ�
	if (characterState_ == characterKnockBackState_ || characterState_ == characterDieState_) {
		characterState_->Update(character);
		return;
	}

	//���ʏ���
	if (character->GetStatus().dead) {
		ChangeState(DIE, character);
	}

	//�ړ��L�[��������Ă���Ȃ�
	if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D)|| Input::IsKey(DIK_W) || Input::IsKey(DIK_S))
	{

		//Runstate�ňړ����Ȃ瑬�x�������āA����state�Ȃ�ړ����x�x������Ƃ����ǂ��C������
		MoveCharacter(character);
		//ChangeState(Character_RUN, Character);
	}

	characterState_->Update(character);

	

}

void CharacterStateManager::HandleInput(Character* character)
{
}

void CharacterStateManager::Enter(Character* character)
{
}

void CharacterStateManager::ChangeState(CharacterStatePattern nextState, Character* character)
{

	//��Ԃ�ύX���āA���̏�Ԃ̏������������s��
	switch (nextState)
	{
	case ATTACK:
		characterState_ = characterAttackState_;
		break;

	case DIE:
		characterState_ = characterDieState_;
		break;

	case IDLE:
		characterState_ = characterIdleState_;
		break;

	case JUMP:
		characterState_ = characterJumpState_;
		break;

	case KNOCKBACK:
		characterState_ = characterKnockBackState_;
		break;

	case RUN:
		characterState_ = characterRunState_;
		break;

	default:
		return;
		break;
	}

	characterState_->Enter(character);
	
}

void CharacterStateManager::MoveCharacter(Character* character)
{
	XMFLOAT3 fMove = ZERO_FLOAT3;

	////�����̈����Ńv���C���[�����w�肷��
	//fMove.x = Input::GetPadStickL(0).x;
	//fMove.z = Input::GetPadStickL(0).y;

	XMFLOAT3 characterPos = character->GetPosition();

	//���ǌ�Ő��K�����Ă邩�炱���̒l�͑傫���Ă��Ӗ��Ȃ�
	if (Input::IsKey(DIK_A) && characterPos.x >= 0.5)
	{
		fMove.x = -0.01f;
	}
	if (Input::IsKey(DIK_D) && characterPos.x <= 28.5)
	{
		fMove.x = 0.01f;
	}
	if (Input::IsKey(DIK_W) && characterPos.z <= 28.5)
	{
		fMove.z = 0.01f;
	}
	if (Input::IsKey(DIK_S) && characterPos.z >= 0.5)
	{
		fMove.z = -0.01f;
	}

	XMVECTOR vMove = XMLoadFloat3(&fMove);

	//�΂߂̈ړ��ł������Ȃ�Ȃ��悤��(�K�v���H)
	vMove = XMVector3Normalize(vMove);

	fMove = VectorToFloat3(vMove);

	//���x����
	fMove.x *= 0.5;
	fMove.z *= 0.5;

	characterPos.x += fMove.x;
	characterPos.z += fMove.z;

	character->SetPosition(characterPos);

	float length = Length(vMove);

	//�����Ă���Ȃ�p�x�����߂ĉ�]����
	if (length != ZERO) {

		XMVECTOR vFront = { 0,0,1,0 };
		vMove = XMVector3Normalize(vMove);

		//���ς���p�x�����߂�
		XMVECTOR vDot = XMVector3Dot(vFront, vMove);
		float dot = XMVectorGetX(vDot);
		float angle = acos(dot);

		//�O�ς�-�ɂȂ�p�x�Ȃ�
		XMVECTOR vCross = XMVector3Cross(vFront, vMove);
		if (XMVectorGetY(vCross) < ZERO) {

			angle *= -1;
		}

		float degree = XMConvertToDegrees(angle);

		character->SetRotateY(degree);

		character->SetColliderRotate(XMFLOAT3(ZERO, degree, ZERO));

	}
}
