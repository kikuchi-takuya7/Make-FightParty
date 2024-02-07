#include "OneBrock.h"

OneBrock::OneBrock(GameObject* parent)
	:StageSourceBase(parent, "OneBrock")
{
}

OneBrock::~OneBrock()
{
}

void OneBrock::ChildInitialize()
{

	//モデルのロードはCreateModeで全部終わらせちゃってるから、ここではしなくていい？逆にここですべき？

}

void OneBrock::ChildUpdate()
{
}

void OneBrock::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void OneBrock::ChildRelease()
{
}

void OneBrock::OnCollision(GameObject* pTarget)
{
}
