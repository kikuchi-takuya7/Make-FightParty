#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

class Text;

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


    /// <summary>
    /// アニメーションが終わったか
    /// </summary>
    /// <returns>終わってたらtrue</returns>
    bool IsEndAnim();

private:

    int hPict_;

    //プレイヤー名
    Text* pText_;

};