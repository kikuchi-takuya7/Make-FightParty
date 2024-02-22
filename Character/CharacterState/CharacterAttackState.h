#pragma once
#include "CharacterState.h"

class BoxCollider;

/// <summary>
/// �U���������
/// </summary>
class CharacterAttackState : public CharacterState
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

	int flame_;
	//BoxCollider* pAttackCollision_;

};

