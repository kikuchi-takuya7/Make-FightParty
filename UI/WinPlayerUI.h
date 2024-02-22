#pragma once
#include "../Engine/GameObject.h"

class WinPlayerUI : public GameObject
{


public:

    //コンストラクタ
    WinPlayerUI(GameObject* parent);

    //デストラクタ
    ~WinPlayerUI();

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