#pragma once
#include "../Engine/GameObject.h"

//https://ai-kenkyujo.com/news/gameai/
//構造の参考サイト

/// <summary>
/// AIを管理する基底クラス.
/// </summary>
class AI : public GameObject
{

public:

	//コンストラクタ
	AI(GameObject* parent, std::string name);

	//デストラクタ
	~AI();//virtual付けたほうがいい？後で調べよう


private:

	

};

