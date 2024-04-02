#pragma once
#include "../Engine/GameObject.h"

class MetaAI;
class NavigationAI;
class Stage;
class CreateMode;
class Enemy;
struct Status;



/// <summary>
/// ゲームのメインとなるシーン
/// </summary>
class MainGameScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MainGameScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:

	//クリエイトモードに色々セットしたりする関数
	void CreateModeInit();

	//キャラクターAIを作る
	void CreateCharaAI(Enemy* enemy, int attackRange);

	//背景
	int hPict_;

	//このクラス内では使わないけど一応インスタンスを保持しておく

	//ゲーム全体の位置等を管理するAI
	NavigationAI* pNavigationAI_;
	
	//ゲーム全体のバランスを管理するAI
	MetaAI* pMetaAI_;

	//ステージ
	Stage* pStage_;

	//クリエイトモード時に使うクラス
	CreateMode* pCreateMode_;

	
	//インスタンスを作成して色々するテンプレート
	template <class T>
	T* CreateCharacter(int ID, std::string name);

};

