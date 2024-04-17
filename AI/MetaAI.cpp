#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Character/CharacterState/CharacterState.h"
#include "../Engine/Camera.h"
#include "../Engine/Input.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Timer.h"
#include "../Engine/VFX.h"
#include "../Engine/Audio.h"
#include "../Engine/Text.h"
#include "../UI/CountDownUI.h"
#include "../UI/RankingUI.h"
#include "../UI/GaugeUI/RankingGaugeUI.h"
#include "../UI/WinnerUI.h"
#include "../UI/ChampionUI.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../VFXData/VFXData.h"

namespace {

	//カメラやエフェクトの位置
	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 15, -15);
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);
	const XMFLOAT3 MAIN_GAME_CAM_ANGLE = XMFLOAT3(1, 0, 1);
	const XMFLOAT3 CHAMPION_CAM_POS_DIFF = { ZERO,4,-5 };
	const XMFLOAT3 CHAMPION_CAM_TAR_DIFF = { ZERO,2,ZERO };
	const float CHAMPION_CAM_RATE = 0.05f;
	const float CHAMPION_EFFECT_DIFF = 2.0f;
	const XMFLOAT3 RANKING_CAM_POS = XMFLOAT3(15, 40, 0);
	const XMFLOAT3 RANKING_CAM_TAR = XMFLOAT3(15, 35, 15);
	const float RANKING_CAM_RATE = 0.1f;
	const float GAME_CAM_RATE = 0.01f;

	//カメラの角度°
	const int CAM_ANGLE = 45;

	//各シーン推移の際の待機時間
	const float WAIT_WINNER_TIME = 3.0f;
	const float WAIT_CHAMPION_TIME = 3.0f;

	//スコア関係
	const int SCORE[GAUGE_NUM] = { 20,10,5 };
	const int VICTORY_POINT = 80;

	//プレイヤーの最大人数
	const int PLAYER_MAX_NUM = 4;

	const int PLAYER_ID = ZERO;

	//表示する現在のAIの情報
	const XMFLOAT3 TEXT_POS = { 10,20,ZERO };
	std::string nowModeText[MODE_NUM] = { ":Waiting...",":ChampionMode",":ResultMode" };
}

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(ZERO),ranking_(ZERO),characterStatusList_(ZERO),
	endGame_(false),pWaitTimer_(Instantiate<Timer>(this)), pCountDown_(Instantiate<CountDownUI>(this)),pRankingUI_(Instantiate<RankingUI>(this)),
	pWinnerUI_(Instantiate<WinnerUI>(this)),pChampionUI_(nullptr),pText_(new Text)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
	//色々初期化
	for (int i = ZERO; i < PLAYER_MAX_NUM; i++) {
		No1CharaID_.emplace_back(i);
		ranking_.emplace_back(i);
		score_.emplace_back(ZERO);
	}

	pWaitTimer_->StopDraw();
	pWaitTimer_->Stop();
	pWaitTimer_->SetLimit(WAIT_WINNER_TIME);

	pRankingUI_->AllChildLeave();
	pRankingUI_->AllChildVisible();

	pWinnerUI_->Visible();
	
	hAudio_ = Audio::Load("Audio/FightBGM.wav", true);
	assert(hAudio_ >= ZERO);

	Audio::Play(hAudio_);

	pText_->Initialize();

}

void MetaAI::Update()
{
	mode_ = WAITING;

	//優勝者が決まったら試合を止める
	if (endGame_) {
		ChampionUpdate();
		return;
	}

	//優勝者が決まってる場合は上で、決まってないならこっちを使う。
	UsuallyUpdate();
	
}

void MetaAI::Draw()
{
	std::string str = GetObjectName() + nowModeText[mode_];
	pText_->Draw(TEXT_POS.x, TEXT_POS.y, str.c_str());
}

void MetaAI::Release()
{
}

