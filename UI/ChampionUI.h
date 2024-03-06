#pragma once
#include "../Engine/GameObject.h"

class Timer;
class Text;

/// <summary>
/// 優勝者が決まった時に出るUI
/// </summary>
class ChampionUI : public GameObject
{


public:

    //コンストラクタ
    ChampionUI(GameObject* parent);

    //デストラクタ
    ~ChampionUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    bool IsEnd();

private:

    int hPict_;

    int hAudio_;

    Timer* pTimer_;

    Text* pText_;


};