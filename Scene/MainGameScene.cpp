#include "MainGameScene.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "../MapEditor/MapEditor.h"

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//������
void MainGameScene::Initialize()
{
	//Instantiate<Player>(this);
	//Instantiate<Stage>(this);
	Instantiate<MapEditor>(this);
}

//�X�V
void MainGameScene::Update()
{
}

//�`��
void MainGameScene::Draw()
{
}

//�J��
void MainGameScene::Release()
{
}
