#pragma once
#include "../Engine/GameObject.h"
#include <vector>
#include <queue>

class RankingGaugeUI;
enum SCOREGAUGELIST;

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

    void SetPlayerName(int ID, std::string str);

    void SetScore(int ID, SCOREGAUGELIST score, int num);

private:

    int hPict_;

    //{ゲージのインスタンス、スコア}
    std::vector<RankingGaugeUI*> pGaugeList_;
};