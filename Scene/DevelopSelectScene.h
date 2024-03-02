#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SceneManager.h"

/// <summary>
/// �f�x���b�v�p�̃V�[��
/// </summary>
class DevelopSelectScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	DevelopSelectScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Imgui_Window() override;

private:

	SCENE_ID scene_;

	int hModel_;

};