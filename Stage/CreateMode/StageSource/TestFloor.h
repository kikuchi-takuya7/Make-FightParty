#pragma once
#include "../../GameObject.h"
#include "StageSourceBase.h"

//���������Ǘ�����N���X
class TestFloor : public StageSourceBase
{


public:
    //�R���X�g���N�^
    TestFloor(GameObject* parent);

    //�f�X�g���N�^
    ~TestFloor();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};