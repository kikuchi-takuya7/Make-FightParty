#include "NavigationAI.h"
#include "../Engine/Input.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//const int moveZ[8] = { ZERO, ZERO,    1,	 -1, 1 ,1,-1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
	//const int moveX[8] = {	1,	 -1, ZERO, ZERO, 1,-1 ,1,-1 };

	//上下左右に移動（探索）するための配列
	const int moveZ[4] = { ZERO,ZERO,	1,	-1 };
	const int moveX[4] = { 1,  -1,ZERO,ZERO };
}

namespace Astar {

}

NavigationAI::NavigationAI():height_(STAGE_HEIGHT),width_(STAGE_WIDTH),pPlayer_(nullptr), pEnemy_(nullptr)
{
	//playerPos = { 15,0,15 };
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

	
}

XMFLOAT3 NavigationAI::Astar()
{

	//探索を始める場所と目標地点
	intPair start;
	intPair target;

	XMFLOAT3 enemyPos = pEnemy_->GetPosition();
	XMFLOAT3 playerPos = pPlayer_->GetPosition();

	//スタート地点と目標地点をセットする
	start = FloatToIntPair(enemyPos.z, enemyPos.x);
	target = FloatToIntPair(playerPos.z, playerPos.x);

	//既に目標地点にいるならば移動しない
	if (start == target)
		return ZERO_FLOAT3;

	//マップのコストを入れる。
	Graph map;

	//マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	Graph dist;

	//経路復元に使用するため、この中には一個前にいたxy座標を入れておく
	vector<vector<intPair>> rest;
	
	//width分の行を先にheight列分だけ確保しておく
	for (int i = ZERO; i < height_; i++) {
		map.emplace_back(width_);
		dist.emplace_back(width_);
		rest.emplace_back(width_);
	}

	//ステージのコストを入れる。壁は-1
	for (int i = ZERO; i < height_; i++) {
		for (int f = ZERO; f < width_; f++) {

			int n = ZERO;
			map.at(i).at(f) = n;

			//restにxz座標を入れる
			rest[i][f] = intPair(i, f);
		}
	}

	//スタート地点の座標
	rest.at(enemyPos.z).at(enemyPos.x) = intPair(enemyPos.z, enemyPos.x); 
	
	//探索済みの場所を昇順で記憶しておく
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que;

	//スタート地点から探索を始める
	que.emplace(ZERO, intPair(enemyPos.z, enemyPos.x));

	//ありえない値の情報で初期化
	const int Inf = 9999999;
	dist.assign(height_, vector<long>(width_, Inf));

	//スタート地点のコストを入れる
	dist.at(enemyPos.z).at(enemyPos.x) = map.at(enemyPos.z).at(enemyPos.x); 

	//targetまでの最短距離を求める
	while (!que.empty())
	{
		PP now = que.top();//今いる場所を確保
		que.pop();

		bool isBreak = false;

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
			if (map.at(sz).at(sx) == -1) {
				continue;
			}

			//これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋vのコスト分で今現在わかっている最短距離）でないなら。
			if (dist.at(sz).at(sx) <= dist.at(nz).at(nx) + map.at(sz).at(sx) + Heuristic(sz, sx, target)) {
				//今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
				continue; 
			}

			//最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			rest.at(sz).at(sx) = intPair(nz, nx); 

			//目的地に着いたら
			if (sz == target.first && sx == target.second) {

				isBreak = true;
				break;
			}

			//ヒューリスティック分も込みで最短距離の更新
			dist.at(sz).at(sx) = dist.at(nz).at(nx) + map.at(sz).at(sx) + Heuristic(sz, sx, target);

			//次の探索候補を入れておく
			que.emplace(PP(dist.at(sz).at(sx), intPair(sz, sx)));
		}

		if (isBreak)
			break;

	}

	XMFLOAT3 nextPos = Path_Search(rest, start,target);

	//A*アルゴリズムを整数のグリッド形式で読み込んでいるため小数以下の値を足しなおす
	/*nextPos.z += enemyPos.z - (int)enemyPos.z;
	nextPos.x += enemyPos.x - (int)enemyPos.x;*/

	return nextPos;

}

//経路復元
XMFLOAT3 NavigationAI::Path_Search(vector<vector<intPair>> rest,intPair start, intPair target)
{

	//targetからスタート地点までたどりなおす
	int nz = target.first;
	int nx = target.second;

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
			if (rest.at(nz).at(nx) != intPair(z, x)) {
				continue;
			}

			//通ってきた座標を入れる
			searchPos.push(rest.at(nz).at(nx));

			//次はその前にいた座標の上下左右を探索するため更新
			nz = z;  
			nx = x;
		}

		//次に探索する場所が初期位置に戻ったら止める。
		if (nz == start.first && nx == start.second) {
			break;
		}

	}

	//メモリは確保されてた。
	XMFLOAT3 fMove = ZERO_FLOAT3;

	//一番上には開始位置が入ってるからそれを取り除く
	searchPos.pop();

	//空ならやめる
	if (searchPos.empty())
		return fMove;	

	//stackのtopは一番最後の要素を取ってくる
	int checkVecX = start.second - searchPos.top().second;
	int checkVecZ = start.first - searchPos.top().first;

	//値逆？試行錯誤中
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

	//向かう方向ベクトルを確認
	XMVECTOR tmp = XMLoadFloat3(&fMove);
	tmp = XMVector3Normalize(tmp);
	fMove = VectorToFloat3(tmp);
	fMove = fMove / 10;	

	return fMove;

}

int NavigationAI::Heuristic(int x, int z, intPair target)
{
	int tmpX = x - target.second;
	int tmpZ = z - target.first;

	return abs(tmpX + tmpZ);
}

//XMFLOAT3 NavigationAI::TeachNextPos()
//{
//	XMFLOAT3 fMove = { (float)teachPath_.second, ZERO, nextPos_.first };
//
//}

bool NavigationAI::IsSomePos(XMFLOAT3 pos1, XMFLOAT3 pos2)
{
	pos1.x = pos1.x - (int)pos1.x;
	pos1.x = pos1.x - (int)pos1.x;
	pos1.x = pos1.x - (int)pos1.x;
	pos1.x = pos1.x - (int)pos1.x;
	pos1.x = pos1.x - (int)pos1.x;
	pos1.x = pos1.x - (int)pos1.x;
	return false;
}

intPair NavigationAI::FloatToIntPair(float z, float x)
{

	
	int zPos = (int)z;
	int xPos = (int)x;
	intPair pair = std::make_pair(zPos, xPos);

	return pair;
}