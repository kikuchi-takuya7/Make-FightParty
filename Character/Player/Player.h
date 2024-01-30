#pragma once
#include "../../Engine/GameObject.h"
//#include "PlayerState/PlayerState.h"
#include "PlayerState/PlayerStateManager.h"
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

    /// <summary>
    /// 別のcolliderに衝突したときに呼ばれる関数
    /// </summary>
    /// <param name="pTarget">当たった相手</param>
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////メンバ関数/////////////////////////////////////

    ///////////////////アクセス関数/////////////////////////////////////
    void ChangeState(PlayerStatePattern nextState);


private:

    //int hModel_;

    ////HP等のステータス
    //Status status_;

    PlayerStateManager* pState_; //プレイヤーの状態を表す
};