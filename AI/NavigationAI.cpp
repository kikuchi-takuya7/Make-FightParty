#include "NavigationAI.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//const int moveZ[8] = { ZERO, ZERO,    1,	 -1, 1 ,1,-1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
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

	//width分の行を先にheight列分だけ確保しておく
	for (int i = ZERO; i < height_; i++) {
		map_.emplace_back(width_);
		dist_.emplace_back(width_);
		rest_.emplace_back(width_);
	}

	//ステージのコストを入れる。壁は-1
	for (int i = ZERO; i < height_; i++) {
		for (int f = ZERO; f < width_; f++) {

			int n = ZERO;
			map_.at(i).at(f) = n;

			//restにxz座標を入れる
			rest_[i][f] = intPair(i, f);
		}
	}

	//スタート地点と目標地点をセットする
	SetStartPos(enemyPos_.z, enemyPos_.x);

	//もしプレイヤー3cpu1みたいな構図になるとしたらこの前に誰狙うか決めておくのがいい
	SetTargetPos(playerPos_.z, playerPos_.x);

	rest_.at(enemyPos_.z).at(enemyPos_.x) = intPair(enemyPos_.z, enemyPos_.x); //スタート地点の座標
	que_.emplace(ZERO, intPair(enemyPos_.z, enemyPos_.x));//スタート地点から探索を始める

	target_ = std::make_pair(playerPos_.z, playerPos_.x);

	//まだ探索していない状態の情報
	const int Inf = 9999999;
	dist_.assign(height_, vector<long>(width_, Inf));//初期化

	dist_.at(enemyPos_.z).at(enemyPos_.x) = map_.at(enemyPos_.z).at(enemyPos_.x); //スタート地点のコストを入れる
}

XMFLOAT3 NavigationAI::Astar()
{


	//上下左右に移動（探索）するための配列
	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };
	const int moveX[4] = { 1,  -1,ZERO,ZERO };
	
	InitAstar();

	//targetまでの最短距離を求める
	while (!que_.empty())
	{
		PP now = que_.top();//今いる場所を確保
		que_.pop();

		for (int i = ZERO; i < 4; i++) {

			int nz = now.second.first;//今いる場所 NowZ
			int nx = now.second.second;
			int sz = nz + moveZ[i];//今から探索する場所 SecondZ
			int sx = nx + moveX[i];

			// 画面外なら
			if (sz < ZERO || sz >= height_ || sx < ZERO || sx >= width_) {
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

			rest_.at(sz).at(sx) = intPair(nz, nx); //最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う

			//目的地に着いたら
			if (sz == target_.first && sx == target_.second)
				break;

			dist_.at(sz).at(sx) = dist_.at(nz).at(nx) + map_.at(sz).at(sx) + Heuristic(sz, sx);//ヒューリスティック分も込みで最短距離の更新

			que_.emplace(PP(dist_.at(sz).at(sx), intPair(sz, sx)));//次の探索候補を入れておく
		}
	}

	
	dist_.clear();
	
	//queの中身を空にする
	while (!que_.empty())
		que_.pop();

	return Path_Search();

}

//てかこれもいらなくね？？て思ったけど近くの4マスだけ見ても意味ないから結局最後まで探索するのは必須で、経路探索は一マス分で十分
XMFLOAT3 NavigationAI::Path_Search()
{

	//上下左右に移動（探索）するための配列
	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };
	const int moveX[4] = { 1,  -1,ZERO,ZERO };

	//targetからスタート地点までたどりなおす
	int nz = target_.first;
	int nx = target_.second;

	//targetから探索するからstackで最後の方に獲得した座標を使うため
	std::stack <intPair> searchPos;

	//どの道をたどってきたか思い出す
	while (true) {
		for (int n = ZERO; n < 4; n++) {

			int z = nz;
			int x = nx;

			//上下探索
			z += moveZ[n];
			x += moveX[n];

			// 画面外なら
			if (z < ZERO || z >= height_ || x < ZERO || x >= width_) {
				continue;
			}

			//上下探索する時の座標とrestに入ってるその場所に行く前に居た座標と照らし合わせてその値が同じじゃないなら
			if (rest_.at(nz).at(nx) != intPair(z, x)) {
				continue;
			}

			//通ってきた座標を入れる
			searchPos.push(rest_.at(nz).at(nx));

			//次はその前にいた座標の上下左右を探索するため更新
			nz = z;  
			nx = x;
		}

		//次に探索する場所が初期位置に戻ったら止める。
		if (nz == start_.first && nx == start_.second) {
			break;
		}

	}

	XMFLOAT3 nextPos;

	//空ならやめる
	if (searchPos.empty())
		return nextPos;

	nextPos = XMFLOAT3((FLOAT)searchPos.top().second ,ZERO,(FLOAT)searchPos.top().first);

	nextPos.x = (FLOAT)searchPos.top().second;
	nextPos.y = 0.0f;
	nextPos.z = (FLOAT)searchPos.top().first;
	
	//正規化して、速度を調整する
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
