#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    int winPoint;
    bool dead;
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
    virtual void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 攻撃に当たった時
    /// </summary>
    /// <param name="damage">食らったダメージ量</param>
    void HitDamage(int damage);

    void StopDraw();

    void StartDraw();

    void Dead();

    //////////////////////KnockBackstateで使う関数/////////////////////////////

    void KnockBackEnter(float distance);

    void KnockBackUpdate(int rigidityFlame);

    float GetRateValue(float begin, float end, float rate);

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

    virtual void ChildOnCollision() {};

    //stateまとめて処理したいけど何とかできないかな
    virtual void ResetStatus() {};

    ///////////////////アクセス関数/////////////////////////////////////
    Status GetStatus() { return status_; }
    XMFLOAT3 GetStartPos() { return startPos_; }
    void SetStatus(Status status) { status_ = status; }
    void SetStartPos(XMFLOAT3 pos) { startPos_ = pos; }
    void SetColliderRotate(XMFLOAT3 rotate) { pAttackCollision_->SetRotate(rotate); }
    void SetTargetRotate(XMFLOAT3 rot) { targetRot_ = rot; }
    void SetAttackCollider() { AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK); }


protected:

    int hModel_;

    //HP等のステータス
    Status status_;

    //CharacterStateManager* pState_; //プレイヤーの状態を表す

    //当たり判定
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

    //それぞれのキャラのスタート地点
    XMFLOAT3 startPos_;

private:


    //////ノックバック関数で使うやつ/////////

    //緩急を付けるレート
    float knockBackRate_;

    //最終的な位置
    XMFLOAT3 lastPoint_;

    XMFLOAT3 targetRot_;

    ////////////////////////////////////////////

    bool stopDraw_;


};