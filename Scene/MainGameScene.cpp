#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Engine/Camera.h"
#include "../Engine/Image.h"
#include "../Engine/Audio.h"
#include "../Engine/CsvReader.h"
#include "../Character/Enemy/Enemy.h"
#include "../AI/MetaAI.h"
#include "../AI/NavigationAI.h"
#include "../AI/CharacterAI.h"
#include "../Engine/Global.h"

#include "../UI/PlayerUI.h"

namespace {

	const int PLAYER_NUM = 1;
	const int ENEMY_NUM = 3;
	const int MAX_PLAYER = 4;
	const XMFLOAT3 CHARA_POS[4] = { XMFLOAT3(5,ZERO,5),XMFLOAT3(25,ZERO,5) ,XMFLOAT3(5,ZERO,25) ,XMFLOAT3(25,ZERO,25) };

	//プレイヤーUIの位置。後で画像用の座標に切り替える
	const XMFLOAT3 PLAYERUI_FIRST_POS = XMFLOAT3(185.0f, 650.0f, ZERO);
	const float UI_DIFF = 275.0f;

	//csv内の攻撃射程、攻撃確率がある位置（x座標のみ）
	const int CSV_RANGE_POS = 1;
	const int CSV_PROBABILITY_POS = 2;
	const int CSV_ADDPRO_POS = 3;
	const int CSV_COOLDOWN_POS = 4;
}

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	:GameObject(parent, "MainGameScene"),hPict_(-1),pNavigationAI_(Instantiate<NavigationAI>(this)),pMetaAI_(Instantiate<MetaAI>(this)),
	pStage_(Instantiate<Stage>(this)),pCreateMode_(NoInitInstantiate<CreateMode>(this))
{

}

//初期化
void MainGameScene::Initialize()
{

	

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

		CreateCharaAI(pEnemy[i],attackRange.at(i),attackProbability.at(i),addProbability.at(i), attackCoolDown.at(i));
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
void MainGameScene::Update()
{
}

//描画
void MainGameScene::Draw()
{
	Image::Draw(hPict_);
}

//開放
void MainGameScene::Release()
{
	/*SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pEnemy);*/
	//SAFE_RELEASE(pMetaAI_);
	//SAFE_RELEASE(pNavigationAI_);
	/*SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);*/
	
	
}

//クリエイトモードに色々セットしたりする関数
void MainGameScene::CreateModeInit()
{
	//クリエイトモードに色々セットする
	pCreateMode_->SetMetaAI(pMetaAI_);
	pCreateMode_->SetNavigationAI(pNavigationAI_);
	pCreateMode_->SetStage(pStage_);
	pCreateMode_->Initialize();
	pStage_->SetCreateMode(pCreateMode_);
	pMetaAI_->SetCreateMode(pCreateMode_);
}

void MainGameScene::CreateCharaAI(Enemy* enemy, float attackRange, int attackProbability, int addPro, float coolDown)
{
	CharacterAI* charaAI = NoInitInstantiate<CharacterAI>(this);
	charaAI->SetEnemy(enemy);
	charaAI->SetNavigationAI(pNavigationAI_);
	charaAI->SetMetaAI(pMetaAI_);
	charaAI->SetAttackRange(attackRange);
	charaAI->SetAttackProbability(attackProbability);
	charaAI->SetAttackAddPro(addPro);
	charaAI->SetAttackCoolDown(coolDown);
	charaAI->Initialize();

	pNavigationAI_->PushCharacterAI(charaAI);

	enemy->SetCharacterAI(charaAI);

	charaAI->AskTarget();
}

template<class T>
T* MainGameScene::CreateCharacter(int ID, std::string name)
{
	T* character = NoInitInstantiate<T>(this);
	character->SetObjectID(ID);
	character->Initialize();

	std::string str = name + std::to_string(ID + 1);
	character->SetCharacterName(str);
	character->SetUIPos(XMFLOAT3(PLAYERUI_FIRST_POS.x + (UI_DIFF * ID), PLAYERUI_FIRST_POS.y, ZERO));

	character->SetPosition(CHARA_POS[ID]);
	character->SetStartPos(CHARA_POS[ID]);

	pNavigationAI_->PushCharacter(character);
	pMetaAI_->PushCharacterStatus(character->GetStatus());

	return character;
}
