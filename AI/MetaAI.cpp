#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Timer.h"
#include "../UI/CountDownUI.h"
#include "../UI/RankingUI.h"
#include "../UI/GaugeUI/RankingGaugeUI.h"
#include "../UI/WinnerUI.h"
#include "../UI/ChampionUI.h"
#include "../Stage/CreateMode/CreateMode.h"

namespace {

	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -20);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 CHAMPION_CAM_POS_DIFF = { ZERO,4,-5 };
	const XMFLOAT3 CHAMPION_CAM_TAR_DIFF = { ZERO,2,ZERO };
	const float CHAMPION_CAM_RATE = 0.05f;

	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;

	const float WAIT_WINNER_TIME = 1.0f;
	const float WAIT_CHAMPION_TIME = 1.0f;

	const int SCORE[GAUGE_NUM] = { 20,10,5 };
	const int VICTORY_POINT = 80;
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this)),
	pWinnerUI_(Instantiate<WinnerUI>(this)),pChampionUI_(Instantiate<ChampionUI>(this))
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
	//色々初期化
	for (int i = ZERO; i < 4; i++) {
		No1CharaID_.emplace_back(i);
	}
	for (int i = ZERO; i < 4; i++) {
		ranking_.emplace_back(i);
	}
	for (int i = ZERO; i < 4; i++) {
		score_.emplace_back(ZERO);
	}

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();

	pWinnerUI_->Visible();
	pChampionUI_->Visible();
}

void MetaAI::Update()
{
	//優勝者が決まったら試合を止める
	if (endGame_) {

		//一定時間待ったら優勝者にカメラを向ける
		if (pWaitTimer_->IsFinished()) {
			pChampionUI_->Invisible();
			pRankingUI_->AllChildVisible();
			pRankingUI_->AllChildLeave();
			MoveChampionCam();
		}

		return;
	}

	//優勝者が決まってる場合は上で、決まってないならこっちでタイマーを使う。
	if (pWaitTimer_->IsFinished()) {
		pNavigationAI_->AllStopDrawPlayerUI();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		pWinnerUI_->Visible();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);

		if (Input::IsKeyDown(DIK_2)) {
			pRankingUI_->SetScore(ZERO, WIN_GAUGE,1);
			score_.at(ZERO) += SCORE[WIN_GAUGE];
		}
		if (Input::IsKeyDown(DIK_3)) {
			pRankingUI_->SetScore(1, KILL_GAUGE,1);
			score_.at(1) += SCORE[KILL_GAUGE];
		}
		if (Input::IsKeyDown(DIK_4)) {
			pRankingUI_->SetScore(2, TRAP_KILL_GAUGE, 1);
			score_.at(2) += SCORE[TRAP_KILL_GAUGE];
		}
		
		if (Input::IsKeyDown(DIK_SPACE)) {

			if (pRankingUI_->IsAllEndAnim() == false) {
				pRankingUI_->EndAnim();
				return;
			}

			pWaitTimer_->Reset();
			

			//優勝者が決まってらリザルトシーンに
			int ID = VictoryPlayer();
			if (ID != -1) {
				endGame_ = true;
				pNavigationAI_->AllEraseCollision();
				pWaitTimer_->Start();
				return;
			}

			pCreateMode_->ToSelectMode();
			pNavigationAI_->AllStopDraw();
			pRankingUI_->AllChildVisible();
			pRankingUI_->AllChildLeave();

		}
	}

	//カウントダウンが終わったら動く許可を出す
	if (pCountDown_->IsFinished()) {
		pNavigationAI_->AllStartUpdate();
		pCountDown_->Reset();
	}

	//デバック用
	if (Input::IsKeyDown(DIK_1) && pCreateMode_->GetState() == NONE) {

		characterStatusList_.at(ZERO).winPoint++;
		pNavigationAI_->SetStatus(ZERO, characterStatusList_.at(ZERO));
		CheckNo1Chara();

		if (characterStatusList_.at(ZERO).winPoint >= 4) {
			endGame_ = true;
		}
		pCreateMode_->ToSelectMode();
	}
}

void MetaAI::Release()
{
}

//狙うべき相手を決める関数
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % TARGET_NUM;

	TARGETPATTERN target = (TARGETPATTERN)targetFrag;

	bool No1AllDead = true;

	//１位が誰かしら生き残っているかどうか
	for (int i = ZERO; i < No1CharaID_.size(); i++) {
		if (characterStatusList_.at(No1CharaID_.at(i)).dead == false) {
			No1AllDead = false;
			break;
		}
	}

	//自分が1位だった場合0に固定する（同率でも）or 一位が全員死んでても0に固定
	if (score_.at(ranking_.at(ZERO)) == score_.at(ID) || No1AllDead == true) {

		target = TARGET_RANDAM;
	}

	//全体を見て一位のプレイヤーを優先的に狙うように
	switch (target)
	{
	//キャラクターの中からランダムで狙う	
	case TARGET_RANDAM:
		while (true)
		{
			int targetID = rand() % characterStatusList_.size();

			//狙った相手が自分じゃなく、死んでいなければ
			if (targetID != ID)
				return targetID;
		}
		break;
	
	//一位の中から誰かを狙う
	case TARGET_NO_1:
		while (true)
		{
			//狙った相手が自分じゃなければ
			int targetID = rand() % No1CharaID_.size();
			if (targetID != ID)
				return targetID;
		}
		break;

	case TARGET_NUM:
	default:
		break;
	}

	return 0;

}

