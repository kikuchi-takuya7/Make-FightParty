#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <stack>

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


    ////////////////�A�N�Z�X�֐�//////////////////

    /// <summary>
    /// �X�e�[�W�̃R�X�g���Z�b�g����
    /// </summary>
    /// <param name="pos">���̃I�u�W�F�N�g�̈ʒu</param>
    /// <param name="cost">�I�u�W�F�N�g�̃R�X�g</param>
    void SetStageCost(XMFLOAT3 pos, int cost);

    /// <summary>
    /// Astar�A���S���Y���ŏo���o�H��\������ׂɃ��f����ς���ׂ̊֐�
    /// </summary>
    /// <param name="pair">�o�H�T���ŏo���o�H</param>
    void SetStageModel(std::stack<std::pair<int,int>> pair);

    void SetCreateMode(CreateMode* createMode) { pCreateMode_ = createMode; }
    void PushStageSource(StageSourceBase* source) { pStageSourceList_.emplace_back(source); }
    int GetStageHandle() { return hModel_; }
    XMFLOAT3 GetStageSize();
    std::vector<std::vector<long>> GetMap() { return stageCost_; }
    

private:

    //���ʂ�1�}�X���̃X�e�[�W�̃��f���ԍ�
    int hModel_;

    //�F��ς���p��1�}�X���̃X�e�[�W���f���ԍ�
    int debugModel_;

    //�N���G�C�g���[�h�̃C���X�^���X
    CreateMode* pCreateMode_;

    //�񎟌��z��Ń}�b�v��R�X�g��\��
    std::vector<std::vector<long>> stageCost_; 

    //Astar�A���S���Y���̃f�o�b�N�p�ɐF��ς���ׂ̔z��
    std::vector<std::vector<long>> stageModel_;

    //�N���G�C�g���[�h�ō��ꂽ���f���ꗗ
    std::list<StageSourceBase*> pStageSourceList_;

};