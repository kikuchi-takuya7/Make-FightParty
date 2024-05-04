#include "AutoCannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "../../../Engine/Audio.h"
#include "../../../AI/MetaAI.h"
#include "../../../AI/NavigationAI.h"
#include "../../../VFXData/VFXData.h"
#include "Bullet.h"

//定数宣言
namespace {
	const int COST = -1;

	const int MAX_PLAYER = 4;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 7.0f;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 5;
	const float BULLET_SPEED = 0.05f;

	const int SAME_SOUND = 3;
}

AutoCannon::AutoCannon(GameObject* parent)
	:StageSourceBase(parent, "AutoCannon"), timer_(Instantiate<Timer>(this)), pMetaAI_(nullptr),pNavigationAI_(nullptr),target_(ZERO)
{
}

AutoCannon::~AutoCannon()
{
}

void AutoCannon::ChildInitialize()
{


	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	hAudio_ = Audio::Load("Audio/SE/Cannon.wav", false, SAME_SOUND);
	Audio::Stop(hAudio_);

	//球を打つ間隔
	timer_->SetLimit(BULLET_INTERVAL);

	//開始時は設置したプレイヤー以外をランダムで狙うようにする。
	while (true)
	{
		target_ = rand() % MAX_PLAYER;
		if (target_ != authorID_) {
			break;
		}
	}
	

}

void AutoCannon::ChildUpdate()
{

	if (pNavigationAI_->GetCaracter(target_)->GetStatus().dead == true) {
		target_ = pMetaAI_->Targeting(authorID_).ID;
	}

	timer_->Start();

	//内部タイマーが0になったら打ち、またリセットする
	if (timer_->IsFinished()) {
		Bullet* pBullet = Instantiate<Bullet>(GetParent());
		pBullet->SetScale(BULLET_SIZE);
		pBullet->SetPosition(transform_.position_);

		//球の当たり判定を作る
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED, transform_.rotate_.y);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
		Audio::Play(hAudio_);
	}


	//狙っている敵に大砲を回転させる

	//今狙っている敵の座標をatan2で獲得
	XMFLOAT3 targetPos = pNavigationAI_->GetCaracter(target_)->GetPosition();
	targetPos = Float3Sub(targetPos,transform_.position_);

	//xをzとして、yをzとする事で、transform.rotateの0度とx軸を合わせて角度をそのまま使える様に
	float angle = atan2(targetPos.x,targetPos.z);
	float degree = XMConvertToDegrees(angle);

	SetRotateY(degree);

}

void AutoCannon::ChildDraw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void AutoCannon::ChildRelease()
{
}

void AutoCannon::OnCollision(GameObject* pTarget)
{


}

void AutoCannon::FiringEffect()
{
	EmitterData data;

	using namespace FiringEffect;

	data.textureFileName = FILENAME;
	data.position = transform_.position_;
	data.positionRnd = POSITIONRND;
	data.direction = DIRECTION;
	data.directionRnd = DIRECTIONRND;
	data.speed = SPEED;
	data.speedRnd = SPEEDRND;
	data.accel = FiringEffect::ACCEL;
	data.gravity = GRAVITY;
	data.color = COLOR;
	data.deltaColor = DELTACOLOR;
	data.rotate = ROTATE;
	data.rotateRnd = ROTATERND;
	data.spin = SPIN;
	data.size = FiringEffect::SIZE;
	data.sizeRnd = SIZERND;
	data.scale = SCALE;
	data.lifeTime = LIFETIME;
	data.delay = DELAY;
	data.number = NUMBER;
	data.isBillBoard = ISBILLBOARD;

	VFX::Start(data);
}
