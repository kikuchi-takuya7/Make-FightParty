#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

/// <summary>
/// �I�u�W�F�N�g�ŃL�����ꂽ���p�̃Q�[�WUI�N���X
/// </summary>
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


private:

    int hPict_;

};