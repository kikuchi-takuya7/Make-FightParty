#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

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

private:

    int hPict_;
};