#pragma once
#include "../Engine/GameObject.h"



//πΗ·ιNX
class PlayerFoot : public GameObject
{

public:
    //RXgN^
    PlayerFoot(GameObject* parent);

    //fXgN^
    ~PlayerFoot();

    //ϊ»
    void Initialize() override;

    //XV
    void Update() override;

    //`ζ
    void Draw() override;

    //Jϊ
    void Release() override;

    void Imgui_Window() override;

private:

    enum PLAYERFOOT {

        TIP,
        ROOT,
        NUM
    };

    int hModel_[NUM];
    int hBallModel_;
    
    Transform footTipTrans_;//_Μζ[ΜTransform
    Transform footRootTrans_;//_Μͺ{
    XMFLOAT3 goalValue_;

    XMFLOAT3 prevFootTipPos_;
    float prevCosY_;//Y²ρ]Μpxcos
    float prevCosZ_;//Z²ρ]Μpxcos
};