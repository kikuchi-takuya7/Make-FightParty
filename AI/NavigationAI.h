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

class Player;
class Enemy;

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

	XMFLOAT3 Path_Search(vector<vector<intPair>> rest, intPair start, intPair target);

	int Heuristic(int x, int y, intPair target);

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
	

	intPair FloatToIntPair(float z, float x);

	/*void SetEnemyPos(float z, float x) { enemyPos_ = { x,0,z }; }
	void SetEnemyPos(XMFLOAT3 pos) { enemyPos_ = { pos.x,0,pos.z }; }
	void SetPlayerPos(float z, float x) { playerPos_ = { x,0,z }; }
	void SetPlayerPos(XMFLOAT3 pos) { playerPos_ = { pos.x,0,pos.z }; }*/

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetPlayer(Player* player) { pPlayer_ = player; }

private:

	/////////////////Astar�A���S���Y���Ŏg��///////////

	//�X�e�[�W�̏c���Ɖ���
	int height_, width_; 
	
	

	/////////////////////////////�ʒu���////////////////////////

	//enemy�ƃv���C���[�̈ʒu���o���Ă���
	Player* pPlayer_;
	Enemy* pEnemy_;
	
};

