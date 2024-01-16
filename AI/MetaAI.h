#pragma once
#include "AI.h"
#include "NavigationAI.h"
#include "CharacterAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

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


private:
	
	/////////各種インスタンス///////////

	//NavigationAI* pNavigationAI_;
	//CharacterAI* pCharacterAI_;
	
	//Enemy* pEnemy_;
	//Player* pPlayer_;

};

