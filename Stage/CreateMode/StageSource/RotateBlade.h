#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// ��]����n�̃I�u�W�F�N�g
/// </summary>
class RotateBlade : public StageSourceBase
{

public:
    //�R���X�g���N�^
    RotateBlade(GameObject* parent);

    //�f�X�g���N�^
    ~RotateBlade();

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;


    void OnCollision(GameObject* pTarget) override;

private:


};