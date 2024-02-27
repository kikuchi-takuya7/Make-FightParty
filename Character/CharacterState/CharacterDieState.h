#pragma once
#include "CharacterState.h"

/// <summary>
/// ���񂾏��
/// </summary>
class CharacterDieState : public CharacterState
{

public:

	//�R���X�g���N�^
	CharacterDieState(Character* characte, int modelr);

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

