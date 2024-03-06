#pragma once
#include "../../Engine/GameObject.h"
#include "../Character.h"

class PlayerStateManager;

/// <summary>
/// 操作するプレイヤーのクラス
/// </summary>
class Player : public Character
{

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    /////////////オーバーライドした関数/////////////////

    //初期化
    void ChildInitialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void ChildDraw() override;

    //開放
    void ChildRelease() override;

    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 入力によって移動する関数
    /// </summary>
    void MoveCharacter() override;

    /// <summary>
    /// メタAIにステータスを伝える関数
    /// </summary>
    void TellStatus() override;


private:

    

};