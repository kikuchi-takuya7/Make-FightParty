#pragma once
#include "../Engine/GameObject.h"

//�`���[�g���A���V�[�����Ǘ�����N���X
class TutorialScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TutorialScene(GameObject* parent);

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

	/// <summary>
	/// �`���[�g���A���p�̃I�u�W�F�N�g�𐶐�����֐�
	/// </summary>
	void CreateObject();

	//�w�i�摜
	int hBackGround_;
};