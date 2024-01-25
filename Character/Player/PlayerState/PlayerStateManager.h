#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerKnockBackState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

class Player;

enum StatePattern {
	ATTACK,
	DIE,
	IDLE,
	JUMP,
	KNOCKBACK,
	RUN,
	NUM
};

//�v���C���[�ƓG�̃X�e�[�g�}�l�[�W�����ʂɂ����ق���������������
//Character�N���X�ɃX�e�[�g�}�l�[�W�������邵�A�����蔻����p�����Ȃ��Ă悭�Ȃ�

/// <summary>
/// player�̏�Ԃ��Ǘ�����
/// </summary>
class PlayerStateManager
{

public:
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ���Ă����\�z
	//���Ȃ݂ɕ���playerstate�����Ă������ƃN���X����static�Ŏ���Ă����
	//enum�g����static�g��Ȃ��Ă��s�����������ǁA�ǂ�����������
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerKnockBackState* playerKnockBackState_;
	PlayerRunState* playerRunState_;

	PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player);

	void HandleInput(Player* player);

	void Enter(Player* player);

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(StatePattern nextState, Player* player);
	
	//���ǂ����ɐÓI�Ɏc���Ă�state�Ō�������Ȃ炱�̊֐��g���Ă����Ǐ�̂��̃N���X���̕ϐ��g������Ӗ��Ȃ��ː�

private:
	StatePattern nowState_;
};

//��y�͂���state���p�����Ă����ǌp���������R���悭�킩��Ȃ���������p�����Ȃ������B���Ă�������
