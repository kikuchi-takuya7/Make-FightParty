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

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	: GameObject(parent, "MainGameScene"), pNavigationAI_(Instantiate<NavigationAI>(this)), pMetaAI_(Instantiate<MetaAI>(this))
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

//�X�V
void MainGameScene::Update()
{

	//��했�ɏ��҂����܂�����v���C���[�ɃI�u�W�F�N�g��ǉ����Ă��炤����������
	if (pMetaAI_->NextGame()) {
		
		
	}
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
	/*SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);*/
	
	
}

void MainGameScene::CallStatus(int ID, Status status)
{
	pMetaAI_->ChangeStatus(ID, status);
}
