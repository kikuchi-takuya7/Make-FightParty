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

    //�߂�l�̓��W�A��
    float DotCos(XMVECTOR vec1, XMVECTOR vec2);

private:

    enum PLAYERFOOT {

        TIP,
        ROOT,
        NUM
    };

    int hModel_[NUM];
    int hBallModel_;
    
    Transform footTipTrans_;//�_�̐�[��Transform
    Transform footRootTrans_;//�_�̍��{
    Transform ballTrans_;
    XMVECTOR ballVec_;//�{�[����transform
    XMFLOAT3 goalValue_;

    XMFLOAT3 prevBallRot_;
    float prevCosY_;//Y����]�̊p�xcos
    float prevCosZ_;//Z����]�̊p�xcos
};