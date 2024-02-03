#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Character/Character.h"

class Player;
class Enemy;
class CreateMode;
class NavigationAI;

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

	void NextGame();

	void GameCameraSet();

	//////////////アクセス関数 //////////

	void PushCharacterStatus(Status status) { characterStatusList_.emplace_back(status); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void ChangeStatus(int ID, Status status) { characterStatusList_.at(ID) = status; }
	void SetCreateMode(CreateMode* create) { pCreateMode_ = create; }
	vector<int> GetRanking() { return ranking_; }


private:
	

	//vector<Status> enemyStatusList_;
	//vector<Status> playerStatusList_;

	vector<Status> characterStatusList_;

	NavigationAI* pNavigationAI_;

	CreateMode* pCreateMode_;

	//現在1位の人のIDを覚えておく
	vector<int> No1CharaID_;

	//現在の順位をIDで覚えておく
	vector<int> ranking_;
};

