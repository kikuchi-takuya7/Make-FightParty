#pragma once
#include "../Engine/GameObject.h"
#include "GaugeBase.h"

enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

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


    void SetName(std::string name) { name_ = name; }

private:

    int hPict_[GAUGE_NUM];

    //プレイヤー名
    Text* pText_;
    std::string name_;

};