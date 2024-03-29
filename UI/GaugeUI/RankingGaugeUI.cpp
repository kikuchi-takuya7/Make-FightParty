#include "RankingGaugeUI.h"
#include "../../Engine/Image.h"
#include "../../Engine/Text.h"
#include "../../Engine/Input.h"
#include "../../Engine/Audio.h"
#include "WinScore.h"
#include "KillScore.h"
#include "TrapKillScore.h"
#include<assert.h>

//定数宣言
namespace {

	const float MIN = ZERO;
	const float MAX = 1.0f;

	const float ONE_GAUGE_LENGTH = 184;

	//スコア毎のゲージの大きさを入れる
	const float SCORE_DIFF[GAUGE_NUM] = { ONE_GAUGE_LENGTH,ONE_GAUGE_LENGTH / 2,ONE_GAUGE_LENGTH / 4 };
	const float START_DIFF[GAUGE_NUM] = { ZERO,ONE_GAUGE_LENGTH / 2,ONE_GAUGE_LENGTH - ONE_GAUGE_LENGTH / 4 };

	//ゲージをすぐMaxにしたいだけで数字に意味はない
	const int TEST_SCORE = 100;

	const XMFLOAT3 GAUGE_SIZE = { 0.72f,0.5f,ZERO };
}


//コンストラクタ
RankingGaugeUI::RankingGaugeUI(GameObject* parent)
	: GaugeBase(parent, "RankingGaugeUI"),hAudio_(-1)
{
}

//デストラクタ
RankingGaugeUI::~RankingGaugeUI()
{
}

//初期化
void RankingGaugeUI::ChildInitialize()
{

	gaugePos_ = transGaugeUI_.position_;

	pText_ = new Text;
	pText_->Initialize();

	hAudio_ = Audio::Load("Audio/SE/Gauge.wav", false, 3);
	assert(hAudio_ >= ZERO);

	Audio::Stop(hAudio_);
}

//更新
void RankingGaugeUI::ChildUpdate()
{

	if (gauge_.empty()) {
		return;
	}

	// 今のスコアゲージのアニメーションが終わったら次入れる予定のゲージを追加する
	if (gauge_.back().first->IsEndAnim() == true && nextScore_.empty() == false) {
		CreateScore(nextScore_.front());
		nextScore_.pop();
	}
}

//描画
void RankingGaugeUI::ChildDraw()
{
	XMFLOAT3 textPos = transform_.position_;
	textPos.x -= 130;
	pText_->Draw(textPos.x, textPos.y, name_.c_str());
}

//開放
void RankingGaugeUI::ChildRelease()
{
}

// 追加するスコアを入れる
// 引数：追加するスコアゲージ
void RankingGaugeUI::PushScore(SCOREGAUGELIST score)
{
	//最初だけ即時に入れる
	if (gauge_.empty()) {
		CreateScore(score);
		return;
	}

	nextScore_.push(score);
}

// 全てのゲージのアニメーションが終わっているかどうか
// 戻り値：全て終わっていたらtrue
bool RankingGaugeUI::IsAllEndAnim()
{
	for (int i = 0; i < gauge_.size(); i++) {
		if (gauge_.at(i).first->IsEndAnim() == false) {
			return false;
		}
	}

	if (nextScore_.empty() == false)
		return false;

	return true;
}

// ゲージのアニメーションを即座に終わらせる（一ゲージ分だけ）
void RankingGaugeUI::AllEndAnim()
{
	for (int i = ZERO; i < gauge_.size(); i++) {
		gauge_.at(i).first->EndAnim();
	}
}

// 表示するスコアのインスタンスを作る
// 引数：インスタンスを作るスコアゲージ
void RankingGaugeUI::CreateScore(SCOREGAUGELIST score)
{
	//最初のゲージだけ画像の隙間分を埋める
	if (gauge_.empty())
		gaugePos_.x -= START_DIFF[score];
	else
		gaugePos_.x += SCORE_DIFF[score];

	switch (score)
	{
	case WIN_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<WinScore>(this), score));
		break;

	case KILL_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<KillScore>(this), score));
		break;

	case TRAP_KILL_GAUGE:
		gauge_.emplace_back(std::make_pair(Instantiate<TrapKillScore>(this), score));
		break;

	default:
		return;
	}

	gauge_.back().first->SetGauge(TEST_SCORE, TEST_SCORE);
	gauge_.back().first->Enter();
	gauge_.back().first->SetScale(GAUGE_SIZE);
	gauge_.back().first->SetPosition(SpriteToFloatX(transform_.position_.x + gaugePos_.x), SpriteToFloatY(transform_.position_.y), ZERO);

	Audio::Play(hAudio_);
}
