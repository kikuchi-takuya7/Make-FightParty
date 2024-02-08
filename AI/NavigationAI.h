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
using IntPair = pair<int, int>; // 座標を示す{ z,x }
using Graph = vector<vector<long>>; //二次元配列でマップやコストを表す
using PP = pair<long, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる


class Character;
class CharacterAI;

/// <summary>
/// キャラクターAIとメタAIに情報を提供する
/// </summary>
class NavigationAI : public AI
{
	//
public:

	//コンストラクタ
	NavigationAI(GameObject* parent);

	//デストラクタ
	~NavigationAI();

	///////////オーバーライドした関数/////////
	
	//初期化
	void Initialize() override;
	
	//解放
	void Release() override;

	//////////メンバ関数///////////////


	Transform MoveSelectObject(int ID);

	void AllResetStatus();

	void AllStopDraw();

	void AllStartDraw();

	float Distance(int myID, int targetID);


	//////////////////Astarアルゴリズムで使う関数//////////////////
	
	/// <summary>
	/// Astarを使い目標地点を探索する
	/// </summary>
	XMFLOAT3 Astar(int myID, int targetID);

	/// <summary>
	/// Astarアルゴリズムで使う経路復元用
	/// </summary>
	/// <param name="rest">一個前にいた座標を2次元配列で記憶したもの</param>
	/// <param name="start">スタート地点</param>
	/// <param name="target">目標地点</param>
	/// <returns></returns>
	XMFLOAT3 Path_Search(vector<vector<IntPair>> rest, IntPair start, IntPair target);

	/// <summary>
	/// ヒューリスティックで最短距離を測る
	/// </summary>
	/// <param name="x">現在のx座標</param>
	/// <param name="y">現在のy座標</param>
	/// <param name="target">目標地点</param>
	/// <returns>最短距離の期待値</returns>
	int Heuristic(int x, int y, IntPair target);

	/// <summary>
	/// 小数点以下を切り捨てて整数にする
	/// </summary>
	/// <param name="z">整数にしたいz</param>
	/// <param name="x">整数にしたいx</param>
	/// <returns>整数にしたIntPair</returns>
	IntPair FloatToIntPair(float z, float x);


	
	//////////////アクセス関数//////////////
	//void PushEnemy(Enemy* enemy) { pEnemyList_.push_back(enemy); }
	//void PushPlayer(Player* player) { pPlayerList_.push_back(player); }
	void PushCharacter(Character* chara) { pCharacterList_.emplace_back(chara); }
	void PushCharacterAI(CharacterAI* AI) { pCharacterAIList_.emplace_back(AI); }

private:

	/////////////////Astarアルゴリズムで使う///////////

	//ステージの縦幅と横幅
	int height_, width_; 
	
	

	/////////////////////////////Characterの情報////////////////////////

	vector<Character*> pCharacterList_;

	vector<CharacterAI*> pCharacterAIList_;
	
};

