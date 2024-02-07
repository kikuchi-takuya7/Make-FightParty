#include "TestFloor.h"
#include "../CreateMode.h"
#include "../../Model.h"

//コンストラクタ
TestFloor::TestFloor(GameObject* parent)
	:StageSourceBase(parent, "TestFloor"), hModel_(-1), isDelete_(false), isClose_(false)
{
}

//デストラクタ
TestFloor::~TestFloor()
{
}

//初期化
void TestFloor::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Map/testFloor.fbx");
	assert(hModel_ >= 0);
}

//更新
void TestFloor::Update()
{
}

//描画
void TestFloor::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TestFloor::Release()
{
}

void TestFloor::Imgui_Window()
{

	//ImGui::Begin("DataWindow");
	//Imgui_Data_Edit();

}

void TestFloor::Imgui_Data_Edit()
{
	
}

bool TestFloor::IsKillCheck()
{
	return isDelete_;
}

void TestFloor::DeleteMe()
{
	isDelete_ = true;
}

void TestFloor::DeleteStop()
{
	isDelete_ = false;
}
