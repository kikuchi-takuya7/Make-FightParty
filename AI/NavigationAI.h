#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>


//pair����Ȃ���struct�ɂ��������������H
using std::vector;
using std::pair;
using Pair = pair<int, int>; // ���W������{ z,x }
using Graph = vector<vector<long>>; //�񎟌��z���̃O���t
using PP = pair<long, pair<int, int>>;//first�ɃR�X�g�Bsecond�ɂ��̃R�X�g�̈ʒu�Ɠ������W������
//using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //�����ŗv�f�����Ă���.�������ď����������ĈӖ��������

/// <summary>
/// �L�����N�^�[AI�ƃ��^AI�ɏ���񋟂���
/// </summary>
class NavigationAI : AI
{
	//
public:

	//�R���X�g���N�^
	NavigationAI();

	//�f�X�g���N�^
	~NavigationAI();

	///////////�I�[�o�[���C�h�����֐�/////////
	
	//������
	void Initialize() override;
	
	//���
	void Release() override;

	//////////�����o�֐�///////////////

	void InitAstar();

	XMFLOAT3 Astar();

	XMFLOAT3 Path_Search();

	int Heuristic(int _x, int _y);

	/// <summary>
	/// ���ɍs���ׂ����W��������
	/// </summary>
	/// <returns>���̍��W</returns>
	XMFLOAT3 TeachNextPos();

	//////////////�A�N�Z�X�֐�//////////////
	
	/// <summary>
	/// �T�����n�߂�ʒu
	/// </summary>
	/// <param name="z">�n�߂�ʒu��z���W</param>
	/// <param name="x">�n�߂�ʒu��x���W</param>
	void SetStartPos(float z, float x);

	/// <summary>
	/// �ڕW�Ƃ���ʒu
	/// </summary>
	/// <param name="z">�ڕW�̈ʒu��z���W</param>
	/// <param name="x">�ڕW�̈ʒu��x���W</param>
	void SetTargetPos(float z, float x);
	
	void SetEnemyPos(float z, float x) { enemyPos_ = { x,0,z }; }
	void SetEnemyPos(XMFLOAT3 pos) { enemyPos_ = { pos.x,0,pos.z }; }
	void SetPlayerPos(float z, float x) { playerPos_ = { x,0,z }; }
	void SetPlayerPos(XMFLOAT3 pos) { playerPos_ = { pos.x,0,pos.z }; }

private:

	int height_, width_; //�X�e�[�W�̏c���Ɖ���
	
	//�X�^�[�g�ƃS�[����float�ɂ����ق��������H������
	Pair start_;
	Pair target_;

	//�}�b�v�̃R�X�g������B
	Graph map_;    

	//�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̕����ōs���邩�ǉ�����
	Graph dist_;
	
	//�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���
	vector<vector<Pair>> rest_; 

	//�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W���������тŊo���Ă����΂���
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que_; 

	//�O��stack��target�܂ł̈ʒu��S���ۑ����Ă����ǂP�}�X���T�����������ǂ�����
	pair<float, float> nextPos_;

	//�������S������enemy�ƃv���C���[�̈ʒu���o���Ă���
	XMFLOAT3 enemyPos_;
	XMFLOAT3 playerPos_;
	
};

