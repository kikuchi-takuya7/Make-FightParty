#include "MainGameScene.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../Engine/Camera.h"
#include "../Engine/Image.h"
#include "../Engine/Audio.h"
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

	//�v���C���[UI�̈ʒu�B��ŉ摜�p�̍��W�ɐ؂�ւ���
	const XMFLOAT3 PLAYERUI_FIRST_POS = XMFLOAT3(185.0f,650.0f, ZERO);
	const float UI_DIFF = 275.0f;
}

//�R���X�g���N�^
MainGameScene::MainGameScene(GameObject* parent)
	:GameObject(parent, "MainGameScene"),hPict_(-1),pNavigationAI_(Instantiate<NavigationAI>(this)),pMetaAI_(Instantiate<MetaAI>(this)),
	pStage_(Instantiate<Stage>(this)),pCreateMode_(NoInitInstantiate<CreateMode>(this))
{

}

//������
void MainGameScene::Initialize()
{

	pNavigationAI_->SetStage(pStage_);
	pMetaAI_->SetNavigationAI(pNavigationAI_);
	
	//�N���G�C�g���[�h�ɐF�X�Z�b�g����
	CreateModeInit();

	int objectID = 0;

	//�v���C���[���v���C�l�����p�ӂ���
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
	
	//�G�̍ŏ���ID���o���Č�Ŏg��
	pCreateMode_->SetStartEnemyID(objectID);

	Enemy* pEnemy[ENEMY_NUM];
	
	//�e��AI��p�ӂ��ăZ�b�g����
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



	//character�̃X�e�[�^�X��S���v�b�V�����Ă��烁�^AI�ɏ���^���ă^�[�Q�b�g�������߂ăv���C���[�ȊO�������Ƒ_���悤��
	for (int i = 0; i < ENEMY_NUM; i++) {

		CharacterAI* charaAI = Instantiate<CharacterAI>(this);
		charaAI->SetEnemy(pEnemy[i]);
		charaAI->SetNavigationAI(pNavigationAI_);
		charaAI->SetMetaAI(pMetaAI_);

		pNavigationAI_->PushCharacterAI(charaAI);

		pEnemy[i]->SetCharacterAI(charaAI);

		charaAI->AskTarget();
	}

	pMetaAI_->ResetGame();

	hPict_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hPict_ >= 0);

	Transform trans = transform_;
	trans.scale_ = XMFLOAT3(5, 5, 5);
	Image::SetTransform(hPict_, trans);


	

}

//�X�V
void MainGameScene::Update()
{
}

//�`��
void MainGameScene::Draw()
{
	Image::Draw(hPict_);
}

//�J��
void MainGameScene::Release()
{
	/*SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pEnemy);*/
	//SAFE_RELEASE(pMetaAI_);
	//SAFE_RELEASE(pNavigationAI_);
	/*SAFE_DELETE(pMetaAI_);
	SAFE_DELETE(pNavigationAI_);*/
	
	
}

//�N���G�C�g���[�h�ɐF�X�Z�b�g�����肷��֐�
void MainGameScene::CreateModeInit()
{
	//�N���G�C�g���[�h�ɐF�X�Z�b�g����
	pCreateMode_->SetMetaAI(pMetaAI_);
	pCreateMode_->SetNavigationAI(pNavigationAI_);
	pCreateMode_->SetStage(pStage_);
	pCreateMode_->Initialize();
	pStage_->SetCreateMode(pCreateMode_);
	pMetaAI_->SetCreateMode(pCreateMode_);
}
