#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../MapEditor/MapEditor.h"
#include "../Engine/Camera.h"
#include "../Character/Enemy/Enemy.h"
#include "../AI/MetaAI.h"
#include "../AI/NavigationAI.h"
#include "../AI/CharacterAI.h"
#include "../Engine/Global.h"


//コンストラクタ
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), pNavigationAI_(new NavigationAI), pMetaAI_(new MetaAI)//, pPlayer(nullptr), pEnemy(nullptr)
{
}

//初期化
void MainGameScene::Initialize()
{

	pNavigationAI_->Initialize();
	pMetaAI_->Initialize();

	Player* pPlayer;

	Enemy* pEnemy;

	//Astarアルゴリズムが完成してから複数人追加しよう
	pPlayer = Instantiate<Player>(this);
	pNavigationAI_->SetPlayer(pPlayer);
	
	//各種AIを用意してセットする
	pEnemy = Instantiate<Enemy>(this);
	pNavigationAI_->SetEnemy(pEnemy);
	CharacterAI* charaAI = new CharacterAI(pEnemy, pNavigationAI_);
	charaAI->Initialize();
	pEnemy->SetCharacterAI(charaAI);
	
	
	//SAFE_DELETE(charaAI);


	Instantiate<Stage>(this);
	//Instantiate<MapEditor>(this);

	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));

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
	//SAFE_RELEASE(pMetaAI_);//RELEASEじゃなくてDELETEの可能性ワンタン
	//SAFE_RELEASE(pNavigationAI_);
	SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);
	
	
}
