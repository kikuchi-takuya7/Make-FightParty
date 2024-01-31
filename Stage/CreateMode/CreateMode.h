#pragma once
#include "../../Engine/GameObject.h"
#include <stack>
#include <vector>

//�V�����t�@�C����ǉ�������A������CreateObject�ɗv�f���蓮�Œǉ�����
enum FBXPATTERN {
	//SCHOOL,
	TEST,
	TESTFLOOR,
	TESTWALL,
	PATTERN_END
};

struct BACKUPDATA {
	std::string objectName;
	int objectId;
	Transform objectTrans;
};

//�I�u�W�F�N�g�ǉ����[�h���Ǘ�����N���X
class CreateMode
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CreateMode();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�J��
	void Release();

	std::list<GameObject*> GetCreateObjectList() { return createObjectList_; }

	/// <summary>
	/// selecting_object�ɑΉ������I�u�W�F�N�g���쐬����
	/// </summary>
	/// <returns>�쐬�����I�u�W�F�N�g</returns>
	GameObject* CreateObject();

	//createObjectList�ɓ����
	void AddCreateObject(GameObject* object);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	void MoveCamPos();

	bool IsOverlapCursor();

	void Enter() { isUpdate_ = true; }
	void Leave() { isUpdate_ = false; }

private:

	std::vector<int> hModel_;

	//Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
	std::vector<std::string> fileName_;

	//imgui�őI������Ă���I�u�W�F�N�g
	FBXPATTERN selecting_Object;

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<GameObject*> createObjectList_;

	//hModel���ǂ̃��f�����̃y�A��\��
	std::vector<std::pair<int, FBXPATTERN>> modelPair_;

	bool isUpdate_;

	int nextObjectId_;

	//�C���X�^���X���쐬����objectList�ɓ����e���v���[�g
	template <class T>
	T* CreateInstance()
	{
		//T* pObject = Instantiate<T>(this);
		//AddCreateObject(pObject);
		//pObject->SetObjectID(nextObjectId_); //������I�u�W�F�N�g���Ɏ��ʂ��邽�߂�ID��t����
		//return pObject;
		return nullptr;
	}

};