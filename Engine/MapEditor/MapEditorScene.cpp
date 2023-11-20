#include "MapEditorScene.h"
#include "MapController.h"
#include "MapData.h"

//コンストラクタ
MapEditorScene::MapEditorScene(GameObject* parent)
	: GameObject(parent, "MapEditorScene")
{
}

//初期化
void MapEditorScene::Initialize()
{
	Instantiate<MapController>(this);
	Instantiate<MapData>(this);
}

//更新
void MapEditorScene::Update()
{
}

//描画
void MapEditorScene::Draw()
{
}

//開放
void MapEditorScene::Release()
{
}

void MapEditorScene::Imgui_Window()
{
}
