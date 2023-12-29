#pragma once

class Player;

class PlayerState
{
public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Update(Player* player) {};


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void HandleInput(Player* player) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="player">Player�̃|�C���^</param>
	virtual void Enter(Player* player) {};

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="nowState">���݂̏��</param>
	/// <param name="state">�ω����������</param>
	//void ChangeState(PlayerState* nowState, PlayerState* state);
};

