#pragma once
#include "AI.h"
#include "NavigationAI.h"

/// <summary>
/// �Q�[���̐i�s�A�A�C�e���̑I�o�����Ǘ�����AI
/// </summary>
class MetaAI : public AI
{

	//�R���X�g���N�^
	MetaAI();

	//�f�X�g���N�^
	~MetaAI();

	/////////�I�[�o�[���C�h�����֐�/////////

	//������
	void Initialize() override;

	//���
	void Release() override;


private:
	NavigationAI* pNavigationAI_;
};

