#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/SceneManager.h"

/// <summary>
/// デベロップ用のシーン
/// </summary>
class DevelopSelectScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	DevelopSelectScene(GameObject* parent);

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

	SCENE_ID scene_;

	int hModel_;

};