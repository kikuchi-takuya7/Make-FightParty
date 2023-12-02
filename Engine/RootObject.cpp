#include "RootObject.h"
#include "SceneManager.h"
#include "Input.h"


RootObject::RootObject():
	GameObject(nullptr, "RootObject"), conf_(false)
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}

void RootObject::Imgui_Window()
{

	//ImGui::SetNextWindowPos(ImVec2(875, 10), ImGuiCond_Once);//, ImGuiCond_FirstUseEverこれを付けると初めて実行したときだけこの大きさに設定されて。それ以降はimgui.iniに保存される
	//ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_Once);//ImGuiCond_Onceを付けると呼び出すときだけこの大きさになる
	//ImGui::Begin("DataWindow");

	//ImGui::End();
}
