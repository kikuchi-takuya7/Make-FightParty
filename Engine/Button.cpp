#include "Button.h"
#include "Image.h"
#include "Direct3D.h"
#include "SceneManager.h"
#include "Input.h"

namespace {
	float startX; // 移動開始X座標
	float endX;   // 移動終了X座標
	float totalTime; // 移動時間（秒）
	float currentTime; // 現在の時間

	int seq_line; // 今実行している行
	float seq_time; // シーケンスを実行している時間
	enum ACT { // やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct Sequence {
		float time; // 時間
		ACT action; // やること
		float param; // 必要な値
	};
	Sequence tbl[] = {

		{ 0.0f, A_SLIDEIN, 5.0f }, // まずはスライドイン
		{ 3.0f, A_WAIT, 0.0f/*意味なし*/}, // 1秒待ってから
		{ 4.0f, A_SLIDEOUT, -5.0f }, // スライドアウト
		{ 5.0f, A_END, 0.0f} // ここで消える
	};
	ACT currentAction; // 今実行しているアクション
	bool canMove; // 移動できる
};

Button::Button(GameObject* parent)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
	alpha_ = 255;
	changeLimit_ = 0;
	tmpLimit_ = 0;
	alphaFlag_ = false;
	startFlag_ = false;
	nextScene_ = NONE;
	isFlash_ = false;
}

Button::~Button()
{
}

void Button::Initialize()
{
	pushed_ = false;
	hImage_ = -1;
	hPush_ = -1;
	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.0f;
	
}

void Button::Update()
{
	
	//点滅を管理
	//isFlashがtrueなら待機状態で点滅するように
	if (isFlash_) {
		if (!startFlag_) {//クリックされたらelseになる
			ChangeAlpha();
		}
		else {
			ChangeScene();
		}
	}
	

	if (pushed_) {

		if(!startFlag_)
			alpha_ = 255;

		if (Input::IsMouseButtonDown(0)) {
			startFlag_ = true;
			alphaFlag_ = false;
			isFlash_ = true;
		}
	}

	Image::SetAlpha(hImage_,alpha_);
}

void Button::Draw()
{

	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
	
}

bool Button::Finished()
{
	return canMove;
}

void Button::SetImage(std::string normal)
{
	hImage_ = Image::Load((normal + ".png").c_str());
	size_ = Image::GetSize(hImage_);
}

void Button::SetImage(std::string normal, std::string pushed)
{
	hImage_ = Image::Load((normal+".png").c_str());
	hPush_ = Image::Load((pushed+".png").c_str());
	size_ = Image::GetSize(hImage_);
}

void Button::SetPosition(int x, int y)
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(float)(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ /2);
	center_ = XMFLOAT3(x, y, 0);
}

void Button::Push(bool pushed)
{
	this->pushed_ = pushed;
}

bool Button::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center_.x) > size_.x/2)
		return false;
	if (abs(mousePos.y - center_.y) > size_.y/2)
		return false;
	return true;
}

void Button::SetAlphaNormal(float alpha)
{
	Image::SetAlpha(hImage_, alpha);
}

void Button::SetAlphaPush(float alpha)
{
	Image::SetAlpha(hPush_, alpha);
}

void Button::SetNextScene(NEXTSCENE next)
{
	nextScene_ = next;
}

void Button::SetIsFlash(bool flash)
{
	isFlash_ = flash;
}

void Button::ChangeAlpha()
{
	if (!alphaFlag_) {
		alpha_ += 3;
	}
	else {
		alpha_ -= 3;
	}

	if (alpha_ >= 255)
		alphaFlag_ = true;

	if (alpha_ <= 0)
		alphaFlag_ = false;
}

void Button::ChangeScene()
{
	changeLimit_++;

	if (changeLimit_ % 30 == 1) {
		alphaFlag_ = false;
	}

	if (tmpLimit_ > 15)
		alphaFlag_ = true;

	if (alphaFlag_) {
		alpha_ = 255;
		tmpLimit_ = 0;
	}
	else {
		alpha_ = 0;
		tmpLimit_++;
	}

	if (changeLimit_ > 60) {
		switch (nextScene_)
		{
		case NONE:
			break;
		case SELECT: {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_SELECT);
		}
			break;
		default:
			break;
		}
	}
}
