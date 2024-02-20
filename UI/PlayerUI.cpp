#include "PlayerUI.h"
#include "HpGaugeUI.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include "../Engine/Input.h"

namespace {
	const float TEXT_SIZE = 0.65f;
	const XMFLOAT3 GAUGE_SIZE = XMFLOAT3(0.7f, 0.2f, 1);
	const XMFLOAT3 PLAYERUI_SIZE = XMFLOAT3(0.7f, 0.5f, 1);

	const float GAUGE_DIFF = 80;
	const float TEXT_DIFF_Y = 40;
	const float TEXT_DIFF_X = 85;
}

//コンストラクタ
PlayerUI::PlayerUI(GameObject* parent)
	:GameObject(parent, "PlayerUI"),pHpGauge_(nullptr)
{
}

//デストラクタ
PlayerUI::~PlayerUI()
{
}

//初期化
void PlayerUI::Initialize()
{

	hPict_ = Image::Load("Image/PlayerUI/PlayerUI2.png");

	playerUITrans_.scale_ = PLAYERUI_SIZE;

	pHpGauge_ = Instantiate<HpGaugeUI>(this);
	pHpGauge_ ->SetScale(GAUGE_SIZE);
	//pHpGauge_ ->SetGauge(100, 100);

	pText_ = new Text;
	pText_->Initialize();

	pText_->SetScale(TEXT_SIZE);

	playerName_ = "NONE";
}

//更新
void PlayerUI::Update()
{

	if (Input::IsKeyDown(DIK_L)) {
		pHpGauge_ ->AddValue(-10);
	}

}

//描画
void PlayerUI::Draw()
{

	if (IsVisibled()) {
		return;
	}

	Transform imageTrans_;
	imageTrans_.position_.x = SpriteToFloatX(playerUITrans_.position_.x);
	imageTrans_.position_.y = SpriteToFloatY(playerUITrans_.position_.y);

	imageTrans_.scale_ = playerUITrans_.scale_;

	Image::SetTransform(hPict_, imageTrans_);
	Image::Draw(hPict_);

	

	pText_->Draw(playerUITrans_.position_.x - TEXT_DIFF_X, playerUITrans_.position_.y - TEXT_DIFF_Y, playerName_.c_str());
}

//開放
void PlayerUI::Release()
{
}

void PlayerUI::SetMaxHp(int nowHp, int maxHp)
{
	pHpGauge_->SetGauge(nowHp, maxHp);
}

void PlayerUI::SetNowHp(int nowHp)
{
	pHpGauge_->SetNowGauge(nowHp);
}

void PlayerUI::SetPlayerUIPos(XMFLOAT3 pos)
{
	playerUITrans_.position_ = pos;
	pHpGauge_->SetPosition(SpriteToFloatX(playerUITrans_.position_.x - GAUGE_DIFF), SpriteToFloatY(playerUITrans_.position_.y), ZERO);
}

void PlayerUI::StopDraw()
{
	Visible();
	pHpGauge_->Visible();
}

void PlayerUI::StartDraw()
{
	Invisible();
	pHpGauge_->Invisible();
}
