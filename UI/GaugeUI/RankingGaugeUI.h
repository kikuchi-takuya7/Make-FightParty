#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <queue>
#include <vector>
#include <utility>

enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

class Text;
class GaugeBase;

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

    void PushScore(SCOREGAUGELIST score);

    bool IsAllEndAnim();

    void AllEndAnim();

    void SetName(std::string name) { name_ = name; }

private:

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


    void SetScore(SCOREGAUGELIST score);

};