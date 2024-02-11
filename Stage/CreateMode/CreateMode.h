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
class Timer;

//�I�u�W�F�N�g�ǉ����[�h���Ǘ�����N���X
//2�������[�h����������܂Ƃ߂�����state�ɂ��������ǂ��H
class CreateMode :public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CreateMode(GameObject* parent);

	//////////////////�I�[�o�[���C�h�����֐�///////////////////////

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


	////////////////////�I�u�W�F�N�g�𑀂�֐�/////////////////////

	/// <summary>
	/// �I�u�W�F�N�g���쐬����
	/// </summary>
	/// <param name="hModel">���f���ԍ�</param>
	/// <param name="trans">���f����Transform</param>
	/// <param name="element">���Ԗڂ̗v�f��</param>
	void CreateObject(int hModel,Transform trans, int element);


	//createObjectList�ɓ����
	void AddCreateObject(StageSourceBase* object);

	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��	
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////�Z���N�g���[�h�Ŏg���֐�////////////////////////////////

	void AISelectObject(int ID);

	void SelectObject(int ID);

	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsAllDecidedObject();

	//////////////////////�Z�b�e�B���O���[�h�Ŏg���֐�////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsOverlapPosition();

	void AIMovingObject();

	///////////////////////////�A�N�Z�X�֐�///////////////////////////////
	void ToSelectMode();
	void ToSettingMode();
	void ToGameMode();
	CREATESTATE GetState() { return nowState_; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetStage(Stage* stage) { pStage_ = stage; }
	void SetStartEnemyID(int ID) { startEnemyID_ = ID; }
	std::list<StageSourceBase*> GetCreateObjectList() { return createObjectList_; }


private:

	//���[�h���Ǘ�����ϐ�
	CREATESTATE nowState_;

	/////////////AI���̃C���X�^���X///////////

	MetaAI* pMetaAI_;
	NavigationAI* pNavigationAI_;
	Stage* pStage_;


	/////////�I�u�W�F�N�g����Ɏg���ϐ�////////////

	//���f���̃f�[�^��ۑ�����z��
	std::vector<ModelInfo> modelData_;

	//viewObjectList�̂ǂ����I�΂ꂽ��,setting���[�h�ł͂ǂ���setting�I�u�W�F�N�g���I�΂ꂽ��
	int selecting_Object_;

	//�\�������Ă���I�u�W�F�N�g�̈ꗗ�i���f���ԍ��j
	std::vector<int> viewObjectList_;

	//�v���C���[���ݒu����I�u�W�F�N�g�B{���f���ԍ�,���̃��f����Transform}�ǂ̃v���C���[���I��ł邩�͗v�f�ԖڂŎ����Ă���
	std::vector<std::pair<int,Transform>> settingObject_;

	//�N���G�C�g���[�h���̃����L���O
	std::vector<int> ranking_;

	//���ɑI������v���C���[��ID
	int nextSelectCharacterID_;

	/////////////���̑�/////////

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<StageSourceBase*> createObjectList_;

	//���f������]������ϐ�
	float rotateObjectValue_;

	//�ҋ@���鎞��
	int flame_;

	//�G�̍ŏ���ID
	int startEnemyID_;

	Timer* timer_;

	//////�J���������炩�ɓ������̂Ɏg���ϐ�

	bool isCamMoveEnd_;

	//�C���X�^���X���쐬���ĐF�X����e���v���[�g
	template <class T>
	T* CreateInstance(int hModel, Transform trans)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		pStage_->SetStageCost(trans.position_, pObject->GetStageCost());
		pObject->SetTransform(trans);
		pObject->SetHandle(hModel);
		return pObject;
	}

};