#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// ���ނƓݑ��ɂȂ�D
/// </summary>
class Mud : public StageSourceBase
{

public:
    //�R���X�g���N�^
    Mud(GameObject* parent);

    //�f�X�g���N�^
    ~Mud();

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;


    void OnCollision(GameObject* pTarget) override;

    //�A�N�Z�X�֐�
    float GetDeceleration() { return deceleration_Rate_; }

private:

    //���̓D�𓥂�ł��鎞�̌�����
    float deceleration_Rate_;

};