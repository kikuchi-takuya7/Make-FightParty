#include "MainGameScene.h"
#include "../Player/Player.h"

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene")
{
}

//������
void MainGameScene::Initialize()
{
	Instantiate<Player>(this);
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
