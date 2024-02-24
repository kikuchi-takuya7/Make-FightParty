#include "CharacterAttackState.h"
#include "../../BoxCollider.h"
#include "../Character.h"

//�萔
namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
	const int ATTACK_RIGIDITYFLAME = 60;//�U�������t���[��

}

CharacterAttackState::CharacterAttackState(Character* character) :CharacterState(character)
{
}

void CharacterAttackState::Update()
{

	//�U���A�j���[�V�������n�߂Ĉ�莞�ԗ�������Idle�ɖ߂�
	flame_++;

	//�U���͉���u�Ԃɏ����O�ɏo�ăW�����v�ł��Ȃ��Ȃ�݂����Ȋ����ɂ������B�X�e�B�b�N�t�@�C�g���Q�[���݂����Ȋ���

	//�U�����I�������U���p�̃R���C�_�[��j������state��߂�
	if (flame_ >= ATTACK_RIGIDITYFLAME) {
		pCharacter_->EraseCollider(ColliderAttackType::COLLIDER_ATTACK);
		pCharacter_->ChangeState(IDLE);
	}

	HandleInput();
}

void CharacterAttackState::HandleInput()
{
}

void CharacterAttackState::Enter()
{
	flame_ = ZERO;
	pCharacter_->SetAttackCollider();
}

void CharacterAttackState::Leave()
{
	pCharacter_->EraseCollider(COLLIDER_ATTACK);
}
