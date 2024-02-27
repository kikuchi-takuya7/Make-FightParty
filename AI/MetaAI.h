#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"

enum TARGETPATTERN {
	TARGET_RANDAM,
	TARGET_NO_1,
	TARGET_NUM,

};

class Player;
class Enemy;
class CreateMode;
class NavigationAI;
class CountDownUI;
class RankingUI;
class WinnerUI;
class ChampionUI;
class Timer;

/// <summary>
/// ゲームの進行、アイテムの選出等を管理するAI
/// </summary>
class MetaAI : public AI
{

public:

	//コンストラクタ
	MetaAI(GameObject* parent);

	//デストラクタ
	~MetaAI();

	/////////オーバーライドした関数/////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//解放
	void Release() override;


	////////////メンバ関数////////////////

	/// <summary>
	/// 狙うべき相手を支持する
	/// </summary>
	/// <param name="ID">自分のID</param>
	/// <returns>狙うべき相手のID</returns>
	int Targeting(int ID);

	/// <summary>
	/// 1位のキャラIDは誰か、何人いるかを確認
	/// </summary>
	void CheckNo1Chara();
	

	/////////ゲームの流れを管理する関数///////////

	/// <summary>
	/// 勝敗が決まっていた場合、クリエイトモードに移行する
	/// </summary>
	void ToCreateMode();

	/// <summary>
	/// ゲームを開始する
	/// </summary>
	void StartGame();

	/// <summary>
	/// ゲームの状態をリセットする
	/// </summary>
	void ResetGame();

	/// <summary>
	/// ゲーム用のカメラに切り替える（その位置にセットする）
	/// </summary>
	void GameCameraSet();

	/// <summary>
	/// クリエイトモードで表示されたオブジェクトを選択する
	/// </summary>
	/// <param name="model">表示されているオブジェクト一覧</param>
	/// <returns>どのモデルを選んだか</returns>
	int SelectObject(vector<int> model);

	//////////////アクセス関数 //////////

	//ステータスをプッシュすると同時に、名前もRankingUIにセットする
	void PushCharacterStatus(Status status);

	Status GetCharacterStatus(int ID) { return characterStatusList_.at(ID); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void ChangeStatus(int ID, Status status) { characterStatusList_.at(ID) = status; }
	void SetCreateMode(CreateMode* create) { pCreateMode_ = create; }
	vector<int> GetRanking() { return ranking_; }


private:
	
	void MoveChampionCam();

	int VictoryPlayer();

	//vector<Status> enemyStatusList_;
	//vector<Status> playerStatusList_;

	vector<Status> characterStatusList_;

	NavigationAI* pNavigationAI_;

	CreateMode* pCreateMode_;

	Timer* pWaitTimer_;

	//現在1位の人のIDを覚えておく(同率一位の可能性もあるため、後の処理を楽にするためvectorに)
	vector<int> No1CharaID_;

	//現在の順位をIDで覚えておく
	vector<int> ranking_;

	//現在のスコア。要素数がID
	vector<int> score_;

	bool endGame_;


	////////////////////UI/////////////////////

	CountDownUI* pCountDown_;

	RankingUI* pRankingUI_;

	WinnerUI* pWinnerUI_;

	ChampionUI* pChampionUI_;

};

