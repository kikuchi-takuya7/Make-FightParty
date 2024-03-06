#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"

//AIが狙うターゲットのパターン
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

	/////////オーバーライドした関数////////////////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//解放
	void Release() override;


	////////////メンバ関数/////////////////////////////

	/// <summary>
	/// 狙うべき相手を指示する関数
	/// </summary>
	/// <param name="ID">自分のID</param>
	/// <returns>狙うべき相手のID</returns>
	int Targeting(int ID);

	/// <summary>
	/// クリエイトモードで表示されたオブジェクトを選択する
	/// </summary>
	/// <param name="model">表示されているオブジェクト一覧</param>
	/// <returns>どのオブジェクトを選んだか</returns>
	int SelectObject(vector<int> model);
	

	/////////ゲームの流れを管理する関数////////////////

	/// <summary>
	/// 勝敗が決まっていたらクリエイトモードへ移行する関数
	/// </summary>
	void DecidedWinner();

	/// <summary>
	/// ゲームの状態をリセットしてカウントダウンする関数
	/// </summary>
	void ResetGame();

	//////////////アクセス関数 ///////////////////////

	/// <summary>
	/// characterStatusList_にステータスをプッシュすると同時に、名前もRankingUIにセットする関数
	/// </summary>
	/// <param name="status">プッシュしたいステータス</param>
	void PushCharacterStatus(Status status);

	Status GetCharacterStatus(int ID) { return characterStatusList_.at(ID); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void ChangeStatus(int ID, Status status) { characterStatusList_.at(ID) = status; }
	void SetCreateMode(CreateMode* create) { pCreateMode_ = create; }
	vector<int> GetRanking() { return ranking_; }


private:

	//////////////////////////////private関数//////////////////////

	/// <summary>
	/// 優勝者が決まった時のUpdate
	/// </summary>
	void ChampionUpdate();

	/// <summary>
	/// 通常時のUpdate関数
	/// </summary>
	void UsuallyUpdate();

	/// <summary>
	/// 1位のキャラIDは誰か、何人いるかを確認する関数
	/// </summary>
	void CheckNo1Chara();

	/// <summary>
	/// 勝者の情報を整理してクリエイトモードに移行する関数
	/// </summary>
	/// <param name="winnerID">勝ったプレイヤーのID</param>
	void ToCreateMode(int winnerID);

	/// <summary>
	/// ゲーム用のカメラに切り替える（その位置にセットする）
	/// </summary>
	void GameCameraSet();
	
	/// <summary>
	/// 優勝者の方にカメラを向ける関数
	/// </summary>
	void MoveChampionCam();

	/// <summary>
	/// 優勝者は誰かを決める関数
	/// </summary>
	/// <returns>優勝したプレイヤーのID</returns>
	int VictoryPlayer();

	/// <summary>
	/// 優勝者の周りにエフェクトを出す関数
	/// </summary>
	void VictoryEffect();

	///////////////////////////////////////////メンバ変数//////////////////////////

	//全てのプレイヤーのステータスを覚えた配列
	vector<Status> characterStatusList_;

	//NavigationAIのインスタンス
	NavigationAI* pNavigationAI_;

	//クリエイトモードのインスタンス
	CreateMode* pCreateMode_;

	//一定時間止めるためのタイマー
	Timer* pWaitTimer_;

	//現在1位の人のIDを覚えておく(同率一位の可能性もあるため、後の処理を楽にするためvectorに)
	vector<int> No1CharaID_;

	//現在の順位をIDで覚えておく
	vector<int> ranking_;

	//現在のスコア。要素数がID
	vector<int> score_;

	//試合が終わったらtrue
	bool endGame_;


	////////////////////UI/////////////////////

	CountDownUI* pCountDown_;

	RankingUI* pRankingUI_;

	WinnerUI* pWinnerUI_;

	ChampionUI* pChampionUI_;


	//ゲームBGM
	int hAudio_;

};

