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

	//ImGui::SetNextWindowPos(ImVec2(875, 10), ImGuiCond_Once);//, ImGuiCond_FirstUseEver�����t����Ə��߂Ď��s�����Ƃ��������̑傫���ɐݒ肳��āB����ȍ~��imgui.ini�ɕۑ������
	//ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_Once);//ImGuiCond_Once��t����ƌĂяo���Ƃ��������̑傫���ɂȂ�
	//ImGui::Begin("DataWindow");

	//ImGui::End();
}
