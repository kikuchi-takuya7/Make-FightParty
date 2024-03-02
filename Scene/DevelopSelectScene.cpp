#include "DevelopSelectScene.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
DevelopSelectScene::DevelopSelectScene(GameObject* parent)
	: GameObject(parent, "DevelopSelectScene"),scene_(SCENE_ID_DEVELOP_SELECT),hModel_(-1)
{
}

//������
void DevelopSelectScene::Initialize()
{
	/*hModel_ = Model::Load("Map/school.fbx");
	assert(hModel_ >= 0);*/
}

//�X�V
void DevelopSelectScene::Update()
{
	switch (scene_)
	{
	case SCENE_ID_MAINGAME: {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
		break;
	}

	default:
		break;
	}
}

//�`��
void DevelopSelectScene::Draw()
{
	/*Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);*/
}

//�J��
void DevelopSelectScene::Release()
{
}

void DevelopSelectScene::Imgui_Window()
{
	ImGui::Begin("DataWindow");
	if (ImGui::CollapsingHeader("Let's Go SelectScene"))
	{
		
		if (ImGui::Button("IKEditor"))
			scene_ = SCENE_ID_MAINGAME;

	}
	ImGui::End();
}
