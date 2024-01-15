#pragma once
#include "AI.h"
#include "NavigationAI.h"

/// <summary>
/// ゲームの進行、アイテムの選出等を管理するAI
/// </summary>
class MetaAI : public AI
{

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
	NavigationAI* pNavigationAI_;
};

