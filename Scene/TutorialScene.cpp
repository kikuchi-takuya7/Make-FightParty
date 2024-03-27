#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"

namespace {
	XMFLOAT3 IMAGE_SIZE = { 1.25,1.28,1.25 };
}

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"),tutorialImage_(-1)
{
}

//������
void TutorialScene::Initialize()
{

	tutorialImage_ = Image::Load("Image/TutorialUI/Tutorial.png");
	Transform imageTrans = transform_;
	imageTrans.scale_ = IMAGE_SIZE;
	Image::SetTransform(tutorialImage_,imageTrans);
}

//�X�V
void TutorialScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//�`��
void TutorialScene::Draw()
{
	Image::Draw(tutorialImage_);
}

//�J��
void TutorialScene::Release()
{
	//pText_->Release();
	//Audio::Stop(hAudio_);
}

void TutorialScene::Imgui_Window()
{
}
