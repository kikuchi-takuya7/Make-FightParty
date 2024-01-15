#pragma once
#include "AI.h"
#include "../Engine/GameObject.h"

/// <summary>
/// キャラクターAIとメタAIに情報を提供する
/// </summary>
class NavigationAI : AI
{

	///////////オーバーライドした関数/////////
	
	//初期化
	void Initialize() override;
	
	//解放
	void Release() override;

	//////////メンバ関数///////////////

	void Astar();



private:
	
};

