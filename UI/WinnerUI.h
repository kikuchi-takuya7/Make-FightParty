#pragma once
#include "../Engine/GameObject.h"

//数字の画像をenumで管理
enum PLAYERNUMBER {
    ONE,
    TWO,
    THREE,
    FOUR,
    PLAYER_NUM
};

/// <summary>
/// 誰が勝ったかを表示するUI
/// </summary>
class WinnerUI : public GameObject
{


public:

    //コンストラクタ
    WinnerUI(GameObject* parent);

    //デストラクタ
    ~WinnerUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// 勝ったプレイヤーのIDをセットする
    /// </summary>
    /// <param name="ID">勝ったプレイヤーのID</param>
    void SetWinnerID(int ID) { winnerID_ = ID; }

private:

    int hPict_[PLAYER_NUM];
    int hWinnerPict_;

    int winnerID_;

};