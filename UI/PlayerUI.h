#pragma once
#include "../Engine/GameObject.h"

class Text;
class Gauge;

/// <summary>
/// タイトルのロゴを管理するシーン
/// </summary>
class PlayerUI : public GameObject
{

public:
    //コンストラクタ
    PlayerUI(GameObject* parent);

    //デストラクタ
    ~PlayerUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;


    void SetNowHp(int nowHp);

private:

    int hPict_;

    Text* pText_;

    Gauge* pGauge_;

    Transform playerUITrans_;

};