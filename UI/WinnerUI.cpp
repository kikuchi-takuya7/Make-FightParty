#include "WinnerUI.h"
#include "../Engine/Image.h"
#include<assert.h>

namespace {
	const XMFLOAT3 WINNER_POS = { 625, 180,ZERO };
	const XMFLOAT3 NUMBER_POS = { 585, 125,ZERO };
}

//コンストラクタ
WinnerUI::WinnerUI(GameObject* parent)
	: GameObject(parent, "WinnerUI"), hPict_{-1,-1,-1,-1}, hWinnerPict_(-1),winnerID_(0)
{
}

//デストラクタ
WinnerUI::~WinnerUI()
{
}

//初期化
void WinnerUI::Initialize()
{
	std::string str[PLAYER_NUM] = { "One","Two","Three", "Four" };

	//画像データのロード
	for (int i = 0; i < PLAYER_NUM; i++) {

		std::string dir = "Image/WinnerUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	hWinnerPict_ = Image::Load("Image/WinnerUI/P-WIN.png");

}

//更新
void WinnerUI::Update()
{

}

//描画
void WinnerUI::Draw()
{
	//SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	if (IsVisibled()) {
		return;
	}

	Transform winnerTrans = transform_;
	winnerTrans.position_.x = SpriteToFloatX(WINNER_POS.x);
	winnerTrans.position_.y = SpriteToFloatY(WINNER_POS.y);

	Image::SetTransform(hWinnerPict_, winnerTrans);
	Image::Draw(hWinnerPict_);

	Transform numberTrans = transform_;
	numberTrans.position_.x = SpriteToFloatX(NUMBER_POS.x);
	numberTrans.position_.y = SpriteToFloatY(NUMBER_POS.y);

	Image::SetTransform(hPict_[winnerID_], numberTrans);
	Image::Draw(hPict_[winnerID_]);

}

//開放
void WinnerUI::Release()
{
}
