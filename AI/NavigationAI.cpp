#include "NavigationAI.h"
#include "../Engine/Input.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

namespace {
	const int STAGE_HEIGHT = 30;
	const int STAGE_WIDTH = 30;

	//コストを1にしたら経路復元の所で無限ループしてしまう。
	const int STAGE_COST = 1;

	//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
	/*const int moveZ[8] = {  1, 1,-1,-1, ZERO, ZERO,    1,   -1 };
	const int moveX[8] = {	1,-1, 1,-1,    1,   -1, ZERO, ZERO };*/

	//上下左右に移動（探索）するための配列
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

//グリッド上でAstarアルゴリズムを使い最短距離を探す
XMFLOAT3 NavigationAI::Astar(int myID, int targetID)
{

	//探索を始める場所と目標地点
	IntPair start;
	IntPair target;

	//将来的にMetaAIに狙うべき敵を聞きたい
	XMFLOAT3 startPos = pCharacterList_.at(myID)->GetPosition();
	XMFLOAT3 targetPos = pCharacterList_.at(targetID)->GetPosition();

	//スタート地点と目標地点を小数点を切り捨ててセットする
	start = FloatToIntPair(startPos.z, startPos.x);
	target = FloatToIntPair(targetPos.z, targetPos.x);

	//既に目標地点にいるならば移動しない
	if (start == target)
		return ZERO_FLOAT3;

	//マップのコストを入れる。
	Graph map;

	//マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	Graph dist;

	//経路復元に使用するため、この中には一個前にいたxy座標を入れておく
	vector<vector<IntPair>> rest;
	
	//width分の行を先にheight列分だけ確保しておく
	for (int i = ZERO; i < height_; i++) {
		map.emplace_back(width_);
		dist.emplace_back(width_);
		rest.emplace_back(width_);
	}

	//ステージのコストを入れる。壁は-1.将来的にstageから持ってくる予定
	for (int i = ZERO; i < height_; i++) {
		for (int f = ZERO; f < width_; f++) {

			map.at(i).at(f) = STAGE_COST;

			//restにxz座標を入れる
			rest[i][f] = IntPair(i, f);
		}
	}

	//スタート地点の座標
	rest.at(start.first).at(start.second) = IntPair(start.first, start.second);
	
	//探索済みの場所を昇順で記憶しておく。topで要素を呼び出した時にfirstの一番値が小さいのを持ってきてくれる
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que;

	//スタート地点から探索を始める
	que.emplace(ZERO, IntPair(start.first, start.second));

	//ありえない値の情報で初期化
	const int Inf = 9999999;
	dist.assign(height_, vector<long>(width_, Inf));

	//スタート地点のコストを入れる
	dist.at(start.first).at(start.second) = map.at(start.first).at(start.second);

	//targetまでの最短距離を求める
	while (!que.empty())
	{
		//今いる場所を確保
		PP now = que.top();
		que.pop();

		bool isBreak = false;

		for (int i = ZERO; i < ARRAYSIZE(moveZ); i++) {

			//今いる場所 NowZ
			int nz = now.second.first;
			int nx = now.second.second;
			//今から探索する場所 SecondZ
			int sz = nz + moveZ[i];
			int sx = nx + moveX[i];

			int cost = ZERO;
			
			// 画面外なら
			if (sz < ZERO || sz >= height_ || sx < ZERO || sx >= width_) {
				continue;
			}

			//壁なら
			if (map.at(sz).at(sx) == -1) {
				continue;
			}

			//今と次の行ける最短距離(ヒューリスティック)を取っておく
			int secondH = Heuristic(sz, sx, target);
			int nowH = Heuristic(nz, nx, target);

			//斜め移動にコストをつける。コストをつけないと斜め移動しかしなくなってしまった.Astarにとっては斜め移動も上下移動も同じスピードだから
			if (i > 3) {
				cost = 1;
			}

#if 0
			//これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋mapのコスト分で今現在わかっている最短距離）でないなら。
			if (dist.at(sz).at(sx) <= dist.at(nz).at(nx) + map.at(sz).at(sx) + cost) {
				continue;
			}

			//最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			rest.at(sz).at(sx) = IntPair(nz, nx);

			//目的地に着いたら
			if (sz == target.first && sx == target.second) {

				isBreak = true;
				break;
			}

			//最短距離の更新
			dist.at(sz).at(sx) = map.at(sz).at(sx) + cost + secondH;

			//次の探索候補を入れておく.ヒューリスティック分を含めたコスト,場所
			que.emplace(PP(dist.at(sz).at(sx), IntPair(sz, sx)));
#else
			//これから探索するところが今いる位置から行くとそこまでの最短距離（dist＋map+ヒューリスティックのコスト分で今現在わかっている最短距離）でないなら。
			if (dist.at(sz).at(sx) + secondH <= dist.at(nz).at(nx) + map.at(sz).at(sx) + nowH + cost) {
				//今から探索しようとしてる場所はもし一度も行ってなかったらINFが入ってて絶対更新される
				continue;
			}

			//最短経路が出た探索済みの座標に探索前どこにいたかの情報を入れて後で経路復元に使う
			rest.at(sz).at(sx) = IntPair(nz, nx);

			//目的地に着いたら
			if (sz == target.first && sx == target.second) {

				isBreak = true;
				break;
			}

			//そこに行くまでの最短距離の更新（ヒューリスティックを足してしまうと値が増え続けて探索が最適化できない）
			dist.at(sz).at(sx) = dist.at(nz).at(nx) + map.at(sz).at(sx) + cost;

			//次の探索候補を入れておく
			que.emplace(PP(dist.at(sz).at(sx) + secondH, IntPair(sz, sx)));
#endif
			
		}

		if (isBreak)
			break;

	}

	XMFLOAT3 nextPos = Path_Search(rest, start, target);

	return nextPos;

}

//経路復元
XMFLOAT3 NavigationAI::Path_Search(vector<vector<IntPair>> rest,IntPair start, IntPair target)
{

	//targetからスタート地点までたどりなおす
	int nz = target.first;
	int nx = target.second;

	//targetから探索するからstackで最後の方に獲得した座標を使うため
	std::stack <IntPair> searchPos;

	//どの道をたどってきたか思い出す
	while (true) {
		for (int n = ZERO; n < ARRAYSIZE(moveZ); n++) {

			int z = nz;
			int x = nx;

			//上下探索
			z += moveZ[n];
			x += moveX[n];

			//上下探索する時の座標とrestに入ってるその場所に行く前に居た座標と照らし合わせてその値が同じじゃないなら
			if (rest.at(nz).at(nx) != IntPair(z, x)) {
				continue;
			}

			// 画面外なら
			if (z < ZERO || z >= height_ || x < ZERO || x >= width_) {
				continue;
			}

			//通ってきた座標を入れる
			searchPos.emplace(rest.at(nz).at(nx));

			//次はその前にいた座標の上下左右を探索するため更新
			nz = z;  
			nx = x;

			break;
		}

		//次に探索する場所が初期位置に戻ったら止める。
		if (nz == start.first && nx == start.second) {
			break;
		}

	}


	XMFLOAT3 fMove = ZERO_FLOAT3;

	//一番上には開始位置が入ってるからそれを取り除く
	searchPos.pop();

	//空ならやめる
	if (searchPos.empty())
		return fMove;	

	//stackのtopは一番最後の要素を取ってくる
	int checkVecZ = start.first - searchPos.top().first;
	int checkVecX = start.second - searchPos.top().second;

	//ごり押しで修正することもできるけど良くない気がする
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

	//向かう方向ベクトルを確認
	XMVECTOR vMove = XMLoadFloat3(&fMove);
	vMove = XMVector3Normalize(vMove);
	fMove = VectorToFloat3(vMove);
	fMove = fMove * 0.1;	

	return fMove;

}


int NavigationAI::Heuristic(int z, int x, IntPair target)
{
	//絶対値の差をとる
	int tmpX = abs(target.second - x);
	int tmpZ = abs(target.first - z);

	//斜め移動なので大きいほうを返す
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

//引数で自分とターゲットを持ってくるのも考えた。どっちがいいかね
float NavigationAI::Distance(int myID, int targetID)
{
	
	//将来的にMetaAIに狙うべき敵を聞きたい
	XMFLOAT3 eP = pCharacterList_.at(myID)->GetPosition();
	XMFLOAT3 pP = pCharacterList_.at(targetID)->GetPosition();

	//ピタゴラスの定理で距離を求められるらしい
	float distance = pow((pP.x - eP.x) * (pP.x - eP.x) + (pP.y - eP.y) * (pP.y - eP.y) + (pP.z - eP.z) * (pP.z - eP.z), 0.5);

	return distance;
}
