#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// ��}�X���̕��ʂ̃u���b�N
/// </summary>
class OneBrock : public StageSourceBase
{
    
public:
    //�R���X�g���N�^
    OneBrock(GameObject* parent);

    //�f�X�g���N�^
    ~OneBrock();

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