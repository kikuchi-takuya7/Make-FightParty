#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Engine/Camera.h"
#include "../Character/Enemy/Enemy.h"
#include "../AI/MetaAI.h"
#include "../AI/NavigationAI.h"
#include "../AI/CharacterAI.h"
#include "../Engine/Global.h"

#include "../UI/PlayerUI.h"

namespace {

	const int PLAYER_NUM = 1;
	const int ENEMY_NUM = 3;
	const int MAXPLAYER = 4;
	const XMFLOAT3 CHARA_POS[4] = { XMFLOAT3(5,ZERO,5),XMFLOAT3(25,ZERO,5) ,XMFLOAT3(5,ZERO,25) ,XMFLOAT3(25,ZERO,25) };

	//プレイヤーUIの位置。後で画像用の座標に切り替える
	const XMFLOAT3 PLAYERUI_FIRST_POS = XMFLOAT3(185.0f,650.0f, ZERO);
	const float UI_DIFF = 275.0f;
}

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	:GameObject(parent, "MainGameScene"), pNavigationAI_(nullptr), pMetaAI_(nullptr),pStage_(nullptr)
{

}

//初期化
void MainGameScene::Initialize()
{
	//Direct3Dを呼び出す前にglobal.hを呼び出すから値がバグる。ので一旦ここで定数宣言しちゃう
	/*const XMFLOAT3 PLAYERUI_FIRST_POS = XMFLOAT3(SpriteToFloatX(185), SpriteToFloatY(650), ZERO);
	const float UI_DIFF = SpriteToFloatX(350);*/

	pNavigationAI_ = Instantiate<NavigationAI>(this);
	pMetaAI_ = Instantiate<MetaAI>(this);
	pStage_ = Instantiate<Stage>(this);

	pNavigationAI_->SetStage(pStage_);

	pMetaAI_->SetNavigationAI(pNavigationAI_);
	
	int objectID = 0;

	CreateMode* createMode = Instantiate<CreateMode>(this);
	createMode->SetMetaAI(pMetaAI_);
	createMode->SetNavigationAI(pNavigationAI_);
	createMode->SetStage(pStage_);
	pStage_->SetCreateMode(createMode);
	pMetaAI_->SetCreateMode(createMode);


	//プレイヤーをプレイ人数分用意する
	for (int i = 0; i < PLAYER_NUM; i++) {

		Player* pPlayer;
		pPlayer = NoInitInstantiate<Player>(this);
		pPlayer->SetObjectID(objectID);
		pPlayer->Initialize();

		std::string name = " Player" + std::to_string(objectID + 1);
		pPlayer->SetCharacterName(name);
		pPlayer->SetUIPos(XMFLOAT3(PLAYERUI_FIRST_POS.x + (UI_DIFF * objectID), PLAYERUI_FIRST_POS.y, ZERO));

		pNavigationAI_->PushCharacter(pPlayer);
		pMetaAI_->PushCharacterStatus(pPlayer->GetStatus());

		pPlayer->SetPosition(CHARA_POS[objectID]);
		pPlayer->SetStartPos(CHARA_POS[objectID]);
		objectID++;
	}

	//XMFLOAT3(PLAYERUI_FIRST_POS.x + (UI_DIFF * objectID), PLAYERUI_FIRST_POS.y, ZERO)
	
	//敵の最初のIDを覚えて後で使う
	createMode->SetStartEnemyID(objectID);

	Enemy* pEnemy[ENEMY_NUM];
	
	//各種AIを用意してセットする
	for (int i = 0; i < ENEMY_NUM; i++) {

		pEnemy[i] = NoInitInstantiate<Enemy>(this);
		pEnemy[i]->SetObjectID(objectID);
		pEnemy[i]->Initialize();

		std::string name = "     CP" + std::to_string(objectID + 1 - PLAYER_NUM);
		pEnemy[i]->SetCharacterName(name);
		pEnemy[i]->SetUIPos(XMFLOAT3(PLAYERUI_FIRST_POS.x + (UI_DIFF * objectID), PLAYERUI_FIRST_POS.y, ZERO));

		pNavigationAI_->PushCharacter(pEnemy[i]);
		pMetaAI_->PushCharacterStatus(pEnemy[i]->GetStatus());

		pEnemy[i]->SetPosition(CHARA_POS[objectID]);
		pEnemy[i]->SetStartPos(CHARA_POS[objectID]);
		objectID++;

	}



	//characterのステータスを全部プッシュしてからメタAIに情報を与えてターゲット等を決めてプレイヤー以外もちゃんと狙うように
	for (int i = 0; i < ENEMY_NUM; i++) {

		CharacterAI* charaAI = Instantiate<CharacterAI>(this);
		charaAI->SetEnemy(pEnemy[i]);
		charaAI->SetNavigationAI(pNavigationAI_);
		charaAI->SetMetaAI(pMetaAI_);

		pNavigationAI_->PushCharacterAI(charaAI);

		pEnemy[i]->SetCharacterAI(charaAI);

		charaAI->AskTarget();
	}

	pMetaAI_->StartGame();

	

}

//更新
void MainGameScene::Update()
{
}

//描画
void MainGameScene::Draw()
{
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