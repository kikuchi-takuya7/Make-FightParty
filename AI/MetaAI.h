#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"

class Player;
class Enemy;

/// <summary>
/// �Q�[���̐i�s�A�A�C�e���̑I�o�����Ǘ�����AI
/// </summary>
class MetaAI : public AI
{

public:

	//�R���X�g���N�^
	MetaAI();

	//�f�X�g���N�^
	~MetaAI();

	/////////�I�[�o�[���C�h�����֐�/////////

	//������
	void Initialize() override;

	//���
	void Release() override;


	//////////////�A�N�Z�X�֐� //////////


private:
	
	/////////�e��C���X�^���X///////////

	//NavigationAI* pNavigationAI_;
	//CharacterAI* pCharacterAI_;

};

