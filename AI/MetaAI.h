#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Character/Character.h"

class Player;
class Enemy;
class CreateMode;
class NavigationAI;

/// <summary>
/// �Q�[���̐i�s�A�A�C�e���̑I�o�����Ǘ�����AI
/// </summary>
class MetaAI : public AI
{

public:

	//�R���X�g���N�^
	MetaAI(GameObject* parent);

	//�f�X�g���N�^
	~MetaAI();

	/////////�I�[�o�[���C�h�����֐�/////////

	//������
	void Initialize() override;

	//���
	void Release() override;


	////////////�����o�֐�////////////////

	/// <summary>
	/// �_���ׂ�������x������
	/// </summary>
	/// <param name="ID">������ID</param>
	/// <returns>�_���ׂ������ID</returns>
	int Targeting(int ID);

	/// <summary>
	/// 1�ʂ̃L����ID�͒N���A���l���邩���m�F
	/// </summary>
	void CheckNo1Chara();

	void NextGame();

	void GameCameraSet();

	//////////////�A�N�Z�X�֐� //////////

	void PushCharacterStatus(Status status) { characterStatusList_.emplace_back(status); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void ChangeStatus(int ID, Status status) { characterStatusList_.at(ID) = status; }
	void SetCreateMode(CreateMode* create) { pCreateMode_ = create; }
	vector<int> GetRanking() { return ranking_; }


private:
	

	//vector<Status> enemyStatusList_;
	//vector<Status> playerStatusList_;

	vector<Status> characterStatusList_;

	NavigationAI* pNavigationAI_;

	CreateMode* pCreateMode_;

	//����1�ʂ̐l��ID���o���Ă���
	vector<int> No1CharaID_;

	//���݂̏��ʂ�ID�Ŋo���Ă���
	vector<int> ranking_;
};

