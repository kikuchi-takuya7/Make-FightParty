#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>

//const int moveZ[8] = { 0, 0, 1,-1, 1 ,1,-1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
//const int moveX[8] = { 1,-1, 0, 0, 1,-1 ,1,-1 };

const int moveZ[4] = { 0,0,1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
const int moveX[4] = { 1,-1,0,0 };

//pair����Ȃ���struct�ɂ��������������H
using std::vector;
using std::pair;
using Pair = pair<int, int>; // { z,x }
using Graph = vector<vector<long>>; //�񎟌��z���̃O���t
using PP = pair<long, pair<int, int>>;//first�ɃR�X�g�Bsecond�ɂ��̃R�X�g�̈ʒu�Ɠ������W������
using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //�����ŗv�f�����Ă���.�������ď����������ĈӖ��������

/// <summary>
/// �L�����N�^�[AI�ƃ��^AI�ɏ���񋟂���
/// </summary>
class NavigationAI : AI
{
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

	void Astar();

	void Path_Search();

	int Heuristic(int _x, int _y);


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
	
	


private:

	int h_, w_; //�c���Ɖ���
	
	//�X�^�[�g�ƃS�[����float�ɂ����ق��������H������
	Pair start_;
	Pair target_;

	Graph map_;    //�}�b�v�̃R�X�g������B
	Graph dist_; //�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̕����ōs���邩�ǉ�����
	vector<vector<Pair>> rest_; //�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���

	PqPP que_; //�T���ς݂̏ꏊ���L�����Ă����B��x�s�����ꏊ���������W�ŉ����тŊo���Ă����΂���
	//new���� �q���[���X�e�B�b�N�ŒT�������v����ԋ߂�����Ă���ł����񂶂��
	//���̈ʒu�܂ł̃q���[���X�e�B�b�N�ƃR�X�g�����킹����Ȃ�Ȃ肷��Ƃ���

	Pair nextPos_;//�O��stack��target�܂ł̈ʒu��S���ۑ����Ă����ǂP�}�X���T�����������ǂ�����

	GameObject* pEnemy_;
	GameObject* pPlayer_;
	
};

