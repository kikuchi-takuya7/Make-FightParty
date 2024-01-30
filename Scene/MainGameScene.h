#pragma once
#include "../Engine/GameObject.h"

class MetaAI;
class NavigationAI;
class Status;//構造体だけどこれいいの？？？？

//■■シーンを管理するクラス
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


	void CallStatus(int ID, Status status);

private:

	//
	NavigationAI* pNavigationAI_;

	//ゲーム全体のバランスを管理するAI
	MetaAI* pMetaAI_;

	/*Player* pPlayer_;

	Enemy* pEnemy_;*/
	
};