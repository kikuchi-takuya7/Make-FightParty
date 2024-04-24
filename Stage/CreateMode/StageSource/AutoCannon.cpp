#include "AutoCannon.h"
#include "../../../Character/Character.h"
#include "../../../Engine/Timer.h"
#include "../../../Engine/VFX.h"
#include "../../../Engine/Audio.h"
#include "../../../AI/MetaAI.h"
#include "../../../AI/NavigationAI.h"
#include "Bullet.h"

//定数宣言
namespace {
	const int COST = -1;

	const int MAX_PLAYER = 4;

	const XMFLOAT3 BULLET_COLLISION_CENTER = XMFLOAT3(ZERO, ZERO, ZERO);
	const float BULLET_COLLISION_SIZE = 0.3f;
	const float BULLET_INTERVAL = 5;
	const float BULLET_SIZE = 0.3f;

	const int BULLET_ATTACK_POWER = 5;
	const float BULLET_SPEED = 0.1f;

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

	//モデルのロードはCreateModeで全部終わらせちゃってるから、ここではしなくていい？逆にここですべき？
	cost_ = COST;

	AddCollider(pBoxCollision_, COLLIDER_BROCK);

	hAudio_ = Audio::Load("Audio/SE/Cannon.wav", false, SAME_SOUND);
	Audio::Stop(hAudio_);

	//球を打つ間隔
	timer_->SetLimit(BULLET_INTERVAL);

	//設置したプレイヤー以外をランダムで狙うようにする。
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
		Bullet* pBullet = Instantiate<Bullet>(this);
		pBullet->SetScale(BULLET_SIZE);

		//球の当たり判定を作る
		SphereCollider* pBulletCollider = new SphereCollider(BULLET_COLLISION_CENTER, BULLET_COLLISION_SIZE);
		pBullet->SetBulletData(pBulletCollider, COLLIDER_BULLET, BULLET_ATTACK_POWER, BULLET_SPEED);
		timer_->Reset();
		timer_->Start();
		FiringEffect();
		Audio::Play(hAudio_);
	}


	//狙っている敵に大砲を回転させる

	//今狙っている敵の座標を獲得
	XMFLOAT3 targetPos = pNavigationAI_->GetCaracter(target_)->GetPosition();
	XMVECTOR targetVec = XMVector3Normalize(XMLoadFloat3(&targetPos));

	//前ベクトルを向いている方向に変換して、正規化
	XMVECTOR vFront = { 0,0,1,0 };
	vFront = XMVector3Normalize(vFront);

	//内積から角度を求める
	XMVECTOR vDot = XMVector3Dot(vFront, targetVec);
	float dot = XMVectorGetX(vDot);
	float angle = acos(dot);

	//外積が-になる角度なら
	XMVECTOR vCross = XMVector3Cross(vFront, targetVec);
	if (XMVectorGetY(vCross) < ZERO) {

		angle *= -1;
	}

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

	data.textureFileName = "VFX/cloudA.png";
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);
	data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	data.delay = 0;
	data.number = 2;
	data.lifeTime = 30;
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(0, 0, 0);
	data.speed = 0.1f;
	data.accel = 0.98;
	data.speedRnd = 0.0;
	data.size = XMFLOAT2(2, 2);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 1, 1, 0.2);
	data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);
	data.spin.z = 0.1;
	data.rotateRnd.z = 180;
	VFX::Start(data);
}
