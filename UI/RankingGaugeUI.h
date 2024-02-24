#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

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

private:

    int hPict_;

    //�v���C���[��
    Text* pText_;

};