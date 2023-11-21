#include "IKEditorScene.h"
#include "../Player/PlayerFoot.h"
#include "../Player/PlayerHand.h"

//コンストラクタ
IKEditorScene::IKEditorScene(GameObject* parent)
	: GameObject(parent, "IKEditorScene")
{
}

//初期化
void IKEditorScene::Initialize()
{
	Instantiate<PlayerFoot>(this);
	Instantiate<PlayerHand>(this);
}

//更新
void IKEditorScene::Update()
{
}

//描画
void IKEditorScene::Draw()
{
}

//開放
void IKEditorScene::Release()
{
}