void MetaAI::CheckNo1Chara()
{

	No1CharaID_.clear();

	//一位のポイントとそれと同じ点数が何人いるか
	int No1Score = ZERO;
	
	vector<pair<int,int>> ranking;

	//ソートする用の配列に入れる
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//キャラのスコアとIDを入れる（リストに入ってる順番がそのままIDになってる）
		ranking.emplace_back(std::make_pair(score_.at(i),i));
	}

	//降順でソートする
	std::sort(ranking.rbegin(), ranking.rend());

	//一位のポイントとIDを覚えておく
	No1Score = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	
	//ついでにメンバ変数のランキングも更新する
	ranking_.at(ZERO) = ranking.at(ZERO).second;

	for (int i = 1; i < ranking.size(); i++) {

		//一位の人と同じポイントなら同率１位を入れる
		if (No1Score == score_.at(i)) {

			No1CharaID_.emplace_back(ranking.at(i).second);
			ranking_.at(i) = ranking.at(i).second;
		}
		else {
			
			//2位以下を更新
			ranking_.at(i) = ranking.at(i).second;
		}
	}

	
}

void MetaAI::ToCreateMode()
{

	int deadNum = 0;
	
	int winPlayer = 0;

	//死んでる人数を数える
	for (int i = 0; i < characterStatusList_.size(); i++) {
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
		else {
			//勝ったやつのプレイヤーIDを覚えておく
			winPlayer = i;
		}
	}

	//相打ちだった場合
	if (deadNum == 4) {

	}

	//3人以上死んでいたら勝ったプレイヤーのwinPointを増やして、現在の順位を確認する
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		
		characterStatusList_.at(winPlayer).winPoint++;

		//キャラクタークラスにも教える
		pNavigationAI_->SetStatus(winPlayer, characterStatusList_.at(winPlayer));


		//スコアを確認する
		pRankingUI_->SetScore(winPlayer, WIN_GAUGE,1);
		score_.at(winPlayer) += SCORE[WIN_GAUGE];

		//キル数分もスコアに加算する
		for (int i = 0; i < characterStatusList_.size(); i++) {

			pRankingUI_->SetScore(i, KILL_GAUGE, characterStatusList_.at(i).killPoint);
			score_.at(i) += SCORE[KILL_GAUGE] * characterStatusList_.at(i).killPoint;
			
			pRankingUI_->SetScore(i, TRAP_KILL_GAUGE, characterStatusList_.at(i).trapKillPoint);
			score_.at(i) += SCORE[TRAP_KILL_GAUGE] * characterStatusList_.at(i).trapKillPoint;
		}

		//現状の一位が誰か確認する
		CheckNo1Chara();

		pRankingUI_->AllChildLeave();
		pNavigationAI_->AllStopUpdate();
		
		pWinnerUI_->SetWinnerID(winPlayer);
		pWinnerUI_->Invisible();

		pWaitTimer_->Start();
	}
}

void MetaAI::StartGame()
{
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();

	pCountDown_->Start();
	GameCameraSet();
}

void MetaAI::ResetGame()
{
	//もろもろ初期化して、カウントダウンが終わるまで動かさない。
	pNavigationAI_->AllEraseCollision();
	pNavigationAI_->AllResetStatus();
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();
	
	pCountDown_->Start();
	GameCameraSet();

}

void MetaAI::GameCameraSet()
{
	Camera::SetPosition(MAIN_GAME_CAM_POS);
	Camera::SetTarget(MAIN_GAME_CAM_TAR);
}

int MetaAI::SelectObject(vector<int> model)
{

	//今はとりあえずランダムで返す
	return model.at(rand() % model.size());


}

void MetaAI::PushCharacterStatus(Status status)
{
	characterStatusList_.emplace_back(status);
	pRankingUI_->SetPlayerName(characterStatusList_.size() - 1, status.playerName);
}

void MetaAI::MoveChampionCam()
{
	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 charaPos = pChampion->GetPosition();
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_POS_DIFF.y, charaPos.z + CHAMPION_CAM_POS_DIFF.z);
	XMFLOAT3 camTar = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_TAR_DIFF.y, charaPos.z + CHAMPION_CAM_TAR_DIFF.z);

	//優勝者も合わせて前に向かせる
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, camTar, CHAMPION_CAM_RATE);
}

int MetaAI::VictoryPlayer()
{
	int winner = -1;
	int maxScore = ZERO;
	bool sameScore = false;


	for (int i = ZERO; i < score_.size(); i++) {

		//一位と点数が被っているか確認する
		if (maxScore == score_.at(i)) {
			sameScore = true;
		}

		//同時にボーダーにたどり着く可能性もあるため一番スコアの高い人を覚えておく
		if (score_.at(i) >= VICTORY_POINT && maxScore < score_.at(i)) {
			winner = i;
			maxScore = score_.at(i);
			sameScore = false;
		}
	}

	if (sameScore) {
		//同点だった場合勝ち数が多いほうが勝ち
	}

	return winner;
}
