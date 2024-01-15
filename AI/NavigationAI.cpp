#include "NavigationAI.h"

NavigationAI::NavigationAI()
{
}

NavigationAI::~NavigationAI()
{
}

void NavigationAI::Initialize()
{
	
	//���ꂪstage�̑傫���ɂȂ�.�B�����萔�ɂ���stage�N���X����傫�������Ă����悤�ɂ���init���玝���Ă���̂��ǂ�����
	h_ = 30;
	w_ = 30;

	//�X�^�[�g�n�_�ƖڕW�n�_���Z�b�g����
	XMFLOAT3 startPos = pEnemy_->GetPosition();
	start_ = std::make_pair(startPos.z, startPos.x);

	XMFLOAT3 targetPos = pPlayer_->GetPosition();
	target_ = std::make_pair(targetPos.z, targetPos.x);

	for (int i = 0; i < h_; i++) {
		map_.emplace_back(w_);//w���̍s����h�񕪂����m�ۂ��Ă���
		dist_.emplace_back(w_);
		rest_.emplace_back(w_);
	}

	//�X�e�[�W�̃R�X�g������B�ǂ�-1
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //rest��xz���W������
		}
	}

	rest_.at(0).at(0) = Pair(startPos.z, startPos.x); //�X�^�[�g�n�_�̍��W
	que_.emplace(0, Pair(startPos.z, startPos.x));//�X�^�[�g�n�_����T�����n�߂�

	target_ = std::make_pair(targetPos.z, targetPos.x);

	const int Inf = 9999999;//�܂��T�����Ă��Ȃ�
	dist_.assign(h_, vector<long>(w_, Inf));//������

	dist_.at(startPos.z).at(startPos.x) = map_.at(startPos.z).at(startPos.x); //�X�^�[�g�n�_�̃R�X�g������



}

void NavigationAI::Release()
{
}

void NavigationAI::Astar()
{
	
	while (!que_.empty())
	{
		PP now = que_.top();//������ꏊ���m��
		que_.pop();

		for (int i = 0; i < 4; i++) {

			int nz = now.second.first;//������ꏊ NowZ
			int nx = now.second.second;
			int sz = nz + moveZ[i];//������T������ꏊ SecondZ
			int sx = nx + moveX[i];

			// ��ʊO�Ȃ�
			if (sz < 0 || sz >= h_ || sx < 0 || sx >= w_) {
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

}

void NavigationAI::Path_Search()
{

	//�S�[���n�_
	int i = start_.first;
	int f = start_.second;

	//�ꔃ�����[�v�����ɂ���
	for (int n = 0; n < 4; n++) {
		int z = i;
		int x = f;
		z += moveZ[n]; //�㉺�T��
		x += moveX[n];
		if (z < 0 || z >= h_ || x < 0 || x >= w_) {// ��ʊO�Ȃ�
			continue;
		}
		if (rest_.at(i).at(f) != Pair(z, x)) {//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l�������Ȃ�ans�ɓ����
			continue;
		}
		nextPos_ = rest_.at(i).at(f); //�ʂ��Ă������W������
	}

}

int NavigationAI::Heuristic(int _x, int _z)
{
	int x = _x - target_.second;
	int z = _z - target_.first;

	return abs(x + z);
}

void NavigationAI::SetStartPos(float z, float x)
{
}

void NavigationAI::SetTargetPos(float z, float x)
{
}
