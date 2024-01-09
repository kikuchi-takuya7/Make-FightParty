#include "TestWall.h"
#include "../MapEditor.h"
#include "../../Model.h"


//コンストラクタ
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),isDelete_(false),isClose_(false)
{
}

//デストラクタ
TestWall::~TestWall()
{
}

//初期化
void TestWall::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Map/testWall.fbx");
    assert(hModel_ >= 0);
}

//更新
void TestWall::Update()
{
}

//描画
void TestWall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TestWall::Release()
{
}

void TestWall::Imgui_Window()
{

	//ImGui::Begin("DataWindow");
	//Imgui_Data_Edit();

}

void TestWall::Imgui_Data_Edit()
{
	
}

bool TestWall::IsKillCheck()
{
	return isDelete_;
}

void TestWall::DeleteMe()
{
	isDelete_ = true;
}

void TestWall::DeleteStop()
{
	isDelete_ = false;
}
