#pragma once
#include "../../GameObject.h"
#include "../../Model.h"
#include "StageSourceBase.h"

class Timer;

/// <summary>
/// ���Ԋu�ōU������C��
/// </summary>
class Cannon : public StageSourceBase
{

public:
    //�R���X�g���N�^
    Cannon(GameObject* parent);

    //�f�X�g���N�^
    ~Cannon();

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

    //���C���̃G�t�F�N�g
    void FiringEffect();

    //�^�C�}�[
    Timer* timer_;

    //���ʉ�
    int hAudio_;

    //���̏��
    BulletData bulletData_;
};