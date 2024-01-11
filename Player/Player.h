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

    /////////////オーバーライドした関数/////////////////

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


    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// プレイヤーの移動処理
    /// </summary>
    void MovePlayer();

    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP等のステータス
    Status status_;

    //当たり判定
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;
    XMFLOAT3 attackCollisionCenter_;//AttackCollisionの攻撃判定の向き
    XMFLOAT3 attackCollisionSize_;//攻撃判定の大きさ

    PlayerStateManager* pState_; //プレイヤーの状態を表す

};