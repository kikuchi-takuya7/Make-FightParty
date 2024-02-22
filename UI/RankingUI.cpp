#include "RankingUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//コンストラクタ
RankingUI::RankingUI(GameObject* parent)
	: GameObject(parent, "RankingUI")
{
}

//デストラクタ
RankingUI::~RankingUI()
{
}

//初期化
void RankingUI::Initialize()
{
	hPict_ = Image::Load("Image/RankingUI/RankingPaper.png");

}

//更新
void RankingUI::Update()
{
	
}

//描画
void RankingUI::Draw()
{
	SetScale(XMFLOAT3(0.8f,0.6f,1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	


}

//開放
void RankingUI::Release()
{
}
