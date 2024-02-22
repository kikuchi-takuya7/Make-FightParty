#pragma once
#include "CharacterAttackState.h"
#include "CharacterDieState.h"
#include "CharacterIdleState.h"
#include "CharacterJumpState.h"
#include "CharacterKnockBackState.h"
#include "CharacterRunState.h"
#include "CharacterState.h"

//class Character;



//�v���C���[�ƓG�̃X�e�[�g�}�l�[�W�����ʂɂ����ق���������������
//Character�N���X�ɃX�e�[�g�}�l�[�W�������邵�A�����蔻����p�����Ȃ��Ă悭�Ȃ�

/// <summary>
/// Character�̏�Ԃ��Ǘ�����
/// </summary>
class CharacterStateManager : public CharacterState
{

public:

	
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ���Ă����\�z
	//static�ɂ����Ⴄ�ƃN���X�ʂ�state�̕ϐ����ĂȂ�������
	//enum�g����static�g��Ȃ��Ă��s�����������ǁA�ǂ�����������
	CharacterAttackState* characterAttackState_;
	CharacterDieState* characterDieState_;
	CharacterIdleState* characterIdleState_;
	CharacterJumpState* characterJumpState_;
	CharacterKnockBackState* characterKnockBackState_;
	CharacterRunState* characterRunState_;

	CharacterState* characterState_;

	CharacterStateManager();

	void Update(Character* character) override;

	void HandleInput(Character* character) override;

	void Enter(Character* character) override;

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="Character">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(CharacterStatePattern nextState, Character* character);

	void MoveCharacter(Character* character);

	
	//////////////////////////�A�N�Z�X�֐�/////////////////////////////////


	//���ǂ����ɐÓI�Ɏc���Ă�state�Ō�������Ȃ炱�̊֐��g���Ă����Ǐ�̂��̃N���X���̕ϐ��g������Ӗ��Ȃ��ː�

private:


};

