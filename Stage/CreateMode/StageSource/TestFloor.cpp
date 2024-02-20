#include "TestFloor.h"
#include "../CreateMode.h"
#include "../../Model.h"

//�R���X�g���N�^
TestFloor::TestFloor(GameObject* parent)
	:StageSourceBase(parent, "TestFloor")
{
}

//�f�X�g���N�^
TestFloor::~TestFloor()
{
}

//������
void TestFloor::Initialize()
{
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
