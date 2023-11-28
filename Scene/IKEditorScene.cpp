#include "IKEditorScene.h"
#include "../Player/PlayerFoot.h"
#include "../Player/PlayerHand.h"
#include "../Engine/MapEditor/MapController.h"

//�R���X�g���N�^
IKEditorScene::IKEditorScene(GameObject* parent)
	: GameObject(parent, "IKEditorScene")
{
}

//������
void IKEditorScene::Initialize()
{
	Instantiate<PlayerFoot>(this);
	Instantiate<MapController>(this);

	//Instantiate<PlayerHand>(this);
}

//�X�V
void IKEditorScene::Update()
{
}

//�`��
void IKEditorScene::Draw()
{
}

//�J��
void IKEditorScene::Release()
{
}

void IKEditorScene::Imgui_Window()
{

	ImGui::Begin("DataWindow");

	ImGui::End();
}