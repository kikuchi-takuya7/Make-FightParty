#pragma once
#include "EnemyState.h"

/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class EnemyRunState : public EnemyState
{

public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void Update(Enemy* enemy, CharacterAI* AI) override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void HandleInput(Enemy* enemy) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	void Enter(Enemy* enemy) override;

};

