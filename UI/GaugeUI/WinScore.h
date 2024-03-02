#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

/// <summary>
/// �ꏟ���̃X�R�A�Q�[�W���Ǘ�����N���X
/// </summary>
class WinScore : public GaugeBase
{


public:



    //�R���X�g���N�^
    WinScore(GameObject* parent);

    //�f�X�g���N�^
    ~WinScore();

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