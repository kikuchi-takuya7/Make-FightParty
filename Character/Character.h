#pragma once
#include "../../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};


/// <summary>
/// 操作するプレイヤーのクラス
/// </summary>
class Character : public GameObject
{

public:
    //コンストラクタ
    Character(GameObject* parent);

    //デストラクタ
    ~Character();

    /////////////オーバーライドした関数/////////////////

    //初期化
    virtual void Initialize() override;

    //更新
    virtual void Update() override;

    //描画
    virtual void Draw() override;

    //開放
    virtual void Release() override;

    /// <summary>
    /// 別のcolliderに衝突したときに呼ばれる関数
    /// </summary>
    /// <param name="pTarget">当たった相手</param>
    virtual void OnCollision(GameObject* pTarget) override;


    /////////////////////メンバ関数/////////////////////////////////////


    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }


private:

    int hModel_;

    //HP等のステータス
    Status status_;

    //CharacterStateManager* pState_; //プレイヤーの状態を表す

    //当たり判定
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;
    XMFLOAT3 attackCollisionCenter_;//AttackCollisionの攻撃判定の向き
    XMFLOAT3 attackCollisionSize_;//攻撃判定の大きさ



};