#pragma once
#include "AI.h"

class NavigationAI;
class MetaAI;
class Enemy;

/// <summary>
/// �G�L�����N�^�[�𓮂���AI
/// </summary>
class CharacterAI : public AI
{

public:

	//�R���X�g���N�^
	CharacterAI();
	CharacterAI(Enemy* enemy, NavigationAI* naviAI);

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
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	Enemy* pEnemy_;

};

