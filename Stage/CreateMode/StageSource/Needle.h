#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

/// <summary>
/// ��}�X���̕��ʂ̃u���b�N
/// </summary>
class Needle : public StageSourceBase
{

public:
    //�R���X�g���N�^
    Needle(GameObject* parent);

    //�f�X�g���N�^
    ~Needle();

    //������
    void ChildInitialize() override;

    //�X�V
    void ChildUpdate() override;

    //�`��
    void ChildDraw() override;

    //�J��
    void ChildRelease() override;

    void OnCollision(GameObject* pTarget) override;

    void SetObjCsv(CsvReader* csv, int csvPos) override;

private:

};