#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Character.h"

class Player;
class Enemy;
class NavigationAI;

/// <summary>
/// ゲームの進行、アイテムの選出等を管理するAI
/// </summary>
class MetaAI : public AI
{

public:

	//コンストラクタ
	MetaAI();

	//デストラクタ
	~MetaAI();

	/////////オーバーライドした関数/////////

	//初期化
	void Initialize() override;

	//解放
	void Release() override;


	////////////メンバ関数////////////////


	int Targeting(int ID);

	void CheckNo1Chara();

	//////////////アクセス関数 //////////
	//void PushEnemyStatus(Status status) { enemyStatusList_.push_back(status); }
	//void PushPlayerStatus(Status status) { playerStatusList_.push_back(status); }
	void PushCharacterStatus(Status status) { characterStatusList_.emplace_back(status); }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	




private:
	

	//vector<Status> enemyStatusList_;
	//vector<Status> playerStatusList_;

	vector<Status> characterStatusList_;

	NavigationAI* pNavigationAI_;

	//現在1位の人のIDを覚えておく
	vector<int> No1CharaID_;
};

