#include "TestFloor.h"
#include "../CreateMode.h"
#include "../../Model.h"

//コンストラクタ
TestFloor::TestFloor(GameObject* parent)
	:StageSourceBase(parent, "TestFloor")
{
}

//デストラクタ
TestFloor::~TestFloor()
{
}

//初期化
void TestFloor::Initialize()
{
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
