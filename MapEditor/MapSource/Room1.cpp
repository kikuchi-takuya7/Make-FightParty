#include "Room1.h"
#include "../MapEditor.h"
#include "../../Model.h"

//コンストラクタ
Room1::Room1(GameObject* parent)
	:GameObject(parent, "Room1"), hModel_(-1), isDelete_(false), isClose_(false)
{
}

//デストラクタ
Room1::~Room1()
{
}

//初期化
void Room1::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Map/Room_01.fbx");
	assert(hModel_ >= 0);
}

//更新
void Room1::Update()
{
}

//描画
void Room1::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Room1::Release()
{
}

void Room1::Imgui_Window()
{

	//ImGui::Begin("DataWindow");
	//Imgui_Data_Edit();

}

void Room1::Imgui_Data_Edit()
{
	
}

bool Room1::IsKillCheck()
{
	return isDelete_;
}

void Room1::DeleteMe()
{
	isDelete_ = true;
}

void Room1::DeleteStop()
{
	isDelete_ = false;
}
