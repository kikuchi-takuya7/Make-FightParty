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
	: GameObject(parent, "MainGameScene"), pNavigationAI_(Instantiate<NavigationAI>(this)), pMetaAI_(Instantiate<MetaAI>(this))
{
}

//初期化
void MainGameScene::Initialize()
{

	pNavigationAI_->Initialize();
	pMetaAI_->Initialize();
	pMetaAI_->SetNavigationAI(pNavigationAI_);
	
	int objectID = 0;
	

	//Astarアルゴリズムが完成してから複数人追加できるようにしよう
	for (int i = 0; i < PLAYER_NUM; i++) {

		Player* pPlayer;
		pPlayer = Instantiate<Player>(this);
		pPlayer->SetObjectID(objectID);

		pNavigationAI_->PushCharacter(pPlayer);
		pMetaAI_->PushCharacterStatus(pPlayer->GetStatus());

		pPlayer->SetPosition(CHARA_POS[objectID]);
		objectID++;

		
	}
	
	Enemy* pEnemy[ENEMY_NUM];
	
	//各種AIを用意してセットする
	for (int i = 0; i < ENEMY_NUM; i++) {

		pEnemy[i] = Instantiate<Enemy>(this);
		pEnemy[i]->SetObjectID(objectID);

		pNavigationAI_->PushCharacter(pEnemy[i]);
		pMetaAI_->PushCharacterStatus(pEnemy[i]->GetStatus());

		pEnemy[i]->SetPosition(CHARA_POS[objectID]);
		objectID++;

	}

	//characterのステータスを全部プッシュしてからメタAIに情報を与えてターゲット等を決めてプレイヤー以外もちゃんと狙うように
	for (int i = 0; i < ENEMY_NUM; i++) {

		CharacterAI* charaAI = Instantiate<CharacterAI>(this);
		charaAI->SetEnemy(pEnemy[i]);
		charaAI->SetNavigationAI(pNavigationAI_);
		charaAI->SetMetaAI(pMetaAI_);
		pEnemy[i]->SetCharacterAI(charaAI);

		charaAI->AskTarget();
		

	}
	
	//SAFE_DELETE(charaAI);


	stage_ = Instantiate<Stage>(this);
	Instantiate<CreateMode>(this);

	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));

}

//更新
void MainGameScene::Update()
{

	//一戦毎に勝者が決まったらプレイヤーにオブジェクトを追加してもらう処理を入れる
	if (pMetaAI_->NextGame()) {
		
		
	}
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
