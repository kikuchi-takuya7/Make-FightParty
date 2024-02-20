#include "RankingUI.h"
#include "../Engine/Image.h"
#include<assert.h>

//�R���X�g���N�^
RankingUI::RankingUI(GameObject* parent)
	: GameObject(parent, "RankingUI")
{
}

//�f�X�g���N�^
RankingUI::~RankingUI()
{
}

//������
void RankingUI::Initialize()
{
	hPict_ = Image::Load("Image/RankingUI/RankingPaper.png");

}

//�X�V
void RankingUI::Update()
{
	
}

//�`��
void RankingUI::Draw()
{
	SetScale(XMFLOAT3(0.8f,0.6f,1));

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	


}

//�J��
void RankingUI::Release()
{
}
