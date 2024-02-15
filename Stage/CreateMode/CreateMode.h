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

struct SettingObjectInfo {

	//���f���ԍ�
	int hModel;

	//Transform
	Transform trans;

	//�ړ����I����Ă��邩
	bool moved;

	//�R���X�g���N�^
	SettingObjectInfo() {
		hModel = -1;
		Transform t;
		trans = t;
		moved = false;
	}

	SettingObjectInfo(int h, Transform t,bool m) {
		hModel = h;
		trans = t;
		moved = m;
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


	//������
	void Initialize() override;
	void SelectInit();
	void SettingInit();

	//�X�V
	void Update() override;
	void SelectUpdate();
	void SettingUpdate();

	//�`��
	void Draw() override;

	//�J��
	void Release() override;



	/// <summary>
	/// �I�u�W�F�N�g���쐬����
	/// </summary>
	/// <param name="hModel">���f���ԍ�</param>
	/// <param name="trans">���f����Transform</param>
	/// <param name="element">���Ԗڂ̗v�f��</param>
	void CreateObject(int hModel,Transform trans, int element);


	//createObjectList�ɓ����
	void AddCreateObject(StageSourceBase* object);

	/// <summary>
	/// �}�E�X�J�[�\���̈ʒu����o��x�N�g�����擾����
	/// </summary>
	/// <param name="front">�O�̃x�N�g��</param>
	/// <param name="back">���̃x�N�g��</param>
	void GetCursorRay(XMVECTOR& front, XMVECTOR& back);

	//�f�B���N�g�����̎w�肵�����ʎq�̃t�@�C���l�[�����l��	
	std::vector<std::string> GetFilePath(const std::string& dir_name, const std::string& extension) noexcept(false);

	//////////////////////�Z���N�g���[�h�Ŏg���֐�////////////////////////////////

	/// <summary>
	/// AI���I�u�W�F�N�g��I������֐�
	/// </summary>
	/// <param name="ID">�I�u�W�F�N�g��I������G��ID</param>
	void AISelectObject(int ID);

	/// <summary>
	/// settingObject�ɑI�񂾃I�u�W�F�N�g�̏���n��
	/// </summary>
	/// <param name="ID">�I�u�W�F�N�g��I�񂾐l��ID</param>
	void SelectObject(int ID);

	/// <summary>
	/// �J�[�\����������ł�I�u�W�F�N�g�ɍ��킳���Ă��邩
	/// </summary>
	/// <param name="front">��΂����C�̑O�����x�N�g��</param>
	/// <param name="back">�������̃x�N�g��</param>
	/// <returns>�������Ă�����true</returns>
	bool IsSelectingOverlapCursor(XMVECTOR front, XMVECTOR back);

	/// <summary>
	/// �v���C���[�S�����I�u�W�F�N�g��I�яI�������
	/// </summary>
	/// <returns>�I�яI����Ă�����true</returns>
	bool IsAllDecidedObject();

	//////////////////////�Z�b�e�B���O���[�h�Ŏg���֐�////////////////////////////////

	bool IsStageOverlapCursor(XMVECTOR front, XMVECTOR back);

	bool IsOverlapPosition();

	/// <summary>
	/// Ai���I�񂾃I�u�W�F�N�g�𓮂����ʒu�����߂�
	/// </summary>
	void AIMovingObject();

	////////////////////////���[�h��؂�ւ���֐�///////////////////

	void ToSelectMode();
	void ToSettingMode();
	void ToGameMode();

	///////////////////////////�A�N�Z�X�֐�///////////////////////////////

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

	
	//////////////////////////�I�u�W�F�N�g����Ɏg���ϐ�///////////////////////
	
	//���f���̃f�[�^��ۑ�����z��
	std::vector<ModelInfo> modelData_;

	//�\�������Ă���I�u�W�F�N�g�̈ꗗ�i���f���ԍ��j
	std::vector<int> viewObjectList_;

	//viewObjectList�̂ǂ����I�΂ꂽ��,setting���[�h�ł͂ǂ���setting�I�u�W�F�N�g���I�΂ꂽ��
	int selecting_Object_;

	//�v���C���[���ݒu����I�u�W�F�N�g�B{���f���ԍ�,���̃��f����Transform}�ǂ̃v���C���[���I��ł邩�͗v�f�ԖڂŎ����Ă���
	std::vector<SettingObjectInfo> settingObject_;

	//�N���G�C�g���[�h���̃����L���O
	std::vector<int> ranking_;

	//���ɑI������v���C���[��ID(ranking�Ńr�����珇�ԂɑI�΂���p)
	int nextSelectCharacterID_;

	//�I�������I�u�W�F�N�g���ړ�����
	bool isObjectMoving_;

	//////////////////////////���̑�//////////////////////////////

	//�쐬�����I�u�W�F�N�g���X�g
	std::list<StageSourceBase*> createObjectList_;

	//���f������]������ϐ�
	float rotateObjectValue_;

	//�G�̍ŏ���ID
	int startEnemyID_;

	//���Ԃ�u���̂Ɏg��
	Timer* timer_;


	//�C���X�^���X���쐬���ĐF�X����e���v���[�g
	template <class T>
	T* CreateInstance(int hModel, Transform trans, int ID)
	{
		T* pObject = Instantiate<T>(this);
		AddCreateObject(pObject);
		pStage_->PushStageSource(pObject);
		pStage_->SetStageCost(trans.position_, pObject->GetStageCost());
		
		//AI���I�񂾃I�u�W�F�N�g�Ȃ�^�񒆂��������蓮���悤��
		if (ID >= startEnemyID_) {
			Transform objTrans;
			objTrans.position_ = XMFLOAT3(15.0f, ZERO, 15.0f);
			objTrans.rotate_ = trans.rotate_;
			pObject->SetMoveLastPos(trans.position_);
			pObject->SetTransform(objTrans);
		}
		else {
			pObject->SetMoveLastPos(trans.position_);
			pObject->SetTransform(trans);
		}

		pObject->Leave();
		pObject->SetHandle(hModel);
		return pObject;
	}

};