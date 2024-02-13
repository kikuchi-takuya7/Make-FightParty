#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class CreateMode;
class StageSourceBase;

//stage���Ǘ�����N���X
class Stage : public GameObject
{

public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //////////////�I�[�o�[���[�h�����֐�///////////////

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void AllStartUpdate();

    void AllStopUpdate();

    ///////////////CreateMode�Ŏg���֐�///////////////////////

    void StageCostCheck();


    ////////////////�A�N�Z�X�֐�//////////////////

    /// <summary>
    /// �X�e�[�W�̃R�X�g���Z�b�g����
    /// </summary>
    /// <param name="pos">���̃I�u�W�F�N�g�̈ʒu</param>
    /// <param name="cost">�I�u�W�F�N�g�̃R�X�g</param>
    void SetStageCost(XMFLOAT3 pos, int cost);

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }
    void PushStageSource(StageSourceBase* source) { pStageSourceList_.emplace_back(source); }
    int GetStageHandle() { return hModel_; }
    XMFLOAT3 GetStageSize();
    std::vector<std::vector<long>> GetMap() { return map_; }
    

private:

    int hModel_;

    CreateMode* pCreateMode_;

    //�񎟌��z��Ń}�b�v��R�X�g��\��
    std::vector<std::vector<long>> map_; 

    //�K�v���邩�͂킩��Ȃ�
    std::list<StageSourceBase*> pStageSourceList_;

};