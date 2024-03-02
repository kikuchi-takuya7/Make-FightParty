#pragma once
#include "CharacterAttackState.h"
#include "CharacterDieState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"
#include "CharacterKnockBackState.h"
#include "CharacterRunState.h"
#include "CharacterState.h"
#include <vector>

/// <summary>
/// Character�̏�Ԃ��Ǘ�����
/// </summary>
class CharacterStateManager : public CharacterState
{

public:
	
	//��������state��new���ĕς����莖�O�ɕێ����Ă����Ε��ׂ�������Ȃ�
	CharacterState* characterState_;

	//CharacterStateList��enum�^���ɓ����Ă���
	std::vector<CharacterState*> pCharacterStateList_;

	CharacterStateManager(Character* character, int model);
	~CharacterStateManager();

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

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="Character">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(CharacterStateList nextState);

private:


};

