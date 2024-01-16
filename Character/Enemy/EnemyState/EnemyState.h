#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"

//�O���錾
class Enemy;

/// <summary>
/// playerState�̊��N���X
/// </summary>
class EnemyState
{
public:

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="player">Enemy�̃|�C���^</param>
	virtual void Update(Enemy* player) {};


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="player">Enemy�̃|�C���^</param>
	virtual void HandleInput(Enemy* player) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="player">Enemy�̃|�C���^</param>
	virtual void Enter(Enemy* player) {};

};

//�������z�֐��ɂ����manager�Ŏ��Ԃ����ĂȂ�����_��