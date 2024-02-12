#include "CountDown.h"
#include "../Engine/Timer.h"
#include "../Engine/Image.h"

//コンストラクタ
CountDown::CountDown(GameObject* parent)
    :GameObject(parent, "CountDown")
{
}

//デストラクタ
CountDown::~CountDown()
{
}

//初期化
void CountDown::Initialize()
{
	std::string str[COUNT_NUM] = { "Count-GO","Count-1","Count-2","Count-3" };


	//画像データのロード
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/CountDown";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	transform_.position_ = XMFLOAT3(ZERO, 0.5f, ZERO);

}

//更新
void CountDown::Update()
{
}

//描画
void CountDown::Draw()
{
}

//開放
void CountDown::Release()
{
}