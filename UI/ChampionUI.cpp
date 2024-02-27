#include "ChampionUI.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {
	const XMFLOAT3 UI_POS = { 650, 300,ZERO };
}

//コンストラクタ
ChampionUI::ChampionUI(GameObject* parent)
	: GameObject(parent, "ChampionUI"), hPict_(-1)
{
}

//デストラクタ
ChampionUI::~ChampionUI()
{
}

//初期化
void ChampionUI::Initialize()
{

	hPict_ = Image::Load("Image/WinnerUI/Champion.png");
	assert(hPict_ >= 0);
}

//更新
void ChampionUI::Update()
{

}

//描画
void ChampionUI::Draw()
{
	//SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	if (IsVisibled()) {
		return;
	}

	Transform winnerTrans = transform_;
	winnerTrans.position_.x = SpriteToFloatX(UI_POS.x);
	winnerTrans.position_.y = SpriteToFloatY(UI_POS.y);

	Image::SetTransform(hPict_, winnerTrans);
	Image::Draw(hPict_);


}

//開放
void ChampionUI::Release()
{
}
