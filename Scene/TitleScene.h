#pragma once
#include "../Engine/GameObject.h"

enum IMAGE {

	MAKE,
	AND,
	FIGHT,
	NUM
};

class Button;
class Text;

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

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

	int hPict_[3];

	Text* pText_;

	Transform make_Trans_;
	Transform and_Trans_;
	Transform fight_Trans_;

};