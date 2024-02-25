#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"

enum HPIMAGE {
    FLAME,
    GaugeMAIN,
    GaugeLOW,
    GaugeWHITE,
    HPIMAGE_NUM
};

class HpGaugeUI : public GaugeBase
{


public:

    

    //�R���X�g���N�^
    HpGaugeUI(GameObject* parent);

    //�f�X�g���N�^
    ~HpGaugeUI();

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

private:

    int hPict_[HPIMAGE_NUM];
};