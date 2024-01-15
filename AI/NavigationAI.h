#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>

//const int moveY[8] = { 0, 0, 1,-1, 1 ,1,-1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
//const int moveX[8] = { 1,-1, 0, 0, 1,-1 ,1,-1 };

const int moveY[4] = { 0,0,1,-1 };//上下左右に移動（探索）するための配列。二つまとめて縦に見ると上下左右
const int moveX[4] = { 1,-1,0,0 };

using std::vector;
using std::pair;
using Pair = pair<long long, long long>; // { distance, from }
using Graph = vector<vector<long long>>; //二次元配列上のグラフ
using PP = pair<long long, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる
using PqPP = std::priority_queue<PP, vector<PP>, std::greater<PP>>; //昇順で要素を入れておく.昇順って小さい順って意味だからな

/// <summary>
/// キャラクターAIとメタAIに情報を提供する
/// </summary>
class NavigationAI : AI
{
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

	void Astar();

	void Path_Search();

	int Heuristic(int _x, int _y);


	//////////////アクセス関数//////////////
	
	/// <summary>
	/// 探索を始める位置
	/// </summary>
	/// <param name="x">始める位置のx座標</param>
	/// <param name="y">始める位置のy座標</param>
	void SetStartPos(float x, float y) { start_ = std::make_pair(x, y); }

	/// <summary>
	/// 目標とする位置
	/// </summary>
	/// <param name="x">目標の位置のx座標</param>
	/// <param name="y">目標の位置のy座標</param>
	void SetTargetPos(float x, float y){ target_ = std::make_pair(x, y); }
	
	


private:

	int h_, w_; //縦幅と横幅
	
	//スタートとゴールはfloatにしたほうがいい？検討中
	pair<int, int> start_;
	pair<int, int> target_;

	Graph map_;    //マップのコストを入れる。
	Graph dist_; //マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	vector<vector<Pair>> rest_; //経路復元に使用するため、この中には一個前にいたxy座標を入れておく

	PqPP que_; //探索済みの場所を記憶しておく。一度行った場所だけを座標で横並びで覚えておけばいい
	//newメモ ヒューリスティックで探した合計が一番近いやつってこれでいいんじゃね
	//その位置までのヒューリスティックとコストを合わせたりなんなりするところ

	std::stack <Pair> ans_;

	
};

