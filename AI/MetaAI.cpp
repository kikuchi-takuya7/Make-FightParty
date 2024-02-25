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
#include "../Stage/CreateMode/CreateMode.h"

namespace {

	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -20);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 CHAMPION_CAM_DIFF = { ZERO,4,-5 };
	const float CHAMPION_CAM_RATE = 0.1f;

	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;

	const float WAIT_WINNER_TIME = 1.0f;
	const float WAIT_CHAMPION_TIME = 1.0f;


	const int WIN_POINT = 20;
	const int KILL_POINT = 10;
	const int OBJECT_KILL_POINT = 5;
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this))
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{

	//最初は誰が一位でも同じ
	No1CharaID_.emplace_back(ZERO);

	//とりあえずでIDだけ入れとく
	for (int i = ZERO; i < 4; i++) {
		ranking_.emplace_back(i);
	}

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();
}

void MetaAI::Update()
{
	

	//優勝者が決まったら試合を止める
	if (endGame_) {
		pNavigationAI_->AllEraseCollision();
		pWaitTimer_->Start();

		//一定時間待ったら優勝者にカメラを向ける
		if (pWaitTimer_->IsFinished()) {
			MoveChampionCam();
		}

		return;
	}

	//優勝者が決まってる場合は上で、決まってないならこっちでタイマーを使う。
	if (pWaitTimer_->IsFinished() || Input::IsKey(DIK_K)) {
		//pCreateMode_->ToSelectMode();

		pNavigationAI_->AllStopDraw();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);
		
		if (pRankingUI_->IsAllEndAnim() && Input::IsKeyDown(DIK_SPACE)) {
			pCreateMode_->ToSelectMode();
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
	if (characterStatusList_.at(ranking_.at(ZERO)).winPoint == characterStatusList_.at(ID).winPoint || No1AllDead == true) {

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

	//一位のポイントとそれと同じ点数が何人いるか
	int No1WinPoint = ZERO;
	int sameRateChara = ZERO;
	
	vector<pair<int,int>> ranking;

	//ソートする用の配列に入れる
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//キャラのWinPointとIDを入れる（リストに入ってる順番がそのままIDになってる）
		ranking.emplace_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//降順でソートする
	std::sort(ranking.rbegin(), ranking.rend());

	//一位のポイントとIDを覚えておく
	No1WinPoint = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	
	//ついでにメンバ変数のランキングも更新する
	ranking_.at(ZERO) = ranking.at(ZERO).second;
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//一位の人と同じポイントなら同率１位を入れる
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
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

	//3人以上死んでいたら
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		
		//勝ったプレイヤーのwinPointを増やして、現在の順位を確認する
		characterStatusList_.at(winPlayer).winPoint++;

		//優勝者が決まったらリザルトシーンに
		if (characterStatusList_.at(winPlayer).winPoint >= 4) {
			endGame_ = true;
			//pNavigationAI_->AllStopUpdate();
			pWaitTimer_->SetLimit(WAIT_CHAMPION_TIME);
			pWaitTimer_->Start();
			return;
		}

		//キャラクタークラスにも教える
		pNavigationAI_->SetStatus(winPlayer, characterStatusList_.at(winPlayer));
		CheckNo1Chara();

		pWaitTimer_->Start();

		pRankingUI_->SetScore(winPlayer, WIN_GAUGE);
		pNavigationAI_->AllStopUpdate();
		

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
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_DIFF.y, charaPos.z + CHAMPION_CAM_DIFF.z);

	//優勝者も合わせて前に向かせる
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, charaPos, CHAMPION_CAM_RATE);
}
