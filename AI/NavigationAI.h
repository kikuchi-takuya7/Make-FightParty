#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>

//z,xの位置関係がパッと見やすいからpairにしたけど、structにした方がいい？
using std::vector;
using std::pair;
using intPair = pair<int, int>; // 座標を示す{ z,x }
using Graph = vector<vector<long>>; //二次元配列でマップやコストを表す
using PP = pair<long, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる

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
	//XMFLOAT3 TeachNextPos();
	
	/// <summary>
	/// 同じブロック内にいるかどうか
	/// </summary>
	/// <param name="pos1">比べたい値１</param>
	/// <param name="pos2">比べたい値２</param>
	/// <returns>同じ場所にいるならtrueを返す</returns>
	bool IsSomePos(XMFLOAT3 pos1, XMFLOAT3 pos2);

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

	/////////////////Astarアルゴリズムで使う///////////

	//ステージの縦幅と横幅
	int height_, width_; 
	
	//スタートとゴールはfloatにしたほうがいい？検討中
	intPair start_;
	intPair target_;

	//マップのコストを入れる。
	Graph map_;    

	//マップの位置に連動してその頂点までどのぐらいの歩数で行けるか追加する
	Graph dist_;
	
	//経路復元に使用するため、この中には一個前にいたxy座標を入れておく
	vector<vector<intPair>> rest_; 

	//探索済みの場所を昇順で記憶しておく
	std::priority_queue<PP, vector<PP>, std::greater<PP>> que_; 

	//A*アルゴリズムを整数のグリッド形式で読み込んでいるため、少数以下を保存しておく
	pair<float, float> decimal_;

	/////////////////////////////位置情報////////////////////////

	//自分が担当するenemyとプレイヤーの位置を覚えておく
	XMFLOAT3 enemyPos_;
	XMFLOAT3 playerPos_;
	
};

