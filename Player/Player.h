#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../State/PlayerStateManager.h"


class PlayerState;

//◆◆◆を管理するクラス
class Player : public GameObject
{

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// 状態を変更する
    /// </summary>
    /// <param name="nextState">次の状態</param>
    void ChangeState(PlayerStateManager* nextState);

    /// <summary>
    /// プレイヤーの移動処理
    /// </summary>
    void MovePlayer();

private:

    int hModel_;

    PlayerStateManager* pState_; //プレイヤーの状態を表す

};