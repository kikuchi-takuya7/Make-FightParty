#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// 攻撃力や試合中のkillポイント等を覚えるステータス
/// </summary>
struct Status {

    //試合に関係するステータス
    int hp;                 //HP
    int attackPower;        //敵を殴った時に与えるダメージ
    float moveSpeed;        //そのキャラの移動速度
    bool dead;              //死んでいるかどうか。死んでたらtrue

    //スコアに関係するステータス
    int winPoint;           //勝った合計数
    int killPoint;          //試合中に倒した敵の数
    int trapKillPoint;      //トラップで倒した
    std::string playerName; //プレイヤーの名前

    //デフォルトコンストラクタ
    Status() {
        hp = ZERO;
        attackPower = ZERO;
        moveSpeed = ZERO;
        dead = false;
        winPoint = ZERO;
        killPoint = ZERO;
        trapKillPoint = ZERO;
        playerName = "noname";
    }

    //引数付きコンストラクタ
    Status(int h, int p, float s, bool d, int win, int kill, int obj, std::string n) {
        hp = h;
        attackPower = p;
        moveSpeed = s;
        dead = d;
        winPoint = win;
        killPoint = kill;
        trapKillPoint = obj;
        playerName = n;
    }

};

enum SoundEffect {
    HIT,
    DEAD,
    SE_NUM
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

    //////////////////子供に継承させる関数//////////////////////////////

    /// <summary>
    /// 継承先用の初期化関数
    /// </summary>
    virtual void ChildInitialize() {};

    /// <summary>
    /// 継承先用のUpdate関数
    /// </summary>
    virtual void ChildUpdate() {};

    /// <summary>
    /// 継承先用の描画関数
    /// </summary>
    virtual void ChildDraw() {};

    /// <summary>
    /// 継承先用の開放関数
    /// </summary>
    virtual void ChildRelease() {};

    /// <summary>
    /// キャラクター毎の移動処理（敵ならAI、人なら操作）
    /// </summary>
    virtual void MoveCharacter() {};

    /// <summary>
    /// Enemyが攻撃を食らった時に一定確率で狙いを変える用の関数
    /// </summary>
    virtual void ChangeTarget(GameObject* pTarget) {};

    /// <summary>
    /// メタAIに情報を教える関数
    /// </summary>
    virtual void TellStatus() {};

    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// 攻撃に当たった時にHPを減らす関数
    /// </summary>
    /// <param name="damage">食らったダメージ量</param>
    /// <returns>そのダメージで死亡したらtrue</returns>
    bool HitDamage(int damage);

    /// <summary>
    /// ステータスをゲーム開始時にリセットする関数（winPointはそのまま）
    /// </summary>
    void ResetStatus();

    //////////////////////////////////プレイヤーUIとまとめて状態を変える関数/////////////////

    void StopDraw();    //描画を止める
    void StartDraw();   //描画を許可する
    void StopDrawUI();  //UIの描画を止める
    void Dead();        //ステータスのdeadをtrueにする（未使用）

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

    //攻撃を食らった時のエフェクト
    void HitEffect();

    //死んだ時にでるエフェクト
    void DieEffect();

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

    //効果音
    int hSoundEffect_[SE_NUM];
    

private:

    //攻撃を食らった時に回転するのに使う
    XMFLOAT3 targetRot_;

};