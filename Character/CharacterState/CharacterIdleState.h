#pragma once
#include "CharacterState.h"

/// <summary>
/// �����ĂȂ����
/// </summary>
class CharacterIdleState : public CharacterState
{

public:

	//�R���X�g���N�^
	CharacterIdleState(Character* character);

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

};

