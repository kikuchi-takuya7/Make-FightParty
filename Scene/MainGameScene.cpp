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
	: GameObject(parent, "MainGameScene"), pNavigationAI_(new NavigationAI), pMetaAI_(new MetaAI)
{
}

//������
void MainGameScene::Initialize()
{

	pNavigationAI_->Initialize();
	pMetaAI_->Initialize();
	pMetaAI_->SetNavigationAI(pNavigationAI_);
	
	int objectID = 0;
	

	//Astar�A���S���Y�����������Ă��畡���l�ǉ��ł���悤�ɂ��悤
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
	
	//�e��AI��p�ӂ��ăZ�b�g����
	for (int i = 0; i < ENEMY_NUM; i++) {

		pEnemy[i] = Instantiate<Enemy>(this);
		pEnemy[i]->SetObjectID(objectID);

		pNavigationAI_->PushCharacter(pEnemy[i]);
		pMetaAI_->PushCharacterStatus(pEnemy[i]->GetStatus());

		pEnemy[i]->SetPosition(CHARA_POS[objectID]);
		objectID++;

	}

	//character�̃X�e�[�^�X��S���v�b�V�����Ă��烁�^AI�ɏ���^���ă^�[�Q�b�g�������߂ăv���C���[�ȊO�������Ƒ_���悤��
	for (int i = 0; i < ENEMY_NUM; i++) {

		
		CharacterAI* charaAI = new CharacterAI(pEnemy[i], pNavigationAI_);
		charaAI->SetMetaAI(pMetaAI_);
		charaAI->Initialize();

		pEnemy[i]->SetCharacterAI(charaAI);
		

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
