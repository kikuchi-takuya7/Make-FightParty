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

class Player;
class Enemy;

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

	XMFLOAT3 Path_Search(vector<vector<intPair>> rest, intPair start, intPair target);

	int Heuristic(int x, int y, intPair target);

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
	

	intPair FloatToIntPair(float z, float x);

	/*void SetEnemyPos(float z, float x) { enemyPos_ = { x,0,z }; }
	void SetEnemyPos(XMFLOAT3 pos) { enemyPos_ = { pos.x,0,pos.z }; }
	void SetPlayerPos(float z, float x) { playerPos_ = { x,0,z }; }
	void SetPlayerPos(XMFLOAT3 pos) { playerPos_ = { pos.x,0,pos.z }; }*/

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetPlayer(Player* player) { pPlayer_ = player; }

private:

	/////////////////Astarアルゴリズムで使う///////////

	//ステージの縦幅と横幅
	int height_, width_; 
	
	

	/////////////////////////////位置情報////////////////////////

	//enemyとプレイヤーの位置を覚えておく
	Player* pPlayer_;
	Enemy* pEnemy_;
	
};

