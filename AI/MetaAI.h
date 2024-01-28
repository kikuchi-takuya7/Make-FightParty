#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"


class Player;
class Enemy;
class NavigationAI;

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
	void PushEnemyStatus(Status status) { enemyStatusList_.push_back(status); }
	void PushPlayerStatus(Status status) { playerStatusList_.push_back(status); }


private:
	
	/////////�e��C���X�^���X///////////

	vector<Status> enemyStatusList_;
	vector<Status> playerStatusList_;

	NavigationAI* pNavigationAI_;
};

