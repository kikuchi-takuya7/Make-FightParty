#pragma once
#include "../../Engine/GameObject.h"
#include <stack>
#include <vector>

enum CREATESTATE {
	SELECT_MODE,
	SETTING_MODE,
	NONE
};

//�V�����t�@�C����ǉ�������A������CreateObject�ɗv�f���蓮�Œǉ�����
enum FBXPATTERN {
	CANNON,
	NEEDLE,
	ONEBROCK,
	TESTFLOOR,
	PATTERN_END
};

struct ModelInfo {

	//���f���ԍ�
	int hModel;

	//���f���̎��
	FBXPATTERN modelPattern;

	//������
	ModelInfo(int h, FBXPATTERN pattern) {
		hModel = h;
		modelPattern = pattern;
	}

};

struct SelectModelInfo {


	//


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
	void ViewInit();
	void SettingInit();

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

	void SelectObject();

	//createObjectList�ɓ����
	void AddCreateObject(GameObject* object);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////�Z���N�g���[�h�Ŏg���֐�////////////////////////////////

	bool IsOverlapCursor();

	bool IsAllDecidedObject();

	void SwapElements();

	//////////////////////�Z�b�e�B���O���[�h�Ŏg���֐�////////////////////////////////

	void MovingObject();



	/////////////////////////�J�����ړ��Ŏg���֐�//////////////////////////////////

	float GetRateValue(float begin, float end, float rate);

	void MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar);

	///////////////////////////�A�N�Z�X�֐�///////////////////////////////
	void ToSelectMode();
	void ToSettingMode();
	CREATESTATE GetState() { return nowState_; }

private:

	CREATESTATE nowState_;

	std::vector<ModelInfo> modelData;

	//Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
	std::vector<std::string> fileName_;

	//viewObjectList�̂ǂ����I�΂ꂽ��
	int selecting_Object;

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<GameObject*> createObjectList_;

	//�\�������Ă���I�u�W�F�N�g�̈ꗗ�i���f���ԍ��j
	std::vector<int> viewObjectList_;

	//�v���C���[���ݒu����I�u�W�F�N�g�B{���f���ԍ�,���W}�ǂ̃v���C���[���I��ł邩�͗v�f�ԖڂŎ���.���f���p�^�[���͓����K�v�Ȃ�����
	std::vector<std::pair<int,XMFLOAT3>> settingObject_;

	float rotateObjectValue_;

	int nextObjectId_;

	int flame_;
	
	//////�J���������炩�ɓ������̂Ɏg���ϐ�

	//�ɋ}��t���郌�[�g
	float camMoveRate_;



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