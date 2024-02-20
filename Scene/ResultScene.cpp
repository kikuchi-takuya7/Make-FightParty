#include "ResultScene.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//初期化
void ResultScene::Initialize()
{
}

//更新
void ResultScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
	
}

//描画
void ResultScene::Draw()
{
}

//開放
void ResultScene::Release()
{
}
