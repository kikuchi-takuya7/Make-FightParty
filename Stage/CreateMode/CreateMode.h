#pragma once
#include "../../Engine/GameObject.h"
#include "../Stage.h"
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
	PATTERN_END
};

struct ModelInfo {

	//���f���ԍ�
	int hModel;

	//���f���̎��
	FBXPATTERN modelPattern;

	//�R���X�g���N�^
	ModelInfo(int h, FBXPATTERN pattern) {
		hModel = h;
		modelPattern = pattern;
	}

};

class MetaAI;
class NavigationAI;
class Stage;
class StageSourceBase;

//�I�u�W�F�N�g�ǉ����[�h���Ǘ�����N���X
class CreateMode :public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CreateMode(GameObject* parent);

	//������
	void Initialize() override;
	void ViewInit();
	void SettingInit();

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	

	
	void CreateObject(int hModel,Transform trans);

	void SelectObject();

	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////�Z���N�g���[�h�Ŏg���֐�////////////////////////////////

	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsAllDecidedObject();

	//////////////////////�Z�b�e�B���O���[�h�Ŏg���֐�////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	void AIMovingObject();

	/////////////////////////�J�����ړ��Ŏg���֐�//////////////////////////////////

	void MoveCam(XMFLOAT3 lastPos, XMFLOAT3 lastTar);

	float GetRateValue(float begin, float end, float rate);

	///////////////////////////�A�N�Z�X�֐�///////////////////////////////
	void ToSelectMode();
	void ToSettingMode();
	CREATESTATE GetState() { return nowState_; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetStage(Stage* stage) { pStage_ = stage; }
	void SetStartEnemyID(int ID) { startEnemyID_ = ID; }
	std::list<StageSourceBase*> GetCreateObjectList() { return createObjectList_; }

	//createObjectList�ɓ����
	void AddCreateObject(StageSourceBase* object);

private:

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;
	Stage* pStage_;

	CREATESTATE nowState_;

	std::vector<ModelInfo> modelData_;

	//Map�t�@�C���̒��ɓ����Ă�fbx�t�@�C���̖��O������
	std::vector<std::string> fileName_;

	//viewObjectList�̂ǂ����I�΂ꂽ��
	int selecting_Object_;

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<StageSourceBase*> createObjectList_;

	//�\�������Ă���I�u�W�F�N�g�̈ꗗ�i���f���ԍ��j
	std::vector<int> viewObjectList_;

	//�v���C���[���ݒu����I�u�W�F�N�g�B{���f���ԍ�,���̃��f����Transform}�ǂ̃v���C���[���I��ł邩�͗v�f�ԖڂŎ����Ă���
	std::vector<std::pair<int,Transform>> settingObject_;

	float rotateObjectValue_;

	int nextObjectId_;

	int flame_;

	int startEnemyID_;

	//////�J���������炩�ɓ������̂Ɏg���ϐ�

	//�ɋ}��t���郌�[�g
	float camMoveRate_;



	//�C���X�^���X���쐬����objectList�ɓ����e���v���[�g
	template <class T>
	T* CreateInstance(int hModel, Transform trans)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		pObject->SetTransform(trans);
		pObject->SetHandle(hModel);
		return pObject;
	}

};