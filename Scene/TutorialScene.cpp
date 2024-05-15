#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../AI/CharacterAI.h"
#include "../AI/MetaAI.h"
#include "../AI/NavigationAI.h"

namespace {
	XMFLOAT3 IMAGE_SIZE = { 1.25,1.28,1.25 };
}

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"),tutorialImage_(-1)
{
}

//初期化
void TutorialScene::Initialize()
{

	tutorialImage_ = Image::Load("Image/TutorialUI/Tutorial.png");
	Transform imageTrans = transform_;
	imageTrans.scale_ = IMAGE_SIZE;
	Image::SetTransform(tutorialImage_,imageTrans);

	pNavigationAI_->SetStage(pStage_);
	pMetaAI_->SetNavigationAI(pNavigationAI_);

	//クリエイトモードに色々セットする
	CreateModeInit();

	int objectID = ZERO;
	Player* pPlayer[PLAYER_NUM];

	//プレイヤーをプレイ人数分用意する
	for (int i = ZERO; i < PLAYER_NUM; i++) {

		pPlayer[i] = CreateCharacter<Player>(objectID, " Player");
		objectID++;
	}


	//敵の最初のIDを覚えて後で使う
	pCreateMode_->SetStartEnemyID(objectID);
	Enemy* pEnemy[ENEMY_NUM];

	//各種AIを用意してセットする
	for (int i = ZERO; i < ENEMY_NUM; i++) {

		pEnemy[i] = CreateCharacter<Enemy>(objectID, "     CP");
		objectID++;
	}

	//外部ファイルからAIの情報を入手
	CsvReader csv;
	bool isLoad = csv.Load("CSV/AI_Option.csv");

	//AI毎の攻撃する射程、攻撃する確率、増加率、クールダウンを入手
	vector<float> attackRange;
	vector<int> attackProbability;
	vector<int> addProbability;
	vector<float> attackCoolDown;

	for (int i = ZERO; i < ENEMY_NUM; i++) {

		//csvでのy座標の位置が、一番上（0）には種類や説明等が書かれている為1増やす
		attackRange.push_back(csv.GetValueFloat(CSV_RANGE_POS, i + 1));
		attackProbability.push_back(csv.GetValueInt(CSV_PROBABILITY_POS, i + 1));
		addProbability.push_back(csv.GetValueInt(CSV_ADDPRO_POS, i + 1));
		attackCoolDown.push_back(csv.GetValueFloat(CSV_COOLDOWN_POS, i + 1));
	}

	//characterのステータスを全部プッシュしてからメタAIに情報を与えてターゲット等を決めて全員の中からちゃんと狙うように
	for (int i = ZERO; i < ENEMY_NUM; i++) {

		CreateCharaAI(pEnemy[i], attackRange.at(i), attackProbability.at(i), addProbability.at(i), attackCoolDown.at(i));
	}

	pMetaAI_->ResetGame();

	//背景をロード
	hPict_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hPict_ >= ZERO);

	Transform trans = transform_;
	trans.scale_ = XMFLOAT3(5, 5, 5);
	Image::SetTransform(hPict_, trans);
}

//更新
void TutorialScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//描画
void TutorialScene::Draw()
{
	Image::Draw(tutorialImage_);
}

//開放
void TutorialScene::Release()
{
	//pText_->Release();
	//Audio::Stop(hAudio_);
}

void TutorialScene::Imgui_Window()
{
}
