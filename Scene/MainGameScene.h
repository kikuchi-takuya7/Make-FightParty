#pragma once
#include "../Engine/GameObject.h"

class MetaAI;
class NavigationAI;
class Stage;
class CreateMode;
class Enemy;
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

	//�N���G�C�g���[�h�ɐF�X�Z�b�g�����肷��֐�
	void CreateModeInit();

	//�L�����N�^�[AI�����
	void CreateCharaAI(Enemy* enemy, int attackRange);

	//�w�i
	int hPict_;

	//���̃N���X���ł͎g��Ȃ����ǈꉞ�C���X�^���X��ێ����Ă���

	//�Q�[���S�̂̈ʒu�����Ǘ�����AI
	NavigationAI* pNavigationAI_;
	
	//�Q�[���S�̂̃o�����X���Ǘ�����AI
	MetaAI* pMetaAI_;

	//�X�e�[�W
	Stage* pStage_;

	//�N���G�C�g���[�h���Ɏg���N���X
	CreateMode* pCreateMode_;

	
	//�C���X�^���X���쐬���ĐF�X����e���v���[�g
	template <class T>
	T* CreateCharacter(int ID, std::string name);

};

