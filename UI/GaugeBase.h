#pragma once
#include "../Engine/GameObject.h"


//�Q�[�W�N���X�̓Q�[�W�̍ő��100%�i�܂�1.0�j�ƂȂ�悤�ɍ��B
//�\���̑傫���ɂ���ĕ\���T�C�Y��ς�����悤�ɍ��
//�\������ʒu�́A�O����i�g�����j����w��ł���悤�ɂ���
//���Z����֐��ƁA���Z����֐��ƁA���݂̒l���擾����֐���p�ӂ���

class GaugeBase : public GameObject
{


public:



    //�R���X�g���N�^
    GaugeBase(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~GaugeBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;


    ////////////////�q�̊֐�////////////////

    /// <summary>
    /// �p����p�̏�����
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// �p����p��Update
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// �p����p�̕`��
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// �p����p�̊J��
    /// </summary>
    virtual void ChildRelease() {};


    /// <summary>
    /// �Q�[�W�̒l���Z�b�g����
    /// </summary>
    /// <param name="nowGaugeBase">���̒l</param>
    /// <param name="maxGaugeBase">�l�̍ő�l</param>
    void SetGauge(int nowGaugeBase, int maxGaugeBase);

    /// <summary>
    /// ���̃Q�[�W�̒l��ς���
    /// </summary>
    /// <param name="nowGaugeBase">���̒l</param>
    void SetNowGauge(int nowGaugeBase);

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

protected:

    float nowGauge_; //���̒l
    int maxGauge_; //�ő�l
    float animGauge_; //�A�j���[�V�������HP

private:

    
};