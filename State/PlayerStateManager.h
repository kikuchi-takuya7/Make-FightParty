#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

class Player;

/// <summary>
/// player�̏�Ԃ��Ǘ�����
/// </summary>
class PlayerStateManager
{

public:
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ�
	static PlayerAttackState* playerAttackState_;
	static PlayerDieState* playerDieState_;
	static PlayerIdleState* playerIdleState_;
	static PlayerJumpState* playerJumpState_;
	static PlayerRunState* playerRunState_;

	static PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player);

	void HandleInput(Player* player);

	void Enter(Player* player);

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(PlayerState* nextState, Player* player);
	
	//���ǂ����ɐÓI�Ɏc���Ă�state�Ō�������Ȃ炱�̊֐��g���Ă����Ǐ�̂��̃N���X���̕ϐ��g������Ӗ��Ȃ��ː�
};

