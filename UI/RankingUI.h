#pragma once
#include "../Engine/GameObject.h"
#include <vector>

class RankingGaugeUI;

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

    void AddGaugeValue(int ID, int value);

    bool IsAllEndAnim();

    void ResetPos();

    ///////////ランキングゲージも一緒に操る関数/////////////
    void StopDraw();
    void StartDraw();
    void StopUpdate();
    void StartUpdate();

    ////////////////アクセス関数///////////////

    void SetPlayerName(int ID, std::string str);

private:

    int hPict_;

    std::vector<RankingGaugeUI*> pGaugeList_;

};