#pragma once
#include "CharacterState.h"

/// <summary>
/// �����ĂȂ����
/// </summary>
class CharacterIdleState : public CharacterState
{

public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	void Update(Character* character) override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	void HandleInput(Character* character) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	void Enter(Character* character) override;

};

