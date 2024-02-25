#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

class TrapKillScore : public GaugeBase
{


public:


    //�R���X�g���N�^
    TrapKillScore(GameObject* parent);

    //�f�X�g���N�^
    ~TrapKillScore();

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

};