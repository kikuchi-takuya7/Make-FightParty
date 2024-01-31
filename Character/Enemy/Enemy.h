#pragma once
#include "../../Engine/GameObject.h"
#include "EnemyState/EnemyStateManager.h"
#include "EnemyState/EnemyState.h"
#include "../Character.h"

class EnemyStateManager;
class NavigationAI;
class CharacterAI;



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

    /// <summary>
    /// CharavterAIに移動する場所を聞いて移動する
    /// </summary>
    void MoveCharacter() override;

    /////////////////////AIに伝える関数/////////////////////////////



    ///////////////////アクセス関数/////////////////////////////////////
    void SetCharacterAI(CharacterAI* AI) { pCharacterAI_ = AI; }

    void ChangeState(EnemyStatePattern nextState);
    
    //セッターの中でセッターは呼べなかったから普通にgameSceneで用意しちゃう
    //void SetNavi(NavigationAI* naviAI) { pCharacterAI_->SetNavigationAI(naviAI); }


private:

    int hModel_;

    //HP等のステータス
    //Status status_;

    EnemyStateManager* pState_; //敵の状態を表す

    CharacterAI* pCharacterAI_;//色んな判断をしてくれるAIのつもり

    //当たり判定
    //BoxCollider* pBodyCollision_;

};