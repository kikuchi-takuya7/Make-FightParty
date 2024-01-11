#pragma once
//#include "../Engine/GameObject.h"
#include "../Engine/Global.h"
#include "../Engine/Input.h"

//�O���錾
class Player;

/// <summary>
/// playerState�̊��N���X
/// </summary>
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

};

//�������z�֐��ɂ����manager�Ŏ��Ԃ����ĂȂ�����_��