#pragma once
#include "../Engine/GameObject.h"
#include "../State/PlayerState.h"
#include "../State/PlayerStateManager.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};

class PlayerStateManager;

/// <summary>
/// 操作するプレイヤーのクラス
/// </summary>
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
    /// 別のcolliderに衝突したときに呼ばれる関数
    /// </summary>
    /// <param name="pTarget">当たった相手</param>
    void OnCollision(GameObject* pTarget) override;

    /// <summary>
    /// プレイヤーの移動処理
    /// </summary>
    void MovePlayer();

    /////////アクセス関数////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    Status status_;

    BoxCollider* pBodyCollision_;

    BoxCollider* pAttackCollision_;

    PlayerStateManager* pState_; //プレイヤーの状態を表す

};