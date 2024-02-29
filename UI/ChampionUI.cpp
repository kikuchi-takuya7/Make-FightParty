#include "ChampionUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include "../Engine/Timer.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include<assert.h>

namespace {
	const XMFLOAT3 UI_POS = { 650, 300,ZERO };
	const XMFLOAT3 TEXT_POS = { 500,600,ZERO };
	const float WAIT_TIME = 5.0f;
}

//コンストラクタ
ChampionUI::ChampionUI(GameObject* parent)
	: GameObject(parent, "ChampionUI"), hPict_(-1),pTimer_(Instantiate<Timer>(this)),pText_(new Text)
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

	pText_->Initialize();

	pTimer_->SetLimit(WAIT_TIME);
	pTimer_->StopDraw();
	pTimer_->Stop();

}

//更新
void ChampionUI::Update()
{

	if (IsEntered()) {
		return;
	}

	pTimer_->Start();

	
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

	if (pTimer_->IsFinished()) {
		pText_->Draw(TEXT_POS.x, TEXT_POS.y, "PleaseSpace");
	}


}

//開放
void ChampionUI::Release()
{
}

bool ChampionUI::IsEnd()
{
	return pTimer_->IsFinished();
}
