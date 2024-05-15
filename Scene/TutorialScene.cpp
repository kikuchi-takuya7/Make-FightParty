#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/CreateMode.h"
#include "../AI/CharacterAI.h"
#include "../AI/MetaAI.h"
#include "../AI/NavigationAI.h"

namespace {
	XMFLOAT3 IMAGE_SIZE = { 1.25,1.28,1.25 };
}

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"),tutorialImage_(-1)
{
}

//������
void TutorialScene::Initialize()
{

	tutorialImage_ = Image::Load("Image/TutorialUI/Tutorial.png");
	Transform imageTrans = transform_;
	imageTrans.scale_ = IMAGE_SIZE;
	Image::SetTransform(tutorialImage_,imageTrans);

	pNavigationAI_->SetStage(pStage_);
	pMetaAI_->SetNavigationAI(pNavigationAI_);

	//�N���G�C�g���[�h�ɐF�X�Z�b�g����
	CreateModeInit();

	int objectID = ZERO;
	Player* pPlayer[PLAYER_NUM];

	//�v���C���[���v���C�l�����p�ӂ���
	for (int i = ZERO; i < PLAYER_NUM; i++) {

		pPlayer[i] = CreateCharacter<Player>(objectID, " Player");
		objectID++;
	}


	//�G�̍ŏ���ID���o���Č�Ŏg��
	pCreateMode_->SetStartEnemyID(objectID);
	Enemy* pEnemy[ENEMY_NUM];

	//�e��AI��p�ӂ��ăZ�b�g����
	for (int i = ZERO; i < ENEMY_NUM; i++) {

		pEnemy[i] = CreateCharacter<Enemy>(objectID, "     CP");
		objectID++;
	}

	//�O���t�@�C������AI�̏������
	CsvReader csv;
	bool isLoad = csv.Load("CSV/AI_Option.csv");

	//AI���̍U������˒��A�U������m���A�������A�N�[���_�E�������
	vector<float> attackRange;
	vector<int> attackProbability;
	vector<int> addProbability;
	vector<float> attackCoolDown;

	for (int i = ZERO; i < ENEMY_NUM; i++) {

		//csv�ł�y���W�̈ʒu���A��ԏ�i0�j�ɂ͎�ނ��������������Ă����1���₷
		attackRange.push_back(csv.GetValueFloat(CSV_RANGE_POS, i + 1));
		attackProbability.push_back(csv.GetValueInt(CSV_PROBABILITY_POS, i + 1));
		addProbability.push_back(csv.GetValueInt(CSV_ADDPRO_POS, i + 1));
		attackCoolDown.push_back(csv.GetValueFloat(CSV_COOLDOWN_POS, i + 1));
	}

	//character�̃X�e�[�^�X��S���v�b�V�����Ă��烁�^AI�ɏ���^���ă^�[�Q�b�g�������߂đS���̒����炿���Ƒ_���悤��
	for (int i = ZERO; i < ENEMY_NUM; i++) {

		CreateCharaAI(pEnemy[i], attackRange.at(i), attackProbability.at(i), addProbability.at(i), attackCoolDown.at(i));
	}

	pMetaAI_->ResetGame();

	//�w�i�����[�h
	hPict_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hPict_ >= ZERO);

	Transform trans = transform_;
	trans.scale_ = XMFLOAT3(5, 5, 5);
	Image::SetTransform(hPict_, trans);
}

//�X�V
void TutorialScene::Update()
{

	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}

}

//�`��
void TutorialScene::Draw()
{
	Image::Draw(tutorialImage_);
}

//�J��
void TutorialScene::Release()
{
	//pText_->Release();
	//Audio::Stop(hAudio_);
}

void TutorialScene::Imgui_Window()
{
}
