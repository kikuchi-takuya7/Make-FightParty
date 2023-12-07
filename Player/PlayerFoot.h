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
    
    Transform footTipTrans_;//�_�̐�[��Transform
    Transform footRootTrans_;//�_�̍��{
    XMFLOAT3 goalValue_;

    XMFLOAT3 prevFootTipPos_;
    float prevCosY_;//Y����]�̊p�xcos
    float prevCosZ_;//Z����]�̊p�xcos
};