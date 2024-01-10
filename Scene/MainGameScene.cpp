#include "MainGameScene.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "../MapEditor/MapEditor.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//初期化
void MainGameScene::Initialize()
{
	//Instantiate<Player>(this);
	//Instantiate<Stage>(this);
	Instantiate<MapEditor>(this);
}

//更新
void MainGameScene::Update()
{
}

//描画
void MainGameScene::Draw()
{
}

//開放
void MainGameScene::Release()
{
}