// 狙うべき相手を指示する関数
// 引数：自分のID
// 戻り値：狙うべき敵のID
TargetInfo MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % TARGET_NUM;

	TargetInfo target;

	target.mode = (TARGETPATTERNTEXT)targetFrag;

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

		target.mode = (TARGETPATTERNTEXT)TARGET_RANDAM;
	}

	//全体的に見て一位のプレイヤーを優先的に狙うように
	switch (target.mode)
	{
	//キャラクターの中からランダムで狙う	
	case TARGET_RANDAM:
		while (true)
		{
			target.ID = rand() % characterStatusList_.size();

			//狙った相手が自分じゃなく、死んでいなければ
			if (target.ID != ID && characterStatusList_.at(target.ID).dead == false)
				return target;
		}
		break;
	
	//一位の中から誰かを狙う
	case TARGET_NO_1:
		while (true)
		{
			//狙った相手が自分じゃなければ
			int tmp = rand() % No1CharaID_.size();
			target.ID = No1CharaID_.at(tmp);
			if (target.ID != ID)
				return target;
		}
		break;

	case TARGET_NUM:
	default:
		break;
	}

	return target;

}

// セレクトモードで表示されたオブジェクトを選択する関数
// 引数：表示されているオブジェクト一覧
// 戻り値：どのオブジェクトを選んだか
int MetaAI::SelectObject(vector<int> model)
{
	//今はとりあえずランダムで返す
	return model.at(rand() % model.size());
}

// 勝敗が決まっていたらクリエイトモードへ移行する関数
void MetaAI::DecidedWinner()
{
	int deadNum = ZERO;

	int winPlayer = ZERO;

	//死んでる人数を数える
	for (int i = ZERO; i < characterStatusList_.size(); i++) {
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
		else {
			//勝った人のプレイヤーIDを覚えておく
			winPlayer = i;
		}
	}

	//3人以上死んでいればクリエイトモードへ
	if (deadNum >= PLAYER_MAX_NUM - 1 && pCreateMode_->GetState() == NONE) {
		ToCreateMode(winPlayer);
	}
}

// ゲームの状態をリセットしてカウントダウンする関数
void MetaAI::ResetGame()
{
	//もろもろ初期化して、カウントダウンが終わるまで動かさない。
	pNavigationAI_->AllEraseCollision();
	pNavigationAI_->AllResetStatus();
	pNavigationAI_->AllStartDraw();
	pNavigationAI_->AllStopUpdate();
	pNavigationAI_->AllResetAITarget();
	
	pCountDown_->Start();
	//GameCameraMove();

	Audio::Play(hAudio_);

}


// characterStatusList_にステータスをプッシュすると同時に、名前もRankingUIにセットする関数
// 引数：プッシュしたいステータス
void MetaAI::PushCharacterStatus(Status status)
{
	characterStatusList_.emplace_back(status);
	pRankingUI_->SetPlayerName(characterStatusList_.size() - 1, status.playerName);
}


///////////////////////////////////////////////private関数///////////////////////////////////////////


