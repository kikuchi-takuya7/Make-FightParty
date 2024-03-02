#pragma once
#include "../../Engine/GameObject.h"
#include "GaugeBase.h"
#include <queue>
#include <vector>
#include <utility>

//スコアゲージの一覧
enum SCOREGAUGELIST {
    WIN_GAUGE,
    KILL_GAUGE,
    TRAP_KILL_GAUGE,
    GAUGE_NUM
};

class Text;
class GaugeBase;

/// <summary>
/// ランキングゲージを管理するクラス
/// </summary>
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
    /// 追加するスコアを入れる
    /// </summary>
    /// <param name="score">追加するスコアゲージ</param>
    void PushScore(SCOREGAUGELIST score);

    /// <summary>
    /// 全てのゲージのアニメーションが終わっているかどうか
    /// </summary>
    /// <returns>全て終わっていたらtrue</returns>
    bool IsAllEndAnim();

    /// <summary>
    /// ゲージのアニメーションを即座に終わらせる（一ゲージ分だけ）
    /// </summary>
    void AllEndAnim();

    void SetName(std::string name) { name_ = name; }

private:

    /// <summary>
    /// 表示するスコアのインスタンスを作る
    /// </summary>
    /// <param name="score">インスタンスを作るスコアゲージ</param>
    void CreateScore(SCOREGAUGELIST score);

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


    

};