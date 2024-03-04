#include "TitleUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"

//定数宣言
namespace {
	const XMFLOAT3 TEXT_POS = { 500,600,ZERO };

	const XMFLOAT3 IMAGE_POS[NUM] = { { 650,100,ZERO },{ 650, 200, ZERO },{ 650, 300, ZERO } };

	const XMFLOAT3 IMAGE_START_POS[NUM] = { { 1000,100,ZERO },{ -1000, 200, ZERO },{ 650, 3000, ZERO } };

	const float MOVE_RATE = 0.01f;
}

//コンストラクタ
TitleUI::TitleUI(GameObject* parent)
	:GameObject(parent, "TitleUI"), hPict_{-1,-1,-1}, moved_{ false,false,false }, hBackGround_(-1)
{
}

//デストラクタ
TitleUI::~TitleUI()
{
}

//初期化
void TitleUI::Initialize()
{
	std::string str[NUM] = { "Make","&","Fight Party" };

	//画像データのロード
	for (int i = 0; i < NUM; i++) {

		std::string dir = "Image/TitleUI/";
		std::string extention = ".png";

		std::string fileName = dir + str[i] + extention;

		hPict_[i] = Image::Load(fileName);
		assert(hPict_[i] >= 0);
	}

	hBackGround_ = Image::Load("Image/TitleUI/universe.png");
	assert(hBackGround_ >= 0);

	for (int i = 0; i < NUM; i++) {
		titlePos_[i] = XMFLOAT3(SpriteToFloatX(IMAGE_START_POS[i].x), SpriteToFloatY(IMAGE_START_POS[i].y), ZERO);
	}

	pText_ = new Text;
	pText_->Initialize();
}

//更新
void TitleUI::Update()
{

	//MAKEから順番に動かす処理
	for (int i = 0; i < NUM; i++) {
		if (moved_[i] == false) {

			XMFLOAT3 pos = IMAGE_POS[i];
			pos.y = SpriteToFloatY(pos.y);
			pos.x = SpriteToFloatX(pos.x);

			if (RateMovePosition(titlePos_[i], pos, MOVE_RATE)) {
				moved_[i] = true;
			}

			break;
		}
	}
}

//描画
void TitleUI::Draw()
{

	Transform backTrans = transform_;
	transform_.scale_ = XMFLOAT3(1.5f, 1.5f, 1.5f);

	Image::SetTransform(hBackGround_, backTrans);
	Image::Draw(hBackGround_);

	Transform trans;

	trans.position_ = titlePos_[MAKE];
	Image::SetTransform(hPict_[MAKE], trans);
	Image::Draw(hPict_[MAKE]);

	trans.position_ = titlePos_[AND];
	Image::SetTransform(hPict_[AND], trans);
	Image::Draw(hPict_[AND]);

	trans.position_ = titlePos_[FIGHT];
	Image::SetTransform(hPict_[FIGHT], trans);
	Image::Draw(hPict_[FIGHT]);

	if (moved_[FIGHT]) {
		pText_->Draw(TEXT_POS.x, TEXT_POS.y, "Please Space");
	}

	
}

//開放
void TitleUI::Release()
{
}