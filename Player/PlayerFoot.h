#pragma once
#include "../Engine/GameObject.h"



//◆◆◆を管理するクラス
class PlayerFoot : public GameObject
{

public:
    //コンストラクタ
    PlayerFoot(GameObject* parent);

    //デストラクタ
    ~PlayerFoot();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
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
    
    Transform footTipTrans_;//棒の先端のTransform
    Transform footRootTrans_;//棒の根本
    XMFLOAT3 goalValue_;

    XMFLOAT3 prevFootTipPos_;
    float prevCosY_;//Y軸回転の角度cos
    float prevCosZ_;//Z軸回転の角度cos
};