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
using IntPair = pair<int, int>; // ���W������{ z,x }
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

	/// <summary>
	/// Astar���g���ڕW�n�_���w������
	/// </summary>
	XMFLOAT3 Astar(int ID);

	/// <summary>
	/// Astar�A���S���Y���Ŏg���o�H�����p
	/// </summary>
	/// <param name="rest">��O�ɂ������W��2�����z��ŋL����������</param>
	/// <param name="start">�X�^�[�g�n�_</param>
	/// <param name="target">�ڕW�n�_</param>
	/// <returns></returns>
	XMFLOAT3 Path_Search(vector<vector<IntPair>> rest, IntPair start, IntPair target);

	/// <summary>
	/// �q���[���X�e�B�b�N�ōŒZ�����𑪂�
	/// </summary>
	/// <param name="x">���݂�x���W</param>
	/// <param name="y">���݂�y���W</param>
	/// <param name="target">�ڕW�n�_</param>
	/// <returns>�ŒZ�����̊��Ғl</returns>
	int Heuristic(int x, int y, IntPair target);

	/// <summary>
	/// �����_�ȉ���؂�̂ĂĐ����ɂ���
	/// </summary>
	/// <param name="z">�����ɂ�����z</param>
	/// <param name="x">�����ɂ�����x</param>
	/// <returns>�����ɂ���IntPair</returns>
	IntPair FloatToIntPair(float z, float x);


	float Distance(int ID);
	
	//////////////�A�N�Z�X�֐�//////////////
	void PushEnemy(Enemy* enemy) { pEnemyList_.push_back(enemy); }
	void PushPlayer(Player* player) { pPlayerList_.push_back(player); }

private:

	/////////////////Astar�A���S���Y���Ŏg��///////////

	//�X�e�[�W�̏c���Ɖ���
	int height_, width_; 
	
	

	/////////////////////////////�ʒu���////////////////////////

	//enemy�ƃv���C���[�̈ʒu���o���Ă���
	vector<Player*> pPlayerList_;
	vector<Enemy*> pEnemyList_;
	
};

