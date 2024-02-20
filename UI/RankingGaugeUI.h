#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

class RankingGaugeUI : public GaugeBase
{


public:



    //コンストラクタ
    RankingGaugeUI(GameObject* parent);

    //デストラクタ
    ~RankingGaugeUI();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;

private:

    int hPict_;
};