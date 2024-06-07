#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <queue>

class RankingGaugeUI;
class Text;
enum SCOREGAUGELIST;
class RateFrame;

/// <summary>
/// 一試合の勝者が決まった後に出るランキングのUI
/// </summary>
class RankingUI : public GameObject
{


public:

    //コンストラクタ
    RankingUI(GameObject* parent);

    //デストラクタ
    ~RankingUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    bool IsAllEndAnim();

    void EndAnim();

    void ResetPos();

    ////////////////アクセス関数///////////////

    /// <summary>
    /// プレイヤーの名前を設定
    /// </summary>
    /// <param name="ID">設定したいプレイヤーのID</param>
    /// <param name="str">名前</param>
    void SetPlayerName(int ID, std::string str);

    /// <summary>
    /// スコアを追加する
    /// </summary>
    /// <param name="ID">スコアを追加したいプレイヤーのID</param>
    /// <param name="score">追加するスコアの種類</param>
    /// <param name="num">何個追加するか</param>
    void SetScore(int ID, SCOREGAUGELIST score, int num = 1);

private:

    int hPict_;

    //{ゲージのインスタンス、スコア}
    std::vector<RankingGaugeUI*> pGaugeList_;

    Text* pText_;

    RateFrame* rate_;
};