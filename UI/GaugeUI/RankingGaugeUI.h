#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <queue>
#include <vector>
#include <utility>

//�X�R�A�Q�[�W�̈ꗗ
enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

class Text;
class GaugeBase;

/// <summary>
/// �����L���O�Q�[�W���Ǘ�����N���X
/// </summary>
class RankingGaugeUI : public GaugeBase
{


public:



    //�R���X�g���N�^
    RankingGaugeUI(GameObject* parent);

    //�f�X�g���N�^
    ~RankingGaugeUI();

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

    /// <summary>
    /// �ǉ�����X�R�A������
    /// </summary>
    /// <param name="score">�ǉ�����X�R�A�Q�[�W</param>
    void PushScore(SCOREGAUGELIST score);

    /// <summary>
    /// �S�ẴQ�[�W�̃A�j���[�V�������I����Ă��邩�ǂ���
    /// </summary>
    /// <returns>�S�ďI����Ă�����true</returns>
    bool IsAllEndAnim();

    /// <summary>
    /// �Q�[�W�̃A�j���[�V�����𑦍��ɏI��点��i��Q�[�W�������j
    /// </summary>
    void AllEndAnim();

    void SetName(std::string name) { name_ = name; }

private:

    /// <summary>
    /// �\������X�R�A�̃C���X�^���X�����
    /// </summary>
    /// <param name="score">�C���X�^���X�����X�R�A�Q�[�W</param>
    void CreateScore(SCOREGAUGELIST score);

    //�v���C���[��
    Text* pText_;
    std::string name_;

    //�\������X�R�A
    std::vector<std::pair<GaugeBase*,SCOREGAUGELIST>> gauge_;
    
    //���Ԃɕ\�������邽�߂̃X�^�b�N
    std::queue<SCOREGAUGELIST> nextScore_;

    //���̃Q�[�W�̈ʒu
    XMFLOAT3 gaugePos_;

    //���A�j���[�V�������Ă�Q�[�W�̗v�f�ԍ�
    int nowAnimGauge_;


    

};