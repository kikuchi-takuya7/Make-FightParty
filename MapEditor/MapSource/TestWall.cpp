#include "TestWall.h"
#include "../MapEditor.h"
#include "../../Model.h"


//�R���X�g���N�^
TestWall::TestWall(GameObject* parent)
    :GameObject(parent, "TestWall"), hModel_(-1),isDelete_(false),isClose_(false)
{
}

//�f�X�g���N�^
TestWall::~TestWall()
{
}

//������
void TestWall::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Map/testWall.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void TestWall::Update()
{
}

//�`��
void TestWall::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
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
