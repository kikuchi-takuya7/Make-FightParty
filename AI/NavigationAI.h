#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>


using std::vector;
using std::pair;
using IntPair = pair<int, int>; // 座標を示す{ z,x }
using Graph = vector<vector<int>>; //二次元配列でマップやコストを表す
using PIntP = pair<int, pair<int, int>>;//firstにコスト。secondにそのコストの位置と同じ座標を入れる

class Character;
class CharacterAI;
class Stage;
struct Status;

/// <summary>
/// キャラクターAIとメタAIに情報を提供するAI
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

	/// <summary>
	/// 引数のIDのキャラクターAIにどこにオブジェクトを置くか聞く関数
	/// </summary>
	/// <param name="ID">オブジェクトを置く敵のID</param>
	/// <returns>オブジェクトを置く場所</returns>
	Transform MoveSelectObject(int ID);

	/// <summary>
	/// 引数の値がプレイヤーの開始位置と被っているかを判断する関数
	/// </summary>
	/// <param name="pos">比べるXMFLOAT3型の変数</param>
	/// <returns>重なってたらtrue</returns>
	bool IsOverlapPos(XMFLOAT3 pos);

	/// <summary>
	/// 引数の二人の距離を測る関数
	/// </summary>
	/// <param name="myID">自分のID</param>
	/// <param name="targetID">狙っている相手のID</param>
	/// <returns>比べた二人の距離</returns>
	float Distance(int myID, int targetID);

	/// <summary>
	/// 引数のキャラと一番遠い距離にいるキャラとの距離を測る
	/// </summary>
	/// <param name="ID">一番遠い位置を求める関数</param>
	/// <returns>一番遠いキャラのID</returns>
	int Farthest(int ID);

	//////////////////Astarアルゴリズムで使う関数//////////////////

	/// <summary>
	/// グリッドでAstarを使い目標地点を探索する関数
	/// </summary>
	/// <param name="myID">自分のID</param>
	/// <param name="targetID">狙っている相手のID</param>
	/// <returns>次に向かうべき座標</returns>
	XMFLOAT3 Astar(int myID, int targetID);

	///////////////キャラクターすべてに指示を出す関数/////////////////////

	void AllResetStatus();		//ステータスをリセットする（winPoint以外）
	void AllResetAITarget();	//AIのターゲットを全てリセットする
	void AllStopDraw();			//全ての描画を止める
	void AllStartDraw();		//全ての描画を許可する
	void AllStopUpdate();		//全てのUpdateを止める
	void AllStartUpdate();		//全てのUpdateを許可する
	void AllStopDrawPlayerUI();	//全てのプレイヤーUIの描画を止める
	void AllEraseCollision();	//全てのコライダーを消す(deleteはしない)

	
	//////////////アクセス関数//////////////

	/// <summary>
	/// 指定したIDのキャラのインスタンスを獲得する
	/// </summary>
	/// <param name="ID">欲しいキャラのID</param>
	/// <returns>指定したキャラ</returns>
	Character* GetCaracter(int ID);

	/// <summary>
	/// 指定したキャラにステータスをセットする
	/// </summary>
	/// <param name="ID">セットしたいキャラのID</param>
	/// <param name="status">新しいステータス</param>
	void SetStatus(int ID, Status status);

	void PushCharacter(Character* chara) { pCharacterList_.emplace_back(chara); }
	void PushCharacterAI(CharacterAI* AI) { pCharacterAIList_.emplace_back(AI); }
	void SetStage(Stage* stage) { pStage_ = stage; }


private:

	/////////////////Astarアルゴリズムで使うprivate関数///////////

	/// <summary>
	/// Astarアルゴリズムで使う経路復元用
	/// </summary>
	/// <param name="rest">一個前にいた座標を2次元配列で記憶したもの</param>
	/// <param name="start">スタート地点</param>
	/// <param name="target">目標地点</param>
	/// <returns>次に向かわせる座標</returns>
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

	//ステージの縦幅と横幅
	int height_, width_; 
	
	//ステージの情報
	Stage* pStage_;

	/////////////////////////////Characterの情報////////////////////////

	vector<Character*> pCharacterList_;

	vector<CharacterAI*> pCharacterAIList_;


	
};

