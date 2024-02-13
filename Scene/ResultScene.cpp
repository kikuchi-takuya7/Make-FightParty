#include "ResultScene.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}

//������
void ResultScene::Initialize()
{
}

//�X�V
void ResultScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
	
}

//�`��
void ResultScene::Draw()
{
}

//�J��
void ResultScene::Release()
{
}
