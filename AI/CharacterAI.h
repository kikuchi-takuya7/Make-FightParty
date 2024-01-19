#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"

class MetaAI;

/// <summary>
/// �G�L�����N�^�[�𓮂���AI
/// </summary>
class CharacterAI : public AI
{

public:

	//�R���X�g���N�^
	CharacterAI();
	CharacterAI(Enemy* enemy);

	//�f�X�g���N�^
	~CharacterAI();

	/////////�I�[�o�[���C�h�����֐�///////

	//������
	void Initialize() override;

	//���
	void Release() override;

	/////////////////�����o�֐�//////////////////////////

	
	////////////////�I�u�W�F�N�g�𑀂郁���o�֐�///////////////////

	void MoveEnemy();


	///////////////////�A�N�Z�X�֐�/////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }


private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	Enemy* pEnemy_;

};

