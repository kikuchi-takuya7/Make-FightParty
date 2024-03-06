#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"

//AI���_���^�[�Q�b�g�̃p�^�[��
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
class RankingUI;
class WinnerUI;
class ChampionUI;
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

	/////////�I�[�o�[���C�h�����֐�////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//���
	void Release() override;


	////////////�����o�֐�/////////////////////////////

	/// <summary>
	/// �_���ׂ�������w������֐�
	/// </summary>
	/// <param name="ID">������ID</param>
	/// <returns>�_���ׂ������ID</returns>
	int Targeting(int ID);

	/// <summary>
	/// �N���G�C�g���[�h�ŕ\�����ꂽ�I�u�W�F�N�g��I������
	/// </summary>
	/// <param name="model">�\������Ă���I�u�W�F�N�g�ꗗ</param>
	/// <returns>�ǂ̃I�u�W�F�N�g��I�񂾂�</returns>
	int SelectObject(vector<int> model);
	

	/////////�Q�[���̗�����Ǘ�����֐�////////////////

	/// <summary>
	/// ���s�����܂��Ă�����N���G�C�g���[�h�ֈڍs����֐�
	/// </summary>
	void DecidedWinner();

	/// <summary>
	/// �Q�[���̏�Ԃ����Z�b�g���ăJ�E���g�_�E������֐�
	/// </summary>
	void ResetGame();

	//////////////�A�N�Z�X�֐� ///////////////////////

	/// <summary>
	/// characterStatusList_�ɃX�e�[�^�X���v�b�V������Ɠ����ɁA���O��RankingUI�ɃZ�b�g����֐�
	/// </summary>
	/// <param name="status">�v�b�V���������X�e�[�^�X</param>
	void PushCharacterStatus(Status status);

	Status GetCharacterStatus(int ID) { return characterStatusList_.at(ID); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void ChangeStatus(int ID, Status status) { characterStatusList_.at(ID) = status; }
	void SetCreateMode(CreateMode* create) { pCreateMode_ = create; }
	vector<int> GetRanking() { return ranking_; }


private:

	//////////////////////////////private�֐�//////////////////////

	/// <summary>
	/// �D���҂����܂�������Update
	/// </summary>
	void ChampionUpdate();

	/// <summary>
	/// �ʏ펞��Update�֐�
	/// </summary>
	void UsuallyUpdate();

	/// <summary>
	/// 1�ʂ̃L����ID�͒N���A���l���邩���m�F����֐�
	/// </summary>
	void CheckNo1Chara();

	/// <summary>
	/// ���҂̏��𐮗����ăN���G�C�g���[�h�Ɉڍs����֐�
	/// </summary>
	/// <param name="winnerID">�������v���C���[��ID</param>
	void ToCreateMode(int winnerID);

	/// <summary>
	/// �Q�[���p�̃J�����ɐ؂�ւ���i���̈ʒu�ɃZ�b�g����j
	/// </summary>
	void GameCameraSet();
	
	/// <summary>
	/// �D���҂̕��ɃJ������������֐�
	/// </summary>
	void MoveChampionCam();

	/// <summary>
	/// �D���҂͒N�������߂�֐�
	/// </summary>
	/// <returns>�D�������v���C���[��ID</returns>
	int VictoryPlayer();

	/// <summary>
	/// �D���҂̎���ɃG�t�F�N�g���o���֐�
	/// </summary>
	void VictoryEffect();

	///////////////////////////////////////////�����o�ϐ�//////////////////////////

	//�S�Ẵv���C���[�̃X�e�[�^�X���o�����z��
	vector<Status> characterStatusList_;

	//NavigationAI�̃C���X�^���X
	NavigationAI* pNavigationAI_;

	//�N���G�C�g���[�h�̃C���X�^���X
	CreateMode* pCreateMode_;

	//��莞�Ԏ~�߂邽�߂̃^�C�}�[
	Timer* pWaitTimer_;

	//����1�ʂ̐l��ID���o���Ă���(������ʂ̉\�������邽�߁A��̏������y�ɂ��邽��vector��)
	vector<int> No1CharaID_;

	//���݂̏��ʂ�ID�Ŋo���Ă���
	vector<int> ranking_;

	//���݂̃X�R�A�B�v�f����ID
	vector<int> score_;

	//�������I�������true
	bool endGame_;


	////////////////////UI/////////////////////

	CountDownUI* pCountDown_;

	RankingUI* pRankingUI_;

	WinnerUI* pWinnerUI_;

	ChampionUI* pChampionUI_;


	//�Q�[��BGM
	int hAudio_;

};

