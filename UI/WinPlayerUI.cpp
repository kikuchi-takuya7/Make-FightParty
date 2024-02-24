#include "WinPlayerUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//�R���X�g���N�^
WinPlayerUI::WinPlayerUI(GameObject* parent)
	: GameObject(parent, "WinPlayerUI")
{
}

//�f�X�g���N�^
WinPlayerUI::~WinPlayerUI()
{
}

//������
void WinPlayerUI::Initialize()
{
	hPict_ = Image::Load("Image/RankingUI/RankingPaper.png");

}

//�X�V
void WinPlayerUI::Update()
{

}

//�`��
void WinPlayerUI::Draw()
{
	SetScale(XMFLOAT3(0.8f, 0.6f, 1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);



}

//�J��
void WinPlayerUI::Release()
{
}
