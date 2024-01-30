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
	CharacterAI(GameObject* parent);
	CharacterAI(GameObject* parent,Enemy* enemy, NavigationAI* naviAI);

	//�f�X�g���N�^
	~CharacterAI();

	/////////�I�[�o�[���C�h�����֐�///////

	//������
	void Initialize() override;

	//���
	void Release() override;

	/////////////////�����o�֐�//////////////////////////

	void AskTarget();
	
	////////////////�I�u�W�F�N�g�𑀂郁���o�֐�///////////////////

	void MoveEnemy();

	void Attack();

	void IsAttack();


	///////////////////���AI�ɏ���`����֐�/////////////////////////////

	void TellStatus();

	///////////////////�A�N�Z�X�֐�/////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }

	void SetTargetID(int ID) { targetID_ = ID; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	//����������G�̃C���X�^���X
	Enemy* pEnemy_;

	//���������_���Ă���G��ID
	int targetID_;

};

