#pragma once
#include "EnemyState.h"

/// <summary>
/// �v���C���[�������Ă�����
/// </summary>
class EnemyIdleState : public EnemyState
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
	void HandleInput(Enemy* enemy, CharacterAI* AI) override;

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
<<<<<<< HEAD
	void Enter(Enemy* enemy) override;
=======
	void Enter(Enemy* enemy, CharacterAI* AI) override;
>>>>>>> MapEditor_ver.2

};