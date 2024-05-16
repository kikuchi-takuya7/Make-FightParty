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

	//画像のサイズ
	const XMFLOAT3 IMAGE_SIZE = XMFLOAT3(1.25, 1.28, 1.25);
	
	//プレイヤーの初期位置
	const XMFLOAT3 START_POS = XMFLOAT3(1, ZERO, 1);
	
	//オブジェクトの位置
	const XMFLOAT3 OBJECT_POS = XMFLOAT3(5, ZERO, 10);

	//カメラ
	const XMFLOAT3 MAIN_GAME_CAM_POS = XMFLOAT3(15, 10, -15);		//敵が近くにいるときのカメラ座標
	const XMFLOAT3 MAIN_GAME_CAM_TAR = XMFLOAT3(15, 0, 15);

}

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"), hBackGround_(-1)
{
}

//初期化
void TutorialScene::Initialize()
{
	//背景をロード
	hBackGround_ = Image::Load("Image/BackGround/BackGround.png");
	assert(hBackGround_ >= ZERO);

	Transform trans = transform_;
	trans.scale_ = XMFLOAT3(5, 5, 5);
	Image::SetTransform(hBackGround_, trans);

	//ステージを生成
	Stage* pStage = Instantiate<Stage>(this);

	//プレイヤーを生成（UI等は無し）
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

//更新
void TutorialScene::Update()
{

	/*if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_MAINGAME);
	}*/

}

//描画
void TutorialScene::Draw()
{
	Image::Draw(hBackGround_);
}

//開放
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
