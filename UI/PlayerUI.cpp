#include "PlayerUI.h"
#include "Gauge.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include "../Engine/Input.h"

//コンストラクタ
PlayerUI::PlayerUI(GameObject* parent)
	:GameObject(parent, "PlayerUI"),pGauge_(nullptr)
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

	playerUITrans_.position_ = XMFLOAT3(-0.7, -0.8, 0);
	playerUITrans_.scale_ = XMFLOAT3(0.7, 0.5, 1);

	pGauge_ = Instantiate<Gauge>(this);
	pGauge_->SetPosition(XMFLOAT3(-0.7, -0.8, 0));

	pGauge_->SetGauge(100, 100);

	pText_ = new Text;
	pText_->Initialize();
}

//更新
void PlayerUI::Update()
{

	if (Input::IsKey(DIK_L)) {
		pGauge_->AddValue(-1);
	}

}

//描画
void PlayerUI::Draw()
{
	Image::SetTransform(hPict_, playerUITrans_);
	Image::Draw(hPict_);

	float textX = Direct3D::screenWidth_ / 2;
	float textY = Direct3D::screenHeight_ / 2 + 200;

	pText_->Draw(500, 600, "Player1");
}

//開放
void PlayerUI::Release()
{
}

void PlayerUI::SetNowHp(int nowHp)
{
	pGauge_->SetNowGauge(nowHp);
}
