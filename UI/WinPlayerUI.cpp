#include "WinPlayerUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//コンストラクタ
WinPlayerUI::WinPlayerUI(GameObject* parent)
	: GameObject(parent, "WinPlayerUI")
{
}

//デストラクタ
WinPlayerUI::~WinPlayerUI()
{
}

//初期化
void WinPlayerUI::Initialize()
{
	hPict_ = Image::Load("Image/RankingUI/RankingPaper.png");

}

//更新
void WinPlayerUI::Update()
{

}

//描画
void WinPlayerUI::Draw()
{
	SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);



}

//開放
void WinPlayerUI::Release()
{
}
