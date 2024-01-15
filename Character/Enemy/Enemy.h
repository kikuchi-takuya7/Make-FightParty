#pragma once
#include "../../Engine/GameObject.h"
#include "EnemyState/EnemyStateManager.h"
#include "EnemyState/EnemyState.h"
#include "../Character.h"
#include "../../AI/CharacterAI.h"

class PlayerStateManager;

/// <summary>
/// キャラクターAIで動かす敵のクラス
/// </summary>
class Enemy : public Character
{

public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

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
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetTypee) override;

    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 移動する
    /// </summary>
    void Move();

    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP等のステータス
    //Status status_;

    EnemyStateManager* pState_; //敵の状態を表す

    //当たり判定
    //BoxCollider* pBodyCollision_;

};