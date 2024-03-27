#include "TitleScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../UI/TitleUI.h"
#include "../UI/PlayerUI.h"
#include "../UI/RankingUI.h"
#include "../Engine/Audio.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), title_(nullptr),hAudio_(-1)
{
}

//������
void TitleScene::Initialize()
{
	title_ = Instantiate<TitleUI>(this);
	
	hAudio_ = Audio::Load("Audio/TitleBGM.wav", true);
	assert(hAudio_ >= ZERO);

	Audio::Play(hAudio_);

}

//�X�V
void TitleScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TUTORIAL);
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
	//Audio::Stop(hAudio_);
}

void TitleScene::Imgui_Window()
{
}
