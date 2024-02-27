#pragma once
#include "../Engine/GameObject.h"

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

private:

    int hPict_;
};