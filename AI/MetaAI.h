#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

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


private:
	
	/////////�e��C���X�^���X///////////

	//NavigationAI* pNavigationAI_;
	//CharacterAI* pCharacterAI_;
	
	//Enemy* pEnemy_;
	//Player* pPlayer_;

};

