#pragma once
#include "../Engine/GameObject.h"

//チュートリアルシーンを管理するクラス
class TutorialScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TutorialScene(GameObject* parent);

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
	int tutorialImage_;
};