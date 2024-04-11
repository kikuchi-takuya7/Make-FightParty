#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;

/// <summary>
/// ���Ԋu�ōU������C��
/// </summary>
class AutoCannon : public StageSourceBase
{

public:
    //�R���X�g���N�^
    AutoCannon(GameObject* parent);

    //�f�X�g���N�^
    ~AutoCannon();

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

    void FiringEffect();

    Timer* timer_;

    int hAudio_;
};