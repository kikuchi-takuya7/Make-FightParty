#include "NavigationAI.h"
#include "../Engine/Input.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//�R�X�g��1�ɂ�����o�H�����̏��Ŗ������[�v���Ă��܂��B
	const int STAGE_COST = 1;

	//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
	/*const int moveZ[8] = {  1, 1,-1,-1, ZERO, ZERO,    1,   -1 };
	const int moveX[8] = {	1,-1, 1,-1,    1,   -1, ZERO, ZERO };*/

	//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��
	const int moveZ[8] = { ZERO,ZERO,	1,	-1, 1, 1,-1,-1 };
	const int moveX[8] = {    1,  -1,ZERO,ZERO, 1,-1, 1,-1 };
}

namespace Astar {

}

NavigationAI::NavigationAI(GameObject* parent)
	:AI(parent, "NavigationAI"), height_(STAGE_HEIGHT),width_(STAGE_WIDTH)
{
	//targetPos = { 15,0,15 };
}

NavigationAI::~NavigationAI()
{
}

void NavigationAI::Initialize()
{

	
}

void NavigationAI::Release()
{
}

//�O���b�h���Astar�A���S���Y�����g���ŒZ������T��
XMFLOAT3 NavigationAI::Astar(int myID, int targetID)
{

	//�T�����n�߂�ꏊ�ƖڕW�n�_
	IntPair start;
	IntPair target;

	//�����I��MetaAI�ɑ_���ׂ��G�𕷂�����
	XMFLOAT3 startPos = pCharacterList_.at(myID)->GetPosition();
	XMFLOAT3 targetPos = pCharacterList_.at(targetID)->GetPosition();

	//�X�^�[�g�n�_�ƖڕW�n�_�������_��؂�̂ĂăZ�b�g����
	start = FloatToIntPair(startPos.z, startPos.x);
	target = FloatToIntPair(targetPos.z, targetPos.x);

	//���ɖڕW�n�_�ɂ���Ȃ�Έړ����Ȃ�
	if (start == target)
		return ZERO_FLOAT3;

	//�}�b�v�̃R�X�g������B
	Graph map;

	//�}�b�v�̈ʒu�ɘA�����Ă��̒��_�܂łǂ̂��炢�̕����ōs���邩�ǉ�����
	Graph dist;

	//�o�H�����Ɏg�p���邽�߁A���̒��ɂ͈�O�ɂ���xy���W�����Ă���
	vector<vector<IntPair>> rest;
	
	//width���̍s����height�񕪂����m�ۂ��Ă���
	for (int i = ZERO; i < height_; i++) {
		map.emplace_back(width_);
		dist.emplace_back(width_);
		rest.emplace_back(width_);
	}

	//�X�e�[�W�̃R�X�g������B�ǂ�-1.�����I��stage���玝���Ă���\��
	for (int i = ZERO; i < height_; i++) {
		for (int f = ZERO; f < width_; f++) {

			map.at(i).at(f) = STAGE_COST;

			//rest��xz���W������
			rest[i][f] = IntPair(i, f);
		}
	}

	//�X�^�[�g�n�_�̍��W
	rest.at(start.first).at(start.second) = IntPair(start.first, start.second);
	
	//�T���ς݂̏ꏊ�������ŋL�����Ă����Btop�ŗv�f���Ăяo��������first�̈�Ԓl���������̂������Ă��Ă����
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que;

	//�X�^�[�g�n�_����T�����n�߂�
	que.emplace(ZERO, IntPair(start.first, start.second));

	//���肦�Ȃ��l�̏��ŏ�����
	const int Inf = 9999999;
	dist.assign(height_, vector<long>(width_, Inf));

	//�X�^�[�g�n�_�̃R�X�g������
	dist.at(start.first).at(start.second) = map.at(start.first).at(start.second);

	//target�܂ł̍ŒZ���������߂�
	while (!que.empty())
	{
		//������ꏊ���m��
		PP now = que.top();
		que.pop();

		bool isBreak = false;

		for (int i = ZERO; i < ARRAYSIZE(moveZ); i++) {

			//������ꏊ NowZ
			int nz = now.second.first;
			int nx = now.second.second;
			//������T������ꏊ SecondZ
			int sz = nz + moveZ[i];
			int sx = nx + moveX[i];

			int cost = ZERO;
			
			// ��ʊO�Ȃ�
			if (sz < ZERO || sz >= height_ || sx < ZERO || sx >= width_) {
				continue;
			}

			//�ǂȂ�
			if (map.at(sz).at(sx) == -1) {
				continue;
			}

			//���Ǝ��̍s����ŒZ����(�q���[���X�e�B�b�N)������Ă���
			int secondH = Heuristic(sz, sx, target);
			int nowH = Heuristic(nz, nx, target);

			//�΂߈ړ��ɃR�X�g������B�R�X�g�����Ȃ��Ǝ΂߈ړ��������Ȃ��Ȃ��Ă��܂���.Astar�ɂƂ��Ă͎΂߈ړ����㉺�ړ��������X�s�[�h������
			if (i > 3) {
				cost = 1;
			}

#if 0
			//���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{map�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
			if (dist.at(sz).at(sx) <= dist.at(nz).at(nx) + map.at(sz).at(sx) + cost) {
				continue;
			}

			//�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			rest.at(sz).at(sx) = IntPair(nz, nx);

			//�ړI�n�ɒ�������
			if (sz == target.first && sx == target.second) {

				isBreak = true;
				break;
			}

			//�ŒZ�����̍X�V
			dist.at(sz).at(sx) = map.at(sz).at(sx) + cost + secondH;

			//���̒T���������Ă���.�q���[���X�e�B�b�N�����܂߂��R�X�g,�ꏊ
			que.emplace(PP(dist.at(sz).at(sx), IntPair(sz, sx)));
#else
			//���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{map+�q���[���X�e�B�b�N�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
			if (dist.at(sz).at(sx) + secondH <= dist.at(nz).at(nx) + map.at(sz).at(sx) + nowH + cost) {
				//������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
				continue;
			}

			//�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			rest.at(sz).at(sx) = IntPair(nz, nx);

			//�ړI�n�ɒ�������
			if (sz == target.first && sx == target.second) {

				isBreak = true;
				break;
			}

			//�����ɍs���܂ł̍ŒZ�����̍X�V�i�q���[���X�e�B�b�N�𑫂��Ă��܂��ƒl�����������ĒT�����œK���ł��Ȃ��j
			dist.at(sz).at(sx) = dist.at(nz).at(nx) + map.at(sz).at(sx) + cost;

			//���̒T���������Ă���
			que.emplace(PP(dist.at(sz).at(sx) + secondH, IntPair(sz, sx)));
#endif
			
		}

		if (isBreak)
			break;

	}

	XMFLOAT3 nextPos = Path_Search(rest, start, target);

	return nextPos;

}

