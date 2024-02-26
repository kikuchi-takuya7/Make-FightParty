#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <queue>
#include <vector>
#include <utility>

enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

class Text;
class GaugeBase;

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

    void PushScore(SCOREGAUGELIST score);

    bool IsAllEndAnim();

    void AllEndAnim();

    void SetName(std::string name) { name_ = name; }

private:

    //プレイヤー名
    Text* pText_;
    std::string name_;

    //表示するスコア
    std::vector<std::pair<GaugeBase*,SCOREGAUGELIST>> gauge_;
    
    //順番に表示させるためのスタック
    std::queue<SCOREGAUGELIST> nextScore_;

    //次のゲージの位置
    XMFLOAT3 gaugePos_;

    //今アニメーションしてるゲージの要素番号
    int nowAnimGauge_;


    void SetScore(SCOREGAUGELIST score);

};