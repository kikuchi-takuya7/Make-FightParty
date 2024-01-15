#pragma once
#include "AI.h"
#include "NavigationAI.h"


/// <summary>
/// 敵キャラクターを動かすAI
/// </summary>
class CharacterAI : public AI
{

	//コンストラクタ
	CharacterAI();

	//デストラクタ
	~CharacterAI();

	/////////オーバーライドした関数///////

	//初期化
	void Initialize() override;

	//解放
	void Release() override;

private:

	NavigationAI* pNavigationAI_;
};

