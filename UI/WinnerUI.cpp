#include "WinnerUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//コンストラクタ
WinnerUI::WinnerUI(GameObject* parent)
	: GameObject(parent, "WinnerUI"), hPict_{-1,-1,-1,-1}, hWinnerPict_(-1)
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

	Image::SetTransform(hWinnerPict_, transform_);
	Image::Draw(hWinnerPict_);

	Image::SetTransform(hPict_[winnerID_], transform_);
	Image::Draw(hPict_[winnerID_]);

}

//開放
void WinnerUI::Release()
{
}
