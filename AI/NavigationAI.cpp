#include "NavigationAI.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//const int moveZ[8] = { ZERO, ZERO,    1,	 -1, 1 ,1,-1,-1 };//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��B��܂Ƃ߂ďc�Ɍ���Ə㉺���E
	//const int moveX[8] = {	1,	 -1, ZERO, ZERO, 1,-1 ,1,-1 };

	
}

namespace Astar {

}

NavigationAI::NavigationAI():height_(STAGE_HEIGHT),width_(STAGE_WIDTH)
{
	playerPos_ = { 0,0,0 };
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

void NavigationAI::InitAstar()
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
			rest_[i][f] = intPair(i, f);
		}
	}

	//�X�^�[�g�n�_�ƖڕW�n�_���Z�b�g����
	SetStartPos(enemyPos_.z, enemyPos_.x);

	//�����v���C���[3cpu1�݂����ȍ\�}�ɂȂ�Ƃ����炱�̑O�ɒN�_�������߂Ă����̂�����
	SetTargetPos(playerPos_.z, playerPos_.x);

	rest_.at(enemyPos_.z).at(enemyPos_.x) = intPair(enemyPos_.z, enemyPos_.x); //�X�^�[�g�n�_�̍��W
	que_.emplace(ZERO, intPair(enemyPos_.z, enemyPos_.x));//�X�^�[�g�n�_����T�����n�߂�

	target_ = std::make_pair(playerPos_.z, playerPos_.x);

	//�܂��T�����Ă��Ȃ���Ԃ̏��
	const int Inf = 9999999;
	dist_.assign(height_, vector<long>(width_, Inf));//������

	dist_.at(enemyPos_.z).at(enemyPos_.x) = map_.at(enemyPos_.z).at(enemyPos_.x); //�X�^�[�g�n�_�̃R�X�g������
}

XMFLOAT3 NavigationAI::Astar()
{


	//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��
	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };
	const int moveX[4] = { 1,  -1,ZERO,ZERO };
	
	InitAstar();

	//target�܂ł̍ŒZ���������߂�
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

			rest_.at(sz).at(sx) = intPair(nz, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��

			//�ړI�n�ɒ�������
			if (sz == target_.first && sx == target_.second)
				break;

			dist_.at(sz).at(sx) = dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx);//�q���[���X�e�B�b�N�������݂ōŒZ�����̍X�V

			que_.emplace(PP(dist_.at(sz).at(sx), intPair(sz, sx)));//���̒T���������Ă���
		}
	}

	
	dist_.clear();
	
	//que�̒��g����ɂ���
	while (!que_.empty())
		que_.pop();

	return Path_Search();

}

//�Ă����������Ȃ��ˁH�H�Ďv�������ǋ߂���4�}�X�������Ă��Ӗ��Ȃ����猋�ǍŌ�܂ŒT������͕̂K�{�ŁA�o�H�T���͈�}�X���ŏ\��
XMFLOAT3 NavigationAI::Path_Search()
{

	//�㉺���E�Ɉړ��i�T���j���邽�߂̔z��
	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };
	const int moveX[4] = { 1,  -1,ZERO,ZERO };

	//target����X�^�[�g�n�_�܂ł��ǂ�Ȃ���
	int nz = target_.first;
	int nx = target_.second;

	//target����T�����邩��stack�ōŌ�̕��Ɋl���������W���g������
	std::stack <intPair> searchPos;

	//�ǂ̓������ǂ��Ă������v���o��
	while (true) {
		for (int n = ZERO; n < 4; n++) {

			int z = nz;
			int x = nx;

			//�㉺�T��
			z += moveZ[n];
			x += moveX[n];

			// ��ʊO�Ȃ�
			if (z < ZERO || z >= height_ || x < ZERO || x >= width_) {
				continue;
			}

			//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l����������Ȃ��Ȃ�
			if (rest_.at(nz).at(nx) != intPair(z, x)) {
				continue;
			}

			//�ʂ��Ă������W������
			searchPos.push(rest_.at(nz).at(nx));

			//���͂��̑O�ɂ������W�̏㉺���E��T�����邽�ߍX�V
			nz = z;  
			nx = x;
		}

		//���ɒT������ꏊ�������ʒu�ɖ߂�����~�߂�B
		if (nz == start_.first && nx == start_.second) {
			break;
		}

	}

	XMFLOAT3 nextPos;

	//��Ȃ��߂�
	if (searchPos.empty())
		return nextPos;

	nextPos = XMFLOAT3((FLOAT)searchPos.top().second ,ZERO,(FLOAT)searchPos.top().first);

	nextPos.x = (FLOAT)searchPos.top().second;
	nextPos.y = 0.0f;
	nextPos.z = (FLOAT)searchPos.top().first;
	
	//���K�����āA���x�𒲐�����
	XMVECTOR tmp = XMLoadFloat3(&nextPos);
	tmp = XMVector3Normalize(tmp);
	nextPos = VectorToFloat3(tmp);
	nextPos = nextPos / 10;

	rest_.clear();

	return nextPos;

}

int NavigationAI::Heuristic(int _x, int _z)
{
	int x = _x - target_.second;
	int z = _z - target_.first;

	return abs(x + z);
}

//XMFLOAT3 NavigationAI::TeachNextPos()
//{
//	XMFLOAT3 nextPos = { (float)teachPath_.second, ZERO, nextPos_.first };
//
//}

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
