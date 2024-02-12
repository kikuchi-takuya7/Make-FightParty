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

namespace {
	const int PLAYER_NUM = 1;
	const int ENEMY_NUM = 3;
	const XMFLOAT3 CHARA_POS[4] = { XMFLOAT3(5,ZERO,5),XMFLOAT3(25,ZERO,5) ,XMFLOAT3(5,ZERO,25) ,XMFLOAT3(25,ZERO,25) };
}

//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), pNavigationAI_(nullptr), pMetaAI_(nullptr),pStage_(nullptr)
{

}

//初期化
void MainGameScene::Initialize()
{

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
		pPlayer = Instantiate<Player>(this);
		pPlayer->SetObjectID(objectID);

		pNavigationAI_->PushCharacter(pPlayer);
		pMetaAI_->PushCharacterStatus(pPlayer->GetStatus());

		pPlayer->SetPosition(CHARA_POS[objectID]);
		pPlayer->SetStartPos(CHARA_POS[objectID]);
		objectID++;

		
	}
	
	//敵の最初のIDを覚えて後で使う
	createMode->SetStartEnemyID(objectID);

	Enemy* pEnemy[ENEMY_NUM];
	
	//各種AIを用意してセットする
	for (int i = 0; i < ENEMY_NUM; i++) {

		pEnemy[i] = Instantiate<Enemy>(this);
		pEnemy[i]->SetObjectID(objectID);

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
	
	//SAFE_DELETE(charaAI);


	pMetaAI_->ResetGame();

	

}

//更新
void MainGameScene::Update()
{

	//一試合が終わったらクリエイトモードに移動する
	pMetaAI_->ToCreateMode();
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
	//SAFE_RELEASE(pMetaAI_);//RELEASEじゃなくてDELETEの可能性ワンタン
	//SAFE_RELEASE(pNavigationAI_);
	/*SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);*/
	
	
}

void MainGameScene::CallStatus(int ID, Status status)
{
	pMetaAI_->ChangeStatus(ID, status);
}
