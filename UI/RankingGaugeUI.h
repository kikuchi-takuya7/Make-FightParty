#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

class Text;

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
    /// �A�j���[�V�������I�������
    /// </summary>
    /// <returns>�I����Ă���true</returns>
    bool IsEndAnim();


    void SetName(std::string name) { name_ = name; }

private:

    int hPict_[GAUGE_NUM];

    //�v���C���[��
    Text* pText_;
    std::string name_;

};