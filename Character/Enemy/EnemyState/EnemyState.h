#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"
//#include "../../../AI/CharacterAI.h"

//�O���錾
class Enemy;
class CharacterAI;

enum EnemyStatePattern {
	ENEMY_ATTACK,
	ENEMY_DIE,
	ENEMY_IDLE,
	ENEMY_JUMP,
	ENEMY_KNOCKBACK,
	ENEMY_RUN
};

/// <summary>
/// EnemyState�̊��N���X
/// </summary>
class EnemyState
{
public:


	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	virtual void Update(Enemy* enemy, CharacterAI* AI) {};


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	virtual void HandleInput(Enemy* enemy, CharacterAI* AI) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="enemy">Enemy�̃|�C���^</param>
	virtual void Enter(Enemy* enemy) {};

};

//�������z�֐��ɂ����manager�Ŏ��Ԃ����ĂȂ�����_��