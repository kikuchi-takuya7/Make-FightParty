#include "PlayerUI.h"
#include "Gauge.h"
#include "../Engine/Image.h"
#include "../Engine/Text.h"
#include "../Engine/Input.h"

//�R���X�g���N�^
PlayerUI::PlayerUI(GameObject* parent)
	:GameObject(parent, "PlayerUI"),pGauge_(nullptr)
{
}

//�f�X�g���N�^
PlayerUI::~PlayerUI()
{
}

//������
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

//�X�V
void PlayerUI::Update()
{

	if (Input::IsKey(DIK_L)) {
		pGauge_->AddValue(-1);
	}

}

//�`��
void PlayerUI::Draw()
{
	Image::SetTransform(hPict_, playerUITrans_);
	Image::Draw(hPict_);

	float textX = Direct3D::screenWidth_ / 2;
	float textY = Direct3D::screenHeight_ / 2 + 200;

	pText_->Draw(500, 600, "Player1");
}

//�J��
void PlayerUI::Release()
{
}

void PlayerUI::SetNowHp(int nowHp)
{
	pGauge_->SetNowGauge(nowHp);
}
