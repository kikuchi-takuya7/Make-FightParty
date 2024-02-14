#include "Cannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "Bullet.h"

namespace {
	const int COST = -1;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 3;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 10;
	const float BULLET_SPEED = 0.4f;
}

Cannon::Cannon(GameObject* parent)
	:StageSourceBase(parent, "Cannon"), timer_(Instantiate<Timer>(this))
{
}

Cannon::~Cannon()
{
}

void Cannon::ChildInitialize()
{

	//���f���̃��[�h��CreateMode�őS���I��点������Ă邩��A�����ł͂��Ȃ��Ă����H�t�ɂ����ł��ׂ��H
	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	

	//����łԊu
	timer_->SetLimit(BULLET_INTERVAL);
	
}

void Cannon::ChildUpdate()
{

	timer_->Start();

	//�����^�C�}�[��0�ɂȂ�����ł��A�܂����Z�b�g����
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(this);
		//pBullet->SetRotateY(transform_.position_.y);
		pBullet->SetScale(BULLET_SIZE);
		
		//���̓����蔻������
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED);
		timer_->Reset();
		timer_->Start();
	}

}

void Cannon::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Cannon::ChildRelease()
{
}

void Cannon::OnCollision(GameObject* pTarget)
{
	

}
