#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <stack>

/// <summary>
/// ランキングゲージ内のキルスコアゲージを管理するクラス
/// </summary>
class KillScore : public GaugeBase
{


public:



    //コンストラクタ
    KillScore(GameObject* parent);

    //デストラクタ
    ~KillScore();

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