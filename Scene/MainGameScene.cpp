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

namespace {
	const int PLAYER_NUM = 1;
	const int ENEMY_NUM = 3;
	const XMFLOAT3 CHARA_POS[4] = { XMFLOAT3(5,ZERO,5),XMFLOAT3(25,ZERO,5) ,XMFLOAT3(5,ZERO,25) ,XMFLOAT3(25,ZERO,25) };
}

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), pNavigationAI_(new NavigationAI), pMetaAI_(new MetaAI)//, pPlayer(nullptr), pEnemy(nullptr)
{
}

//������
void MainGameScene::Initialize()
{

	pNavigationAI_->Initialize();
	pMetaAI_->Initialize();

	
	int element = 0;
	

	//Astar�A���S���Y�����������Ă��畡���l�ǉ��ł���悤�ɂ��悤
	for (int i = 0; i < PLAYER_NUM; i++) {

		Player* pPlayer;
		pPlayer = Instantiate<Player>(this);
		pNavigationAI_->PushPlayer(pPlayer);
		pMetaAI_->PushPlayerStatus(pPlayer->GetStatus());

		pPlayer->SetPosition(CHARA_POS[element]);
		element++;

		pPlayer->SetObjectID(i);
	}
	
	
	//�e��AI��p�ӂ��ăZ�b�g����
	for (int i = 0; i < ENEMY_NUM; i++) {

		Enemy* pEnemy;
		pEnemy = Instantiate<Enemy>(this);
		pNavigationAI_->PushEnemy(pEnemy);
		pMetaAI_->PushEnemyStatus(pEnemy->GetStatus());

		CharacterAI* charaAI = new CharacterAI(pEnemy, pNavigationAI_);
		charaAI->Initialize();

		pEnemy->SetCharacterAI(charaAI);
		pEnemy->SetPosition(CHARA_POS[element]);
		element++;

		pEnemy->SetObjectID(i);
	}

	
	
	
	//SAFE_DELETE(charaAI);


	Instantiate<Stage>(this);
	//Instantiate<MapEditor>(this);

	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));

}

//�X�V
void MainGameScene::Update()
{
}

//�`��
void MainGameScene::Draw()
{
}

//�J��
void MainGameScene::Release()
{
	/*SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pEnemy);*/
	//SAFE_RELEASE(pMetaAI_);//RELEASE����Ȃ���DELETE�̉\�������^��
	//SAFE_RELEASE(pNavigationAI_);
	SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);
	
	
}
