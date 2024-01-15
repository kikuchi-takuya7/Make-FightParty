#include "NavigationAI.h"

NavigationAI::NavigationAI()
{
}

NavigationAI::~NavigationAI()
{
}

void NavigationAI::Initialize()
{
	
	//これがstageの大きさになる.。いつか定数にするstageクラスから大きさ持ってこれるようにしてinitから持ってくるのが良いかな
	h_ = 30;
	w_ = 30;

	//スタート地点と目標地点をセットする
	XMFLOAT3 startPos = pEnemy_->GetPosition();
	start_ = std::make_pair(startPos.z, startPos.x);

	XMFLOAT3 targetPos = pPlayer_->GetPosition();
	target_ = std::make_pair(targetPos.z, targetPos.x);

	for (int i = 0; i < h_; i++) {
		map_.emplace_back(w_);//w分の行を先にh列分だけ確保しておく
		dist_.emplace_back(w_);
		rest_.emplace_back(w_);
	}

	//ステージのコストを入れる。壁は-1
	for (int i = 0; i < h_; i++) {
		for (int f = 0; f < w_; f++) {
			int n = 0;
			map_.at(i).at(f) = n;
			rest_[i][f] = Pair(i, f); //restにxz座標を入れる
		}
	}

	rest_.at(0).at(0) = Pair(startPos.z, startPos.x); //スタート地点の座標
	que_.emplace(0, Pair(startPos.z, startPos.x));//スタート地点から探索を始める

	target_ = std::make_pair(targetPos.z, targetPos.x);

	const int Inf = 9999999;//まだ探索していない
	dist_.assign(h_, vector<long>(w_, Inf));//初期化

	dist_.at(startPos.z).at(startPos.x) = map_.at(startPos.z).at(startPos.x); //スタート地点のコストを入れる



}

void NavigationAI::Release()
{
}

void NavigationAI::Astar()
{
	
	while (!que_.empty())
	{
		PP now = que_.top();//今いる場所を確保
		que_.pop();

		for (int i = 0; i < 4; i++) {

			int nz = now.second.first;//今いる場所 NowZ
			int nx = now.second.second;
			int sz = nz + moveZ[i];//今から探索する場所 SecondZ
			int sx = nx + moveX[i];

			// 画面外なら
			if (sz < 0 || sz >= h_ || sx < 0 || sx >= w_) {
				continue;
			}

			//壁なら
			if (map_.at(sz).at(sx) == -1) {
				continue;
			}

			//これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
			if (dist_.at(sz).at(sx) <= dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx)) {
				continue; //今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
			}

			rest_.at(sz).at(sx) = Pair(nz, nx); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う

			//目的地に着いたら
			if (sz == target_.first && sx == target_.second)
				break;

			dist_.at(sz).at(sx) = dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx);//ヒューリスティック分も込みで最短距離の更新

			que_.emplace(PP(dist_.at(sz).at(sx), Pair(sz, sx)));//次の探索候補を入れておく
		}
	}

}

void NavigationAI::Path_Search()
{

	//ゴール地点
	int i = start_.first;
	int f = start_.second;

	//一買いループだけにした
	for (int n = 0; n < 4; n++) {
		int z = i;
		int x = f;
		z += moveZ[n]; //上下探索
		x += moveX[n];
		if (z < 0 || z >= h_ || x < 0 || x >= w_) {// 画面外なら
			continue;
		}
		if (rest_.at(i).at(f) != Pair(z, x)) {//上下探索する時の座標とrestに入ってるその場所に行く前に居た座標と照らし合わせてその値が同じならansに入れる
			continue;
		}
		nextPos_ = rest_.at(i).at(f); //通ってきた座標を入れる
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
