#pragma once
#include "../Engine/GameObject.h"

class MetaAI;
class NavigationAI;
class Stage;
struct Status;

/// <summary>
/// �Q�[���̃��C���ƂȂ�V�[��
/// </summary>
class MainGameScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MainGameScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

private:

	//�w�i
	int hPict_;

	
	
};