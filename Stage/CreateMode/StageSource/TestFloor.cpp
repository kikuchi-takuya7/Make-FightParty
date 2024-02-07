#include "TestFloor.h"
#include "../CreateMode.h"
#include "../../Model.h"

//�R���X�g���N�^
TestFloor::TestFloor(GameObject* parent)
	:StageSourceBase(parent, "TestFloor"), hModel_(-1), isDelete_(false), isClose_(false)
{
}

//�f�X�g���N�^
TestFloor::~TestFloor()
{
}

//������
void TestFloor::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Map/testFloor.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void TestFloor::Update()
{
}

//�`��
void TestFloor::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
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
