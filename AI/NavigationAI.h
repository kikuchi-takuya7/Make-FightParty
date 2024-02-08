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


class Character;
class CharacterAI;

/// <summary>
/// �L�����N�^�[AI�ƃ��^AI�ɏ���񋟂���
/// </summary>
class NavigationAI : public AI
{
	//
public:

	//�R���X�g���N�^
	NavigationAI(GameObject* parent);

	//�f�X�g���N�^
	~NavigationAI();

	///////////�I�[�o�[���C�h�����֐�/////////
	
	//������
	void Initialize() override;
	
	//���
	void Release() override;

	//////////�����o�֐�///////////////


	Transform MoveSelectObject(int ID);

	void AllResetStatus();

	void AllStopDraw();

	void AllStartDraw();

	float Distance(int myID, int targetID);


	//////////////////Astar�A���S���Y���Ŏg���֐�//////////////////
	
	/// <summary>
	/// Astar���g���ڕW�n�_��T������
	/// </summary>
	XMFLOAT3 Astar(int myID, int targetID);

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


	
	//////////////�A�N�Z�X�֐�//////////////
	//void PushEnemy(Enemy* enemy) { pEnemyList_.push_back(enemy); }
	//void PushPlayer(Player* player) { pPlayerList_.push_back(player); }
	void PushCharacter(Character* chara) { pCharacterList_.emplace_back(chara); }
	void PushCharacterAI(CharacterAI* AI) { pCharacterAIList_.emplace_back(AI); }

private:

	/////////////////Astar�A���S���Y���Ŏg��///////////

	//�X�e�[�W�̏c���Ɖ���
	int height_, width_; 
	
	

	/////////////////////////////Character�̏��////////////////////////

	vector<Character*> pCharacterList_;

	vector<CharacterAI*> pCharacterAIList_;
	
};

