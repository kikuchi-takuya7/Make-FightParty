#include "TitleScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../UI/TitleUI.h"

#include "../UI/PlayerUI.h"
#include "../UI/GameUI.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), title_(nullptr)
{
}

//初期化
void TitleScene::Initialize()
{
	title_ = Instantiate<TitleUI>(this);
	//Instantiate<PlayerUI>(this);
	//Instantiate<GameUI>(this);
}

//更新
void TitleScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//描画
void TitleScene::Draw()
{

}

//開放
void TitleScene::Release()
{
	//pText_->Release();
}

void TitleScene::Imgui_Window()
{
}
