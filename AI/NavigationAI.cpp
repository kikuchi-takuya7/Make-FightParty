#include "NavigationAI.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//const int moveZ[8] = { ZERO, ZERO,    1,	 -1, 1 ,1,-1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
	//const int moveX[8] = {	1,	 -1, ZERO, ZERO, 1,-1 ,1,-1 };

	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
	const int moveX[4] = {	  1,  -1,ZERO,ZERO };
}

namespace Astar {

}

NavigationAI::NavigationAI():height_(STAGE_HEIGHT),width_(STAGE_WIDTH)
{
}

NavigationAI::~NavigationAI()
{
}

void NavigationAI::Initialize()
{

	//width���̍s����height�񕪂����m�ۂ��Ă���
	for (int i = ZERO; i < height_; i++) {
		map_.emplace_back(width_);
		dist_.emplace_back(width_);
		rest_.emplace_back(width_);
	}

	//�X�e�[�W�̃R�X�g������B�ǂ�-1
	for (int i = ZERO; i < height_; i++) {
		for (int f = ZERO; f < width_; f++) {
			
			int n = ZERO;
			map_.at(i).at(f) = n;

			//rest��xz���W������
			rest_[i][f] = Pair(i, f); 
		}
	}

	
	
	

}

void NavigationAI::Release()
{
}

void NavigationAI::InitAstar()
{


	//�X�^�[�g�n�_�ƖڕW�n�_���Z�b�g����
	SetStartPos(enemyPos_.z, enemyPos_.x);

	//�����v���C���[3cpu1�݂����ȍ\�}�ɂȂ�Ƃ����炱�̑O�ɒN�_�������߂Ă����̂�����
	SetTargetPos(playerPos_.z, playerPos_.x);

	rest_.at(enemyPos_.z).at(enemyPos_.x) = Pair(enemyPos_.z, enemyPos_.x); //�X�^�[�g�n�_�̍��W
	que_.emplace(ZERO, Pair(enemyPos_.z, enemyPos_.x));//�X�^�[�g�n�_����T�����n�߂�

	target_ = std::make_pair(playerPos_.z, playerPos_.x);

	//�܂��T�����Ă��Ȃ���Ԃ̏��
	const int Inf = 9999999;
	dist_.assign(height_, vector<long>(width_, Inf));//������

	dist_.at(enemyPos_.z).at(enemyPos_.x) = map_.at(enemyPos_.z).at(enemyPos_.x); //�X�^�[�g�n�_�̃R�X�g������
}

XMFLOAT3 NavigationAI::Astar()
{
	
	InitAstar();

	while (!que_.empty())
	{
		PP now = que_.top();//������ꏊ���m��
		que_.pop();

		for (int i = ZERO; i < 4; i++) {

			int nz = now.second.first;//������ꏊ NowZ
			int nx = now.second.second;
			int sz = nz + moveZ[i];//������T������ꏊ SecondZ
			int sx = nx + moveX[i];

			// ��ʊO�Ȃ�
			if (sz < ZERO || sz >= height_ || sx < ZERO || sx >= width_) {
				continue;
			}

			//�ǂȂ�
			if (map_.at(sz).at(sx) == -1) {
				continue;
			}

			//���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{v�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
			if (dist_.at(sz).at(sx) <= dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx)) {
				continue; //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
			}

			rest_.at(sz).at(sx) = Pair(nz, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��

			//�ړI�n�ɒ�������
			if (sz == target_.first && sx == target_.second)
				break;

			dist_.at(sz).at(sx) = dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx);//�q���[���X�e�B�b�N�������݂ōŒZ�����̍X�V

			que_.emplace(PP(dist_.at(sz).at(sx), Pair(sz, sx)));//���̒T���������Ă���
		}
	}

	rest_.clear();
	dist_.clear();
	
	while (!que_.empty())
		que_.pop();

	return Path_Search();

}

XMFLOAT3 NavigationAI::Path_Search()
{

	//������n�_����
	int i = start_.first;
	int f = start_.second;

	XMFLOAT3 nextPos;

	//��񂾂��̃��[�v�ɂ���
	for (int n = ZERO; n < 4; n++) {
		int z = i;
		int x = f;
		z += moveZ[n]; //�㉺�T��
		x += moveX[n];
		if (z < ZERO || z >= height_ || x < ZERO || x >= width_) {// ��ʊO�Ȃ�
			continue;
		}
		if (rest_.at(i).at(f) != Pair(z, x)) {//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l�������Ȃ�ans�ɓ����
			continue;
		}
		nextPos = { (float)z,0,(float)x }; //�ʂ��Ă������W������
	}

	//���K�����āA���x�𒲐�����
	XMVECTOR tmp = XMLoadFloat3(&nextPos);
	tmp = XMVector3Normalize(tmp);
	nextPos = VectorToFloat3(tmp);
	nextPos = nextPos / 2;

	return nextPos;

}

int NavigationAI::Heuristic(int _x, int _z)
{
	int x = _x - target_.second;
	int z = _z - target_.first;

	return abs(x + z);
}

XMFLOAT3 NavigationAI::TeachNextPos()
{
	XMFLOAT3 nextPos = { nextPos_.second, ZERO, nextPos_.first };
	return nextPos;
}

void NavigationAI::SetStartPos(float z, float x)
{

	int zPos = (int)z;
	int xPos = (int)x;
	start_ = std::make_pair(zPos, xPos);


}

void NavigationAI::SetTargetPos(float z, float x)
{

	int zPos = (int)z;
	int xPos = (int)x;
	target_ = std::make_pair(zPos, xPos);

}
