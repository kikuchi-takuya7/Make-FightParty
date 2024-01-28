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


	//////////////アクセス関数 //////////
	void PushEnemyStatus(Status status) { enemyStatusList_.push_back(status); }
	void PushPlayerStatus(Status status) { playerStatusList_.push_back(status); }


private:
	
	/////////各種インスタンス///////////

	vector<Status> enemyStatusList_;
	vector<Status> playerStatusList_;

	NavigationAI* pNavigationAI_;
};

