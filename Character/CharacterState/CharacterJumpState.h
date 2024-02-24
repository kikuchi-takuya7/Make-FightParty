#pragma once
#include "CharacterState.h"

/// <summary>
/// �W�����v���Ă���
/// </summary>
class CharacterJumpState : public CharacterState
{

public:

	//�R���X�g���N�^
	CharacterJumpState(Character* character);

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

	float velocity_;

};

