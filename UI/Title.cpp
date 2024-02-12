#include "Title.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"

//コンストラクタ
Title::Title(GameObject* parent)
    :GameObject(parent, "Title")
{
}

//デストラクタ
Title::~Title()
{
}

//初期化
void Title::Initialize()
{
	std::string str[NUM] = { "Make","&","Fight Party" };


	//画像データのロード
	for (int i = 0; i < ARRAYSIZE(hPict_); i++) {

		std::string dir = "Image/Title/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	make_Trans_.position_ = XMFLOAT3(0, 0.7, 0);
	and_Trans_.position_ = XMFLOAT3(0, 0.5, 0);
	fight_Trans_.position_ = XMFLOAT3(0, 0.3, 0);

	pText_ = new Text;
	pText_->Initialize();
}

//更新
void Title::Update()
{
}

//描画
void Title::Draw()
{
	Image::SetTransform(hPict_[MAKE], make_Trans_);
	Image::Draw(hPict_[MAKE]);

	Image::SetTransform(hPict_[AND], and_Trans_);
	Image::Draw(hPict_[AND]);

	Image::SetTransform(hPict_[FIGHT], fight_Trans_);
	Image::Draw(hPict_[FIGHT]);

	float textX = Direct3D::screenWidth_ / 2;
	float textY = Direct3D::screenHeight_ / 2 + 200;

	pText_->Draw(500, 600, "PleaseSpace");
}

//開放
void Title::Release()
{
}