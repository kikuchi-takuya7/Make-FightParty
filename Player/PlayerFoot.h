#pragma once
#include "../Engine/GameObject.h"



//���������Ǘ�����N���X
class PlayerFoot : public GameObject
{

public:
    //�R���X�g���N�^
    PlayerFoot(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerFoot();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Imgui_Window() override;

private:

    enum PLAYERFOOT {

        FOOT,
        LEG,
        NUM
    };

    int hModel_[NUM];
    int hBallModel_;
    Transform footTrans_;
    Transform footRoot_;
    XMVECTOR goalVec_;//�ڕW�n�_�܂ł̃x�N�g��
    XMVECTOR footVec_;//�_�̃x�N�g��
    XMFLOAT3 goalValue_;
};