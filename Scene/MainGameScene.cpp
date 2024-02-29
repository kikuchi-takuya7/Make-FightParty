#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Engine/Camera.h"
#include "../Engine/Image.h"
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
	:GameObject(parent, "MainGameScene"),hPict_(-1)
{

}

//初期化
void MainGameScene::Initialize()
{
	//Direct3Dを呼び出す前にglobal.hを呼び出すから値がバグる。ので一旦ここで定数宣言しちゃう
	/*const XMFLOAT3 PLAYERUI_FIRST_POS = XMFLOAT3(SpriteToFloatX(185), SpriteToFloatY(650), ZERO);
	const float UI_DIFF = SpriteToFloatX(350);*/

	//ゲーム全体の位置等を管理するAI
	NavigationAI* pNavigationAI;

	//ゲーム全体のバランスを管理するAI
	MetaAI* pMetaAI;

	//ステージ
	Stage* pMetaA;

	pNavigationAI = Instantiate<NavigationAI>(this);
	pMetaAI = Instantiate<MetaAI>(this);
	pMetaA = Instantiate<Stage>(this);

	pNavigationAI->SetStage(pMetaA);

	pMetaAI->SetNavigationAI(pNavigationAI);
	
	int objectID = 0;

	CreateMode* createMode = Instantiate<CreateMode>(this);
	createMode->SetMetaAI(pMetaAI);
	createMode->SetNavigationAI(pNavigationAI);
	createMode->SetStage(pMetaA);
	pMetaA->SetCreateMode(createMode);
	pMetaAI->SetCreateMode(createMode);


	//プレイヤーをプレイ人数分用意する
	for (int i = 0; i < PLAYER_NUM; i++) {

		Player* pPlayer;
		pPlayer = NoInitInstantiate<Player>(this);
		pPlayer->SetObjectID(objectID);
		pPlayer->Initialize();

		std::string name = " Player" + std::to_string(objectID + 1);
		pPlayer->SetCharacterName(name);
		pPlayer->SetUIPos(XMFLOAT3(PLAYERUI_FIRST_POS.x + (UI_DIFF * objectID), PLAYERUI_FIRST_POS.y, ZERO));

		pNavigationAI->PushCharacter(pPlayer);
		pMetaAI->PushCharacterStatus(pPlayer->GetStatus());

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

		pNavigationAI->PushCharacter(pEnemy[i]);
		pMetaAI->PushCharacterStatus(pEnemy[i]->GetStatus());

		pEnemy[i]->SetPosition(CHARA_POS[objectID]);
		pEnemy[i]->SetStartPos(CHARA_POS[objectID]);
		objectID++;

	}



	//characterのステータスを全部プッシュしてからメタAIに情報を与えてターゲット等を決めてプレイヤー以外もちゃんと狙うように
	for (int i = 0; i < ENEMY_NUM; i++) {

		CharacterAI* charaAI = Instantiate<CharacterAI>(this);
		charaAI->SetEnemy(pEnemy[i]);
		charaAI->SetNavigationAI(pNavigationAI);
		charaAI->SetMetaAI(pMetaAI);

		pNavigationAI->PushCharacterAI(charaAI);

		pEnemy[i]->SetCharacterAI(charaAI);

		charaAI->AskTarget();
	}

	pMetaAI->StartGame();

	hPict_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hPict_ >= 0);

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
	//SAFE_RELEASE(pMetaAI);
	//SAFE_RELEASE(pNavigationAI);
	/*SAFE_DELETE(pMetaAI);
	SAFE_DELETE(pNavigationAI);*/
	
	
}