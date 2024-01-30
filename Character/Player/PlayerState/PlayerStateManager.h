#pragma once
#include "PlayerAttackState.h"
#include "PlayerDieState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerKnockBackState.h"
#include "PlayerRunState.h"
#include "PlayerState.h"

//class Player;



//�v���C���[�ƓG�̃X�e�[�g�}�l�[�W�����ʂɂ����ق���������������
//Character�N���X�ɃX�e�[�g�}�l�[�W�������邵�A�����蔻����p�����Ȃ��Ă悭�Ȃ�

/// <summary>
/// player�̏�Ԃ��Ǘ�����
/// </summary>
class PlayerStateManager : public PlayerState
{

public:

	
	
	//��������state��new���ĕς����莖�O�ɐÓI�ɕێ����Ă����΃������̐ߖ�ɂȂ���Ă����\�z
	//static�ɂ����Ⴄ�ƃN���X�ʂ�state�̕ϐ����ĂȂ�������
	//enum�g����static�g��Ȃ��Ă��s�����������ǁA�ǂ�����������
	PlayerAttackState* playerAttackState_;
	PlayerDieState* playerDieState_;
	PlayerIdleState* playerIdleState_;
	PlayerJumpState* playerJumpState_;
	PlayerKnockBackState* playerKnockBackState_;
	PlayerRunState* playerRunState_;

	PlayerState* playerState_;

	PlayerStateManager();

	void Update(Player* player) override;

	void HandleInput(Player* player) override;

	void Enter(Player* player) override;

	/// <summary>
	/// ��Ԃ�ύX����
	/// </summary>
	/// <param name="change">�ύX��̏��</param>
	/// <param name="player">�ύX����v���C���[�̃|�C���^</param>
	void ChangeState(PlayerStatePattern nextState, Player* player);

	void MovePlayer(Player* player);

	
	//////////////////////////�A�N�Z�X�֐�/////////////////////////////////

	void SetEnemyRot(XMFLOAT3 rot) { playerKnockBackState_->SetEnemyRotate(rot); }


	//���ǂ����ɐÓI�Ɏc���Ă�state�Ō�������Ȃ炱�̊֐��g���Ă����Ǐ�̂��̃N���X���̕ϐ��g������Ӗ��Ȃ��ː�

private:


};

//��y�͂���state���p�����Ă����ǌp���������R���悭�킩��Ȃ���������p�����Ȃ������B���Ă�������
//�֐������ʂ��Ă邩��Ȃ̂��Ȃ�
