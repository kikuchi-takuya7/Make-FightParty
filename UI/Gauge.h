#pragma once
#include "../Engine/GameObject.h"

enum HPIMAGE {
    FLAME,
    GAUGEMAIN,
    GAUGELOW,
    GAUGEWHITE,
    HPIMAGE_NUM
};


//�Q�[�W�N���X�̓Q�[�W�̍ő��100%�i�܂�1.0�j�ƂȂ�悤�ɍ��B
//�\���̑傫���ɂ���ĕ\���T�C�Y��ς�����悤�ɍ��
//�\������ʒu�́A�O����i�g�����j����w��ł���悤�ɂ���
//���Z����֐��ƁA���Z����֐��ƁA���݂̒l���擾����֐���p�ӂ���

class Gauge : public GameObject
{


public:

    

    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �Q�[�W�̒l���Z�b�g����
    /// </summary>
    /// <param name="nowGauge">���̒l</param>
    /// <param name="maxGauge">�l�̍ő�l</param>
    void SetGauge(int nowGauge, int maxGauge);

    /// <summary>
    /// ���̃Q�[�W�̒l��ς���
    /// </summary>
    /// <param name="nowGauge">���̒l</param>
    void SetNowGauge(int nowGauge);

    /// <summary>
    /// �l�������Z����
    /// </summary>
    /// <param name="v">���Z�������l</param>
    void AddValue(float v);

    /// <summary>
    /// �l�������̒l�ɕύX����
    /// </summary>
    /// <param name="v">�ύX��̒l</param>
    void SetValue(float v);

    float GetValue();

private:

    int hPict_[HPIMAGE_NUM];

    float nowGauge_; //���̒l
    int maxGauge_; //�ő�l
    float animGauge_; //�A�j���[�V�������HP
};