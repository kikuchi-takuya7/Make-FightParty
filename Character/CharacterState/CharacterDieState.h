#pragma once
#include "CharacterState.h"

/// <summary>
/// ���񂾏��
/// </summary>
class CharacterDieState : public CharacterState
{

public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="character">Character�̃|�C���^</param>
	void Update(Character* character) override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="character">Character�̃|�C���^</param>
	void HandleInput(Character* character) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="character">Character�̃|�C���^</param>
	void Enter(Character* character) override;

};

