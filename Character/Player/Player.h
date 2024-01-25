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
    void Initialize() override;

    //更新
    void ChildUpdate() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// 別のcolliderに衝突したときに呼ばれる関数
    /// </summary>
    /// <param name="pTarget">当たった相手</param>
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// プレイヤーの移動処理
    /// </summary>
    void MoveCharacter() override;

    /// <summary>
    /// 攻撃用のコライダーをセットする
    /// </summary>
    void SetAttackCollider();

    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }
    void ChangeState(StatePattern nextState);
    void ChangeKnockBack(bool next) { isKnockBack_ = next; }
    bool IsKnockBack() { return isKnockBack_; }


private:

    //int hModel_;

    ////HP等のステータス
    //Status status_;

    PlayerStateManager* pState_; //プレイヤーの状態を表す

    bool isKnockBack_; //ノックバック中ならtrue

};