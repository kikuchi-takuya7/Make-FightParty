#pragma once
//#include "../Engine/GameObject.h"
#include "../../../Engine/Global.h"
#include "../../../Engine/Input.h"
#include "../../../Engine/Model.h"

//�O���錾
class Character;

//���̏��Ԃ�Manager�̃��X�g�ɓ����Ă���
enum CharacterStateList {
	IDLE,
	ATTACK,
	JUMP,
	KNOCKBACK,
	RUN,
	DIE,
	STATE_NUM
};

/// <summary>
/// CharacterState�̊��N���X
/// </summary>
class CharacterState
{

public:

	//�R���X�g���N�^
	CharacterState(Character* character, int model);


	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() {};


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	virtual void HandleInput() {};

	/// <summary>
	/// ��ԕω������Ƃ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void Enter() {};

	/// <summary>
	/// ����state���痣��鎞�Ɉ�x�����Ă΂��֐�
	/// </summary>
	virtual void Leave() {};

protected:

	//�v���C���[���G�l�~�[�̃C���X�^���X�������Ă���
	Character* pCharacter_;

	int hCharacterModel_;

};

//�������z�֐��ɂ����manager�Ŏ��Ԃ����ĂȂ�����_��