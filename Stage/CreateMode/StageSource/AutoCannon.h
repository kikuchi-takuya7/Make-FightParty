#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;
class MetaAI;
class NavigationAI;


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


    //�A�N�Z�X�֐�
    void SetMetaAI(MetaAI* metaAI) { pMetaAI_ = metaAI; }
    void SetNavigationAI(NavigationAI* naviAI) { pNavigationAI_ = naviAI; }

private:

    //���C���̃G�t�F�N�g
    void FiringEffect();

    Timer* timer_;

    int hAudio_;

    //AI�̃C���X�^���X
    MetaAI* pMetaAI_;
    NavigationAI* pNavigationAI_;

    //�^�[�Q�b�g�̏��
    int target_;

};