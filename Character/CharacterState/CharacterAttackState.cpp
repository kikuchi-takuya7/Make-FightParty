#include "CharacterAttackState.h"
#include "../../BoxCollider.h"
#include "../Character.h"

//�萔
namespace {
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1, 0.5, 2);
	const int ATTACK_RIGIDITYFLAME = 60;//�U�������t���[��

}

void CharacterAttackState::Update(Character* character)
{

	//�U���A�j���[�V�������n�߂Ĉ�莞�ԗ�������Idle�ɖ߂�
	flame_++;

	//�U���͉���u�Ԃɏ����O�ɏo�ăW�����v�ł��Ȃ��Ȃ�݂����Ȋ����ɂ������B�X�e�B�b�N�t�@�C�g���Q�[���݂����Ȋ���

	//�U�����I�������U���p�̃R���C�_�[��j������state��߂�
	if (flame_ >= ATTACK_RIGIDITYFLAME) {
		character->EraseCollider(ColliderAttackType::COLLIDER_ATTACK);
		character->ChangeState(IDLE);
	}

	HandleInput(character);
}

void CharacterAttackState::HandleInput(Character* character)
{
}

void CharacterAttackState::Enter(Character* character)
{
	flame_ = ZERO;
	character->SetAttackCollider();
}
