#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>

//z,x�̈ʒu�֌W���p�b�ƌ��₷������pair�ɂ������ǁAstruct�ɂ������������H
using std::vector;
using std::pair;
using intPair = pair<int, int>; // ���W������{ z,x }
using Graph = vector<vector<long>>; //�񎟌��z��Ń}�b�v��R�X�g��\��
using PP = pair<long, pair<int, int>>;//first�ɃR�X�g�Bsecond�ɂ��̃R�X�g�̈ʒu�Ɠ������W������

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
	//XMFLOAT3 TeachNextPos();
	
	/// <summary>
	/// �����u���b�N���ɂ��邩�ǂ���
	/// </summary>
	/// <param name="pos1">��ׂ����l�P</param>
	/// <param name="pos2">��ׂ����l�Q</param>
	/// <returns>�����ꏊ�ɂ���Ȃ�true��Ԃ�</returns>
	bool IsSomePos(XMFLOAT3 pos1, XMFLOAT3 pos2);

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

	/////////////////Astar�A���S���Y���Ŏg��///////////

	//�X�e�[�W�̏c���Ɖ���
	int height_, width_; 
	
	//�X�^�[�g�ƃS�[����float�ɂ����ق��������H������
	intPair start_;
	intPair target_;

	//�}�b�v�̃R�X�g������B
	Graph map_;    

	//�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̕����ōs���邩�ǉ�����
	Graph dist_;
	
	//�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���
	vector<vector<intPair>> rest_; 

	//�T���ς݂̏ꏊ�������ŋL�����Ă���
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que_; 

	//A*�A���S���Y���𐮐��̃O���b�h�`���œǂݍ���ł��邽�߁A�����ȉ���ۑ����Ă���
	pair<float, float> decimal_;

	/////////////////////////////�ʒu���////////////////////////

	//�������S������enemy�ƃv���C���[�̈ʒu���o���Ă���
	XMFLOAT3 enemyPos_;
	XMFLOAT3 playerPos_;
	
};

