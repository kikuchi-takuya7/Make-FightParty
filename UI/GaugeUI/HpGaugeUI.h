#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"

//HPゲージの画像をenumで管理
enum HPIMAGE {
    FLAME,
    GaugeMAIN,
    GaugeLOW,
    GaugeWHITE,
    HPIMAGE_NUM
};

/// <summary>
/// HPゲージを管理するクラス
/// </summary>
class HpGaugeUI : public GaugeBase
{


public:

    

    //コンストラクタ
    HpGaugeUI(GameObject* parent);

    //デストラクタ
    ~HpGaugeUI();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;

private:

    int hPict_[HPIMAGE_NUM];
};