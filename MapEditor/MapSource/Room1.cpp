#include "Room1.h"
#include "../MapEditor.h"
#include "../../Model.h"

//�R���X�g���N�^
Room1::Room1(GameObject* parent)
	:GameObject(parent, "Room1"), hModel_(-1), isDelete_(false), isClose_(false)
{
}

//�f�X�g���N�^
Room1::~Room1()
{
}

//������
void Room1::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Map/Room_01.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Room1::Update()
{
}

//�`��
void Room1::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
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
