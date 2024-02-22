#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"

//�O���錾
class Character;

enum CharacterStatePattern {
	ATTACK,
	DIE,
	IDLE,
	JUMP,
	KNOCKBACK,
	RUN
};

/// <summary>
/// CharacterState�̊��N���X
/// </summary>
class CharacterState
{

public:

	

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	virtual void Update(Character* character) {};


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	virtual void HandleInput(Character* character) {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <param name="Character">Character�̃|�C���^</param>
	virtual void Enter(Character* character) {};

};

//�������z�֐��ɂ����manager�Ŏ��Ԃ����ĂȂ�����_��