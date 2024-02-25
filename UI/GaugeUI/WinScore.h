#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

class WinScore : public GaugeBase
{


public:



    //コンストラクタ
    WinScore(GameObject* parent);

    //デストラクタ
    ~WinScore();

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;


    /// <summary>
    /// アニメーションが終わったか
    /// </summary>
    /// <returns>終わってたらtrue</returns>
    bool IsEndAnim();

private:

    int hPict_;

};