#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../MapEditor/MapEditor.h"
#include "../Engine/Camera.h"

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//初期化
void MainGameScene::Initialize()
{
	Instantiate<Player>(this);
	//Instantiate<Stage>(this);
	//Instantiate<MapEditor>(this);

	Camera::SetPosition(XMFLOAT3(0, 10, -20));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));

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
