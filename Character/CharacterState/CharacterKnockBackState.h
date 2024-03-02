#pragma once
#include "CharacterState.h"

/// <summary>
/// �v���C���[���U����H����Ă�����
/// </summary>
class CharacterKnockBackState : public CharacterState
{

public:

	//�R���X�g���N�^
	CharacterKnockBackState(Character* character, int model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;


	/// <summary>
	/// ���͂ɂ���ď�Ԃ�ω�����
	/// </summary>
	void HandleInput() override;

	/// <summary>
	/// ��ԕω������ŏ��Ɉ�x�����Ă΂��֐�
	/// </summary>
	void Enter() override;

	/// <summary>
	/// ����state���痣��鎞�Ɉ�x�����Ă΂��֐�
	/// </summary>
	void Leave() override;

private:

	//���ԁi�t���[���P�ʁj
	int flame_;

	//�ɋ}��t���郌�[�g
	float knockBackRate_;

	//�ŏI�I�Ȉʒu
	XMFLOAT3 lastPoint_;
};

