#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool isDead;
};


/// <summary>
/// キャラクターの基底クラス
/// </summary>
class Character : public GameObject
{


public:
    //コンストラクタ
    Character(GameObject* parent, std::string name);

    //デストラクタ
    ~Character();

    /////////////オーバーライドした関数/////////////////

    //初期化
    virtual void Initialize() override;

    //更新
    void Update() override;

    //描画
    virtual void Draw() override;

    //開放
    virtual void Release() override;

    /// <summary>
    /// 別のcolliderに衝突したときに呼ばれる関数
    /// </summary>
    /// <param name="pTarget">当たった相手</param>
    virtual void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 攻撃に当たった時
    /// </summary>
    /// <param name="damage">食らったダメージ量</param>
    void HitDamage(int damage);

    //////////////////子供に継承させる関数//////////////////////////////

    /// <summary>
    /// 継承先用の初期化
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// 継承先用のUpdate
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// 継承先用の描画
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// 継承先用の開放
    /// </summary>
    virtual void ChildRelease() {};

    /// <summary>
    /// キャラクターの移動処理
    /// </summary>
    virtual void MoveCharacter() {};

    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    void SetDead() { status_.isDead = true; }

protected:

    int hModel_;

    //HP等のステータス
    Status status_;

    //CharacterStateManager* pState_; //プレイヤーの状態を表す

    //当たり判定
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

private:

    



};