#include "NavigationAI.h"

NavigationAI::NavigationAI()
{
}

NavigationAI::~NavigationAI()
{
}

void NavigationAI::Initialize()
{
	
	//���ꂪstage�̑傫���ɂȂ�
	h_ = 30;
	w_ = 30;


	start_ = std::make_pair(-1, -1);//�X�^�[�g�n�_����T�����n�߂�
	target_ = std::make_pair(-1, -1);

	for (int i = 0; i < h_; i++) {
		map_.emplace_back(w_);//w���̍s����h�񕪂����m�ۂ��Ă���
		dist_.emplace_back(w_);
		rest_.emplace_back(w_);
	}

	//�ǂ�-1�ł������?
	for (int f = 0; f < w_; f++) {
		int n = 0;
		cin >> n;
		map_.at(i).at(f) = n;
		rest_[i][f] = Pair(i, f); //rest��xy���W������
	}


	if (map_.at(y).at(x) == -1) {
		cout << "�܂������Ă܂���" << endl;
		return;
	}

	start_ = std::make_pair(y, x);//�X�^�[�g�n�_����T�����n�߂�
	rest_.at(0).at(0) = Pair(y, x); //�X�^�[�g�n�_�̍��W
	que_.emplace(0, Pair(y, x));//�X�^�[�g�n�_����T�����n�߂�

	cout << "�S�[������" << endl;
	int goalX, goalY;
	cout << "X = "; cin >> goalX;
	cout << "Y = "; cin >> goalY;
	goalX -= 1;
	goalY -= 1;

	if (map_.at(goalY).at(goalX) == -1) {
		cout << "�܂������Ă܂���" << endl;
		return;
	}

	target_ = std::make_pair(goalY, goalX);

	const int Inf = 9999999;//�܂��T�����Ă��Ȃ�
	dist_.assign(h_, vector<long long>(w_, Inf));//������

	dist_.at(y).at(x) = map_.at(y).at(x); //�X�^�[�g�n�_�̃R�X�g������



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

			int ny = now.second.first;//������ꏊ NowY
			int nx = now.second.second;
			int sy = ny + moveY[i];//������T������ꏊ SecondY
			int sx = nx + moveX[i];

			// ��ʊO�Ȃ�
			if (sy < 0 || sy >= h_ || sx < 0 || sx >= w_) {
				continue;
			}

			//�ǂȂ�
			if (map_.at(sy).at(sx) == -1) {
				continue;
			}

			//���ꂩ��T������Ƃ��낪������ʒu����s���Ƃ����܂ł̍ŒZ�����idist�{v�̃R�X�g���ō����݂킩���Ă���ŒZ�����j�łȂ��Ȃ�B
			if (dist_.at(sy).at(sx) <= dist_.at(ny).at(nx) + map_.at(sy).at(sx)) {
				continue; //������T�����悤�Ƃ��Ă�ꏊ�͂�����x���s���ĂȂ�������INF�������ĂĐ�΍X�V�����
			}

			rest_.at(sy).at(sx) = Pair(ny, nx); //�ŒZ�o�H���o���T���ς݂̍��W�ɒT���O�ǂ��ɂ������̏������Č�Ōo�H�����Ɏg��
			dist_.at(sy).at(sx) = dist_.at(ny).at(nx) + map_.at(sy).at(sx) + Heuristic(sy, sx);//�q���[���X�e�B�b�N�������݂ōŒZ�����̍X�V

			que_.emplace(PP(dist_.at(sy).at(sx), Pair(sy, sx)));//���̒T���������Ă���
		}
	}

}

void NavigationAI::Path_Search()
{

	//�S�[���n�_
	int i = target_.first;
	int f = target_.second;

	cout << dist_.at(i).at(f) << endl;//�p�C�U�͉E�����S�[���̂��߃S�[���̈ʒu�܂ł̍ŒZ�R�X�g��\��

	ans_.emplace(i, f);//�S�[���n�_�������炩���ߓ���Ƃ�

	while (true) {

		for (int n = 0; n < 4; n++) {
			int y = i;
			int x = f;
			y += moveY[n]; //�㉺�T��
			x += moveX[n];
			if (y < 0 || y >= h_ || x < 0 || x >= w_) {// ��ʊO�Ȃ�
				continue;
			}
			if (rest_.at(i).at(f) != Pair(y, x)) {//�㉺�T�����鎞�̍��W��rest�ɓ����Ă邻�̏ꏊ�ɍs���O�ɋ������W�ƏƂ炵���킹�Ă��̒l�������Ȃ�ans�ɓ����
				continue;
			}
			ans_.emplace(rest_.at(i).at(f)); //�ʂ��Ă������W������
			i = y;  //���͂��̑O�ɂ������W�̏㉺���E��T�����邽�ߍX�V
			f = x;  //rest�̒l�����悤�Ƃ����i��f�ŒT�����邽�ߒl�������ɍX�V����Ă��܂��Ȃ���p�ł��������Ȃ��Ă��܂�
		}

		if (i == start_.first && f == start_.second) {//�����ʒu�ɖ߂�����
			break;
		}
	}

}

int NavigationAI::Heuristic(int _x, int _y)
{
	return 0;
}
