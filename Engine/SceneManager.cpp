#include "sceneManager.h"

#include "../Scene/MapEditorScene.h"
#include "../Scene/DevelopSelectScene.h"
#include "../Scene/MainGameScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_MAPEDITOR;
	nextSceneID_ = currentSceneID_;
	Instantiate<MapEditorScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_DEVELOP_SELECT: Instantiate<DevelopSelectScene>(this); break;
		case SCENE_ID_MAPEDITOR: Instantiate<MapEditorScene>(this); break;
		case SCENE_ID_MAINGAME: Instantiate<MainGameScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}