#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

/// <summary>
/// �����L���O�Q�[�W���̃L���X�R�A�Q�[�W���Ǘ�����N���X
/// </summary>
class KillScore : public GaugeBase
{


public:



    //�R���X�g���N�^
    KillScore(GameObject* parent);

    //�f�X�g���N�^
    ~KillScore();

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