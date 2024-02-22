#pragma once
#include "../Engine/GameObject.h"

class Text;
class HpGaugeUI;

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

    

    //////////////アクセス関数/////////////

    void SetMaxHp(int nowHp, int maxHp);
    void SetNowHp(int nowHp);
    void SetPlayerUIPos(XMFLOAT3 pos);
    void SetPlayerName(std::string name) { playerName_ = name; }

    void StopDraw();
    void StartDraw();

private:
    
    //PlayerUIの画像ハンドル
    int hPict_;

    //プレイヤー名
    Text* pText_;

    //HPゲージ
    HpGaugeUI* pHpGauge_;

    Transform playerUITrans_;

    //隣のUIとの距離
    int diff_;

    //プレイヤーの名前
    std::string playerName_;

};