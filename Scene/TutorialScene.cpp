#include "TutorialScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Text.h"
#include "../Engine/Camera.h"
#include "../Character/Player/Player.h"
#include "../Stage/Stage.h"
#include "../Stage/CreateMode/StageSource/OneBrock.h"
#include "../Stage/CreateMode/StageSource/Cannon.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/AutoCannon.h"
#include "../Stage/CreateMode/StageSource/RotateBlade.h"
#include "../Stage/CreateMode/StageSource/Mud.h"

namespace {

	//�摜�̃T�C�Y
	const XMFLOAT3 IMAGE_SIZE = XMFLOAT3(1.25, 1.28, 1.25);
	
	//�v���C���[�̏����ʒu
	const XMFLOAT3 START_POS = XMFLOAT3(1, ZERO, 1);
	
	//�I�u�W�F�N�g�̈ʒu
	const XMFLOAT3 OBJECT_POS = XMFLOAT3(5, ZERO, 10);

	//�J����
	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -15);		//�G���߂��ɂ���Ƃ��̃J�������W
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);

}

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"), hBackGround_(-1)
{
}

//������
void TutorialScene::Initialize()
{
	//�w�i�����[�h
	hBackGround_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hBackGround_ >= ZERO);

	Transform trans = transform_;
	trans.scale_ = XMFLOAT3(5, 5, 5);
	Image::SetTransform(hBackGround_, trans);

	//�X�e�[�W�𐶐�
	Stage* pStage = Instantiate<Stage>(this);

	//�v���C���[�𐶐��iUI���͖����j
	Player* character = NoInitInstantiate<Player>(this);
	character->SetObjectID(ZERO);
	character->Initialize();
	character->SetPosition(START_POS);
	character->SetStartPos(START_POS);
	character->Enter();
	character->Invisible();

	
	CreateObject();

	Camera::SetPosition(MAIN_GAME_CAM_POS);
	Camera::SetTarget(MAIN_GAME_CAM_TAR);
}

//�X�V
void TutorialScene::Update()
{

	/*if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}*/

}

//�`��
void TutorialScene::Draw()
{
	Image::Draw(hBackGround_);
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

void TutorialScene::CreateObject()
{


}
