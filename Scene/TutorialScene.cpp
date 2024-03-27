#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"

namespace {
	XMFLOAT3 IMAGE_SIZE = { 1.25,1.28,1.25 };
}

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"),tutorialImage_(-1)
{
}

//初期化
void TutorialScene::Initialize()
{

	tutorialImage_ = Image::Load("Image/TutorialUI/Tutorial.png");
	Transform imageTrans = transform_;
	imageTrans.scale_ = IMAGE_SIZE;
	Image::SetTransform(tutorialImage_,imageTrans);
}

//更新
void TutorialScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//描画
void TutorialScene::Draw()
{
	Image::Draw(tutorialImage_);
}

//開放
void TutorialScene::Release()
{
	//pText_->Release();
	//Audio::Stop(hAudio_);
}

void TutorialScene::Imgui_Window()
{
}
