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

	Player* pPlayer;

	Enemy* pEnemy;

	//Astar�A���S���Y�����������Ă��畡���l�ǉ����悤
	pPlayer = Instantiate<Player>(this);
	pNavigationAI_->SetPlayer(pPlayer);
	
	//�e��AI��p�ӂ��ăZ�b�g����
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
