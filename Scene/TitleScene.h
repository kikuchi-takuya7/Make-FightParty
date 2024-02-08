#pragma once
#include "../Engine/GameObject.h"

enum IMAGE {

	MAKE,
	AND,
	FIGHT,
	NUM
};

class Button;
class Text;

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void Imgui_Window() override;

private:

	int hPict_[3];

	Text* pText_;

	Transform make_Trans_;
	Transform and_Trans_;
	Transform fight_Trans_;

};