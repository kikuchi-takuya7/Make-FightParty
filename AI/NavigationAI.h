#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>


//pairじゃなくてstructにした方がいいか？
using std::vector;
using std::pair;
using Pair = pair<int, int>; // 座標を示す{ z,x }
using Graph = vector<vector<long>>; //二次元配列上のグラフ
using PP = pair<long, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる
//using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //昇順で要素を入れておく.昇順って小さい順って意味だからな

/// <summary>
/// キャラクターAIとメタAIに情報を提供する
/// </summary>
class NavigationAI : AI
{
	//
public:

	//コンストラクタ
	NavigationAI();

	//デストラクタ
	~NavigationAI();

	///////////オーバーライドした関数/////////
	
	//初期化
	void Initialize() override;
	
	//解放
	void Release() override;

	//////////メンバ関数///////////////

	void InitAstar();

	XMFLOAT3 Astar();

	XMFLOAT3 Path_Search();

	int Heuristic(int _x, int _y);

	/// <summary>
	/// 次に行くべき座標を教える
	/// </summary>
	/// <returns>次の座標</returns>
	XMFLOAT3 TeachNextPos();

	//////////////アクセス関数//////////////
	
	/// <summary>
	/// 探索を始める位置
	/// </summary>
	/// <param name="z">始める位置のz座標</param>
	/// <param name="x">始める位置のx座標</param>
	void SetStartPos(float z, float x);

	/// <summary>
	/// 目標とする位置
	/// </summary>
	/// <param name="z">目標の位置のz座標</param>
	/// <param name="x">目標の位置のx座標</param>
	void SetTargetPos(float z, float x);
	
	void SetEnemyPos(float z, float x) { enemyPos_ = { x,0,z }; }
	void SetEnemyPos(XMFLOAT3 pos) { enemyPos_ = { pos.x,0,pos.z }; }
	void SetPlayerPos(float z, float x) { playerPos_ = { x,0,z }; }
	void SetPlayerPos(XMFLOAT3 pos) { playerPos_ = { pos.x,0,pos.z }; }

private:

	int height_, width_; //ステージの縦幅と横幅
	
	//スタートとゴールはfloatにしたほうがいい？検討中
	Pair start_;
	Pair target_;

	//マップのコストを入れる。
	Graph map_;    

	//マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	Graph dist_;
	
	//経路復元に使用するため、この中には一個前にいたxy座標を入れておく
	vector<vector<Pair>> rest_; 

	//探索済みの場所を記憶しておく。一度行った場所だけを座標だけ横並びで覚えておけばいい
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que_; 

	//前はstackでtargetまでの位置を全部保存してたけど１マスずつ探索した方が良いかも
	pair<float, float> nextPos_;

	//自分が担当するenemyとプレイヤーの位置を覚えておく
	XMFLOAT3 enemyPos_;
	XMFLOAT3 playerPos_;
	
};