// 優勝者が決まった時のUpdate
void MetaAI::ChampionUpdate()
{
	//一定時間待ったら優勝者にカメラを向ける
	if (pWaitTimer_->IsFinished()) {
		mode_ = CHAMPIONMODE;
		pChampionUI_->Invisible();
		pChampionUI_->Enter();
		pRankingUI_->AllChildVisible();
		pRankingUI_->AllChildLeave();
		MoveChampionCam();
		VictoryEffect();
		if (pChampionUI_->IsEnd() && Input::IsKeyDown(DIK_SPACE)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

// 通常時のUpdate関数
void MetaAI::UsuallyUpdate()
{
	//試合が終わったらタイマーがスタートして、終わったら呼ばれる
	if (pWaitTimer_->IsFinished()) {
		mode_ = RESULTMODE;
		pNavigationAI_->AllStopDrawPlayerUI();
		pRankingUI_->AllChildInvisible();
		pRankingUI_->AllChildEnter();
		pWinnerUI_->Visible();
		Camera::MoveCam(RANKING_CAM_POS, RANKING_CAM_TAR, RANKING_CAM_RATE);


#ifdef _DEBUG //デバック用 ゲージを増やす
		if (Input::IsKeyDown(DIK_2)) {
			pRankingUI_->SetScore(ZERO, WIN_GAUGE);
			score_.at(ZERO) += SCORE[WIN_GAUGE];
		}
		if (Input::IsKeyDown(DIK_3)) {
			pRankingUI_->SetScore(1, KILL_GAUGE);
			score_.at(ZERO) += SCORE[KILL_GAUGE];
		}
		if (Input::IsKeyDown(DIK_4)) {
			pRankingUI_->SetScore(2, TRAP_KILL_GAUGE);
			score_.at(ZERO) += SCORE[TRAP_KILL_GAUGE];
		}
#endif

		//スペースが押されたら次へ進むorアニメーションが終わってないならアニメーションをスキップする
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
				pChampionUI_ = Instantiate<ChampionUI>(this);
				pChampionUI_->Visible();
				pChampionUI_->Leave();
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

	//カメラを動かす
	GameCameraMove();
}

// 1位のキャラIDは誰か、何人いるかを確認する関数
void MetaAI::CheckNo1Chara()
{

	No1CharaID_.clear();

	//一位のポイントとそれと同じ点数が何人いるか
	int No1Score = ZERO;

	vector<pair<int, int>> ranking;

	//ソートする用の配列に入れる
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//キャラのスコアとIDを入れる（リストに入ってる順番がそのままIDになってる）
		ranking.emplace_back(std::make_pair(score_.at(i), i));
	}

	//降順でソートする
	std::sort(ranking.rbegin(), ranking.rend());

	//一位のポイントとIDを覚えておく
	No1Score = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);

	//ついでにメンバ変数のランキングも更新する
	ranking_.at(ZERO) = ranking.at(ZERO).second;

	//2位から更新するため、1からforを回す
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


// クリエイトモードに移行する関数
// 引数：勝ったプレイヤーのID
void MetaAI::ToCreateMode(int winnerID)
{

	//勝ったプレイヤーのwinPointを増やして、現在の順位を確認する
	characterStatusList_.at(winnerID).winPoint++;

	pNavigationAI_->GetCaracter(winnerID)->ChangeState(IDLE);

	//キャラクタークラスにも教える
	pNavigationAI_->SetStatus(winnerID, characterStatusList_.at(winnerID));


	//勝者にスコアを追加する
	pRankingUI_->SetScore(winnerID, WIN_GAUGE);
	score_.at(winnerID) += SCORE[WIN_GAUGE];

	//キル数分もスコアに加算する
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		pRankingUI_->SetScore(i, KILL_GAUGE, characterStatusList_.at(i).killPoint);
		score_.at(i) += SCORE[KILL_GAUGE] * characterStatusList_.at(i).killPoint;

		pRankingUI_->SetScore(i, TRAP_KILL_GAUGE, characterStatusList_.at(i).trapKillPoint);
		score_.at(i) += SCORE[TRAP_KILL_GAUGE] * characterStatusList_.at(i).trapKillPoint;
	}

	//現状の一位が誰か確認する
	CheckNo1Chara();

	pRankingUI_->AllChildLeave();
	pNavigationAI_->AllStopUpdate();

	pWinnerUI_->SetWinnerID(winnerID);
	pWinnerUI_->Invisible();

	pWaitTimer_->Start();

	Audio::Stop(hAudio_);

}

// ゲーム用カメラにセットする関数
void MetaAI::GameCameraSet()
{
	Camera::SetPosition(MAIN_GAME_CAM_POS);
	Camera::SetTarget(MAIN_GAME_CAM_TAR);
}

// ゲームカメラを動かす関数
void MetaAI::GameCameraMove()
{

#if 0 //一番遠い敵との間を注視点にしたやつ

	//一番遠いキャラのIDとプレイヤーのIDの位置の真ん中に注視点を置く
	int farthestID = pNavigationAI_->Farthest(PLAYER_ID);

	//既に勝者が決まっていたら
	if (farthestID == -1) {
		return;
	}

	XMFLOAT3 farPos = pNavigationAI_->GetCaracter(farthestID)->GetPosition();
	XMFLOAT3 myPos = pNavigationAI_->GetCaracter(PLAYER_ID)->GetPosition();

	//真ん中の注視点を求める
	XMFLOAT3 camTar = Float3Add(farPos, myPos) / 2;

	//座標は線分の半径分遠くすればいい感じか.camTarとの距離をキャラの距離分ぐらい離してみよう。x座標とy座標だけ動かさない感じ？
	XMFLOAT3 camPos = camTar;
	camPos.z = MAIN_GAME_CAM_POS.z;
	camPos.y = MAIN_GAME_CAM_POS.y;

	float dis = pNavigationAI_->Distance(farthestID, PLAYER_ID);
	
	Camera::MoveCam(camPos, camTar, GAME_CAM_RATE);

#else //4体の真ん中を注視点にしようとしてるやつ
	
	//ID順にキャラクターの座標
	vector<XMFLOAT3> playerPos;

	//ナビゲーションAIから全てのキャラクターの座標を得る
	for (int i = ZERO; i < PLAYER_MAX_NUM; i++) {
		playerPos.emplace_back(pNavigationAI_->GetCaracter(i)->GetPosition());
	}

	float maxX = ZERO, maxZ = ZERO, minX = 9999, minZ = 9999;

	//xとyの最大値、最小値を求める
	for (int i = ZERO; i < playerPos.size(); i++) {

		if (maxX < playerPos.at(i).x) {
			maxX = playerPos.at(i).x;
		}
		else if (minX > playerPos.at(i).x) {
			minX = playerPos.at(i).x;
		}

		if (maxZ < playerPos.at(i).z) {
			maxZ = playerPos.at(i).z;
		}
		else if (minZ > playerPos.at(i).z) {
			minZ = playerPos.at(i).z;
		}
	}

	//一番遠いキャラとの距離を測って、その長さと45度で単位円として斜辺の長さを求めて、その長さを使って何とかしてzとyを求めれば行けるかな
	//平行移動行列見たいなの必要か？
	float radian = XMConvertToRadians(CAM_ANGLE);
	float bottom = maxX - minX;
	float hypot = bottom / radian;

	//四角形の中心を注視点にする
	XMFLOAT3 centerPoint = XMFLOAT3((maxX + minX) / 2, ZERO, (maxZ + minZ) / 2);
	//Camera::SetPosition(XMFLOAT3(centerPoint.x, MAIN_GAME_CAM_POS.y, centerPoint.z));

	XMFLOAT3 tmp = XMFLOAT3(centerPoint.x, hypot / 2, -(hypot / 2 + MAIN_GAME_CAM_POS.z));
	SetPosition(tmp);

	XMVECTOR target = XMLoadFloat3(&centerPoint);
	Camera::SetTarget(target);



#endif

}

// 優勝者の方にカメラを向ける関数
void MetaAI::MoveChampionCam()
{
	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 charaPos = pChampion->GetPosition();
	XMFLOAT3 camPos = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_POS_DIFF.y, charaPos.z + CHAMPION_CAM_POS_DIFF.z);
	XMFLOAT3 camTar = XMFLOAT3(charaPos.x, charaPos.y + CHAMPION_CAM_TAR_DIFF.y, charaPos.z + CHAMPION_CAM_TAR_DIFF.z);

	//優勝者も合わせて前に向かせる為、180度(画面の真正面)に回転させる
	XMFLOAT3 rot = pChampion->GetRotate();
	RateMovePosition(rot, XMFLOAT3(rot.x, 180, rot.z), CHAMPION_CAM_RATE);
	pChampion->SetRotateY(rot.y);

	Camera::MoveCam(camPos, camTar, CHAMPION_CAM_RATE);
}

// 優勝者は誰かを決める関数
// 引数：優勝したプレイヤーのID
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

// 優勝者の周りにエフェクトを出す関数
void MetaAI::VictoryEffect()
{

	using namespace VictoryEffect;

	Character* pChampion = pNavigationAI_->GetCaracter(No1CharaID_.at(ZERO));
	XMFLOAT3 championPos = pChampion->GetPosition();

	EmitterData data;

	//炎本体（プレイヤーの右と左に出す）
	{
		using namespace Fire;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(championPos.x + CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = Fire::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = Fire::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);

		//左に炎を出す
		data.position = XMFLOAT3(championPos.x - CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		VFX::Start(data);
	}
	
	//火の粉
	{
		using namespace FireSpark;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(championPos.x + CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = FireSpark::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.rotate = ROTATE;
		data.rotateRnd = ROTATERND;
		data.spin = SPIN;
		data.size = FireSpark::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;
		data.isBillBoard = ISBILLBOARD;

		VFX::Start(data);

		//左に火の粉を出す
		data.position = XMFLOAT3(championPos.x - CHAMPION_EFFECT_DIFF, ZERO, championPos.z);
		VFX::Start(data);
	}
}
