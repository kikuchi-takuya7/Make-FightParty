#include "Room1.h"
#include "../MapData.h"
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
	ImGui::Begin("DataWindow");

	//Imguiの名前表示でcharにする必要があるためその準備
	int tmp = GetObjectID();
	std::string ID = std::to_string(tmp);
	std::string str = GetObjectName() + ID;
	const char* windowName = str.c_str();

	if (ImGui::CollapsingHeader(windowName))
	{

		Setting_Transform(transform_, -100.0f, 100.0f, 365.0f, 5.0f, GetObjectName() + ID);

		//Deleteボタンが押されたらDeleteの確認ウィンドウを表示して押されたら消す
		str = "delete" + ID;
		const char* deleteName = str.c_str();
		if (ImGui::Button(deleteName)) {
			isDelete_ = true;
		}

		if (isDelete_) {
			ImGui::SetNextWindowPos(ImVec2(600, 300), ImGuiCond_Once);//ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
			ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Once);
			std::string tmp = str + "OK?";
			const char* deleteConf = tmp.c_str();
			ImGui::Begin(deleteConf, &isDelete_);
			if (ImGui::Button(deleteConf)) {

				KillMe();
			}
			ImGui::End();
		}

		str = "ChangeUp" + ID;
		const char* changeUp = str.c_str();
		if (ImGui::Button(changeUp)) {
			((MapData*)this->GetParent())->ChengeUp(this);
			//KillMe();
		}

		str = "ChangeDown" + ID;
		const char* changeDown = str.c_str();
		if (ImGui::Button(changeDown)) {
			((MapData*)this->GetParent())->ChengeDown(this);
		}

	}
	ImGui::End();
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
