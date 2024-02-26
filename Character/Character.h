#pragma once
#include "../Engine/GameObject.h"

struct Status {
    int hp;
    int attackPower;
    bool dead;

    int winPoint;
    int killPoint;
    int trapKillPoint;
    std::string playerName;

    Status() {
        hp = ZERO;
        attackPower = ZERO;
        dead = false;
        winPoint = ZERO;
        killPoint = ZERO;
        trapKillPoint = ZERO;
        playerName = "noname";
    }

    Status(int h, int p, bool d, int win, int kill, int obj, std::string n) {
        hp = h;
        attackPower = p;
        dead = d;
        winPoint = win;
        killPoint = kill;
        trapKillPoint = obj;
        playerName = n;
    }

};

class PlayerUI;
class CharacterStateManager;
enum CharacterStateList;

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
    void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;


    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 攻撃に当たった時
    /// </summary>
    /// <param name="damage">食らったダメージ量</param>
    /// <returns>そのダメージで死亡したらtrue</returns>
    bool HitDamage(int damage);

    void StopDraw();

    void StartDraw();

    void Dead();

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
    virtual void MoveCharacter();

    //子供の当たり判定（EnemyとPlayerで若干処理が違う）
    virtual void ChildOnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) {};

    //メタAIに情報を教える関数
    virtual void TellStatus() {};


    //stateまとめて処理したいけど何とかできないかな
    void ResetStatus();
    

    ///////////////////アクセス関数/////////////////////////////////////

    /// <summary>
    /// 現在のstateを変える
    /// </summary>
    /// <param name="nextState">次のstate</param>
    void ChangeState(CharacterStateList nextState);


    Status GetStatus() { return status_; }
    XMFLOAT3 GetStartPos() { return startPos_; }
    XMFLOAT3 GetTargetRot() { return targetRot_; }
    void SetStatus(Status status) { status_ = status; }
    void SetStartPos(XMFLOAT3 pos) { startPos_ = pos; }
    void SetColliderRotate(XMFLOAT3 rotate) { pAttackCollision_->SetRotate(rotate); }
    void SetTargetRotate(XMFLOAT3 rot) { targetRot_ = rot; }
    void SetAttackCollider() { AddCollider(pAttackCollision_, ColliderAttackType::COLLIDER_ATTACK); }
    void SetUIPos(XMFLOAT3 pos);

    void SetCharacterName(std::string name);

protected:

    //モデル番号
    int hModel_;

    //HP等のステータス
    Status status_;

    //キャラクタークラスのステート
    CharacterStateManager* pState_;

    //当たり判定
    BoxCollider* pBodyCollision_;
    BoxCollider* pAttackCollision_;

    //それぞれのキャラのスタート地点
    XMFLOAT3 startPos_;

    //前にいた座標
    XMFLOAT3 prevPos_;

    //キャラクターがそれぞれで持つUI
    PlayerUI* pPlayerUI_;



private:

    

    ////////////////////////////////////////////

    bool stopDraw_;

    //攻撃を食らった時に回転するのに使う
    XMFLOAT3 targetRot_;

};