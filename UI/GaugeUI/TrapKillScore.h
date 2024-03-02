#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

/// <summary>
/// オブジェクトでキルされた時用のゲージUIクラス
/// </summary>
class TrapKillScore : public GaugeBase
{


public:


    //コンストラクタ
    TrapKillScore(GameObject* parent);

    //デストラクタ
    ~TrapKillScore();

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