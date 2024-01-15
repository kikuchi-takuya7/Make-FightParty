#pragma once
#include "AI.h"
#include "NavigationAI.h"


/// <summary>
/// �G�L�����N�^�[�𓮂���AI
/// </summary>
class CharacterAI : public AI
{

	//�R���X�g���N�^
	CharacterAI();

	//�f�X�g���N�^
	~CharacterAI();

	/////////�I�[�o�[���C�h�����֐�///////

	//������
	void Initialize() override;

	//���
	void Release() override;

private:

	NavigationAI* pNavigationAI_;
};

