#pragma once
#include "../../Engine/GameObject.h"
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
    /// 敵から攻撃を食らった時に呼び出される、一定確率でターゲットを変える関数
    /// </summary>
    void ChangeTarget(GameObject* pTarget) override;

    /////////////////////メンバ関数/////////////////////////////////////

    /// <summary>
    /// CharavterAIに移動する場所を聞いて移動する関数
    /// </summary>
    void MoveCharacter() override;

    /// <summary>
    /// メタAIに現在のステータスを伝える関数
    /// </summary>
    void TellStatus() override;

    ///////////////////アクセス関数/////////////////////////////////////
    void SetCharacterAI(CharacterAI* AI) { pCharacterAI_ = AI; }

private:

    //キャラクターAIのインスタンス
    CharacterAI* pCharacterAI_;

};