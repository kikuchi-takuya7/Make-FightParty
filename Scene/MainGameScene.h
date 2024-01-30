#pragma once
#include "../Engine/GameObject.h"

class MetaAI;
class NavigationAI;
class Status;//�\���̂����ǂ��ꂢ���́H�H�H�H

//�����V�[�����Ǘ�����N���X
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


	void CallStatus(int ID, Status status);

private:

	//
	NavigationAI* pNavigationAI_;

	//�Q�[���S�̂̃o�����X���Ǘ�����AI
	MetaAI* pMetaAI_;

	/*Player* pPlayer_;

	Enemy* pEnemy_;*/
	
};