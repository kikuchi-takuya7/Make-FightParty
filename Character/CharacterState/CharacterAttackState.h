#pragma once
#include "CharacterState.h"

class BoxCollider;

/// <summary>
/// �U���������
/// </summary>
class CharacterAttackState : public CharacterState
{

public:

	//�R���X�g���N�^
	CharacterAttackState(Character* character, int model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	void HandleInput() override;

	/// <summary>
	/// ��ԕω������ŏ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	void Enter() override;

	/// <summary>
	/// ����state���痣��鎞�Ɉ�x�����Ă΂��֐�
	/// </summary>
	void Leave() override;


private:

	int frame_;
	bool settedCollision_;

};

