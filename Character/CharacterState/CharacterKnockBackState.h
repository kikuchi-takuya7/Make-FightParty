#pragma once
#include "CharacterState.h"

/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class CharacterKnockBackState : public CharacterState
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

private:

	//���ԁi�t���[���P�ʁj
	int flame_;
};

