#pragma once
#include "../Engine/GameObject.h"

enum COUNTTIME {
    
    COUNT_GO,
    COUNT_1,
    COUNT_2,
    COUNT_3,
    COUNT_NUM

};

class Timer;

/// <summary>
/// �J�E���g�_�E����UI���Ǘ�����N���X
/// </summary>
class CountDown : public GameObject
{

public:
    //�R���X�g���N�^
    CountDown(GameObject* parent);

    //�f�X�g���N�^
    ~CountDown();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Reset();

    void Start();

    bool IsFinished();

private:

    int hPict_[COUNT_NUM];
    Timer* timer_;
    
    
};