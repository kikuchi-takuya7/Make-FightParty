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

	//モデルのロードはCreateModeで全部終わらせちゃってるから、ここではしなくていい？逆にここですべき？
	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	

	//球を打つ間隔
	timer_->SetLimit(BULLET_INTERVAL);
	
}

void Cannon::ChildUpdate()
{

	timer_->Start();

	//内部タイマーが0になったら打ち、またリセットする
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(this);
		//pBullet->SetRotateY(transform_.position_.y);
		pBullet->SetScale(BULLET_SIZE);
		
		//球の当たり判定を作る
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
