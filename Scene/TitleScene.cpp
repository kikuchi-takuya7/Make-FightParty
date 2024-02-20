#include "TitleScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../UI/TitleUI.h"

#include "../UI/PlayerUI.h"
#include "../UI/GameUI.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), title_(nullptr)
{
}

//������
void TitleScene::Initialize()
{
	title_ = Instantiate<TitleUI>(this);
	//Instantiate<PlayerUI>(this);
	//Instantiate<GameUI>(this);
}

//�X�V
void TitleScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//�`��
void TitleScene::Draw()
{

}

//�J��
void TitleScene::Release()
{
	//pText_->Release();
}

void TitleScene::Imgui_Window()
{
}
