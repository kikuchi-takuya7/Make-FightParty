#pragma once
#include "AI.h"

class NavigationAI;
class MetaAI;
class Enemy;
class Text;
enum TARGETPATTERN;

enum TARGETPATTERNTEXT {
	RANDAM,
	NO_1,
	COUNTER,
	TEXT_NUM,
};

//狙っている敵IDとモード
struct TargetInfo {

	//狙っている敵のID
	int ID;

	//そのIDを狙うのに使った確率のパターン（現在の状態を描画するのに使う）
	TARGETPATTERNTEXT mode;
};

/// <summary>
/// 敵キャラクターを動かすAI
/// </summary>
class CharacterAI : public AI
{

public:

	//コンストラクタ
	CharacterAI(GameObject* parent);
	CharacterAI(GameObject* parent,Enemy* enemy, NavigationAI* naviAI);

	//デストラクタ
	~CharacterAI();

	//////////////オーバーライドした関数////////////////

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//解放
	void Release() override;

	/////////////////メンバ関数/////////////////////////

	/// <summary>
	/// 狙うべき敵をMetaAIに聞く関数
	/// </summary>
	void AskTarget();

	/// <summary>
	/// MetaAIに情報を伝える関数
	/// </summary>
	void TellStatus();

	/// <summary>
	/// NavigationAIに行くべき場所を聞き、移動する関数
	/// </summary>
	void MoveEnemy();

	/// <summary>
	/// 攻撃するかどうかを指示する関数
	/// </summary>
	void IsAttack();

	/// <summary>
	/// クリエイトモードで選択したオブジェクトを移動させる関数
	/// </summary>
	/// <returns>動かした後のTransform</returns>
	Transform MoveSelectObject();

	///////////////////アクセス関数///////////////////

	void SetEnemy(Enemy* enemy) { pEnemy_ = enemy; }
	void SetNavigationAI(NavigationAI* AI) { pNavigationAI_ = AI; }
	void SetMetaAI(MetaAI* AI) { pMetaAI_ = AI; }

	void SetTarget(TargetInfo target) { target_ = target; }

private:

	NavigationAI* pNavigationAI_;

	MetaAI* pMetaAI_;

	//自分が操る敵のインスタンス
	Enemy* pEnemy_;

	TargetInfo target_;

	//現在の状態を表示する用のテキスト
	Text* pText_;
	
};

