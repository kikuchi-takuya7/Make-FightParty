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

	//���f���̃��[�h��CreateMode�őS���I��点������Ă邩��A�����ł͂��Ȃ��Ă����H�t�ɂ����ł��ׂ��H

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