//�o�H����
XMFLOAT3 NavigationAI::Path_Search(vector<vector<IntPair>> rest,IntPair start, IntPair target)
{

	//target����X�^�[�g�n�_�܂ł��ǂ�Ȃ���
	int nz = target.first;
	int nx = target.second;

	//target����T�����邩��stack�ōŌ�̕��Ɋl���������W���g������
	std::stack <IntPair> searchPos;

	//�ǂ̓������ǂ��Ă������v���o��
	while (true) {
		for (int n = ZERO; n < ARRAYSIZE(moveZ); n++) {

			int z = nz;
			int x = nx;

			//�㉺�T��
			z += moveZ[n];
			x += moveX[n];

			//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l����������Ȃ��Ȃ�
			if (rest.at(nz).at(nx) != IntPair(z, x)) {
				continue;
			}

			// ��ʊO�Ȃ�
			if (z < ZERO || z >= height_ || x < ZERO || x >= width_) {
				continue;
			}

			//�ʂ��Ă������W������
			searchPos.emplace(rest.at(nz).at(nx));

			//���͂��̑O�ɂ������W�̏㉺���E��T�����邽�ߍX�V
			nz = z;  
			nx = x;

			break;
		}

		//���ɒT������ꏊ�������ʒu�ɖ߂�����~�߂�B
		if (nz == start.first && nx == start.second) {
			break;
		}

	}


	XMFLOAT3 fMove = ZERO_FLOAT3;

	//��ԏ�ɂ͊J�n�ʒu�������Ă邩�炻�����菜��
	searchPos.pop();

	//��Ȃ��߂�
	if (searchPos.empty())
		return fMove;	

	//stack��top�͈�ԍŌ�̗v�f������Ă���
	int checkVecZ = start.first - searchPos.top().first;
	int checkVecX = start.second - searchPos.top().second;

	//���艟���ŏC�����邱�Ƃ��ł��邯�Ǘǂ��Ȃ��C������
	if (start.first == target.first) {
		checkVecZ = 0;
	}
	if (start.second == target.second) {
		checkVecX = 0;
	}


	if (checkVecX == 1) {
		
		fMove.x = -1.0f;
	}
	if (checkVecX == -1) {
		
		fMove.x = 1.0f;
	}
	if (checkVecZ == 1) {
		
		fMove.z = -1.0f;
	}
	if (checkVecZ == -1) {

		fMove.z = 1.0f;
	}

	//�����������x�N�g�����m�F
	XMVECTOR vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);
	fMove = VectorToFloat3(vMove);
	fMove = fMove * 0.1;	

	return fMove;

}


int NavigationAI::Heuristic(int z, int x, IntPair target)
{
	//��Βl�̍����Ƃ�
	int tmpX = abs(target.second - x);
	int tmpZ = abs(target.first - z);

	//�΂߈ړ��Ȃ̂ő傫���ق���Ԃ�
	return max(tmpZ, tmpX);
}

//XMFLOAT3 NavigationAI::TeachNextPos()
//{
//	XMFLOAT3 fMove = { (float)teachPath_.second, ZERO, nextPos_.first };
//
//}


IntPair NavigationAI::FloatToIntPair(float z, float x)
{

	
	int zPos = (int)z;
	int xPos = (int)x;
	IntPair pair = std::make_pair(zPos, xPos);

	return pair;
}

//�����Ŏ����ƃ^�[�Q�b�g�������Ă���̂��l�����B�ǂ�������������
float NavigationAI::Distance(int myID, int targetID)
{
	
	//�����I��MetaAI�ɑ_���ׂ��G�𕷂�����
	XMFLOAT3 eP = pCharacterList_.at(myID)->GetPosition();
	XMFLOAT3 pP = pCharacterList_.at(targetID)->GetPosition();

	//�s�^�S���X�̒藝�ŋ��������߂���炵��
	float distance = pow((pP.x - eP.x) * (pP.x - eP.x) + (pP.y - eP.y) * (pP.y - eP.y) + (pP.z - eP.z) * (pP.z - eP.z), 0.5);

	return distance;
}
