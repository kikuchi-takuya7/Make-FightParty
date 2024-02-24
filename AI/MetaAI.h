#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"

enum TARGETPATTERN {
	TARGET_RANDAM,
	TARGET_NO_1,
	TARGET_NUM,

};

class Player;
class Enemy;
class CreateMode;
class NavigationAI;
class CountDownUI;
class Timer;

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

	//�X�V
	void Update() override;

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
	

	/////////�Q�[���̗�����Ǘ�����֐�///////////

	/// <summary>
	/// ���s�����܂��Ă����ꍇ�A�N���G�C�g���[�h�Ɉڍs����
	/// </summary>
	void ToCreateMode();

	/// <summary>
	/// �Q�[�����J�n����
	/// </summary>
	void StartGame();

	/// <summary>
	/// �Q�[���̏�Ԃ����Z�b�g����
	/// </summary>
	void ResetGame();

	/// <summary>
	/// �Q�[���p�̃J�����ɐ؂�ւ���i���̈ʒu�ɃZ�b�g����j
	/// </summary>
	void GameCameraSet();

	/// <summary>
	/// �N���G�C�g���[�h�ŕ\�����ꂽ�I�u�W�F�N�g��I������
	/// </summary>
	/// <param name="model">�\������Ă���I�u�W�F�N�g�ꗗ</param>
	/// <returns>�ǂ̃��f����I�񂾂�</returns>
	int SelectObject(vector<int> model);

	//////////////�A�N�Z�X�֐� //////////

	Status GetCharacterStatus(int ID) { return characterStatusList_.at(ID); }
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

	CountDownUI* pCountDown_;

	Timer* pTimer_;

	//����1�ʂ̐l��ID���o���Ă���
	vector<int> No1CharaID_;

	//���݂̏��ʂ�ID�Ŋo���Ă���
	vector<int> ranking_;

	bool endGame_;
};

