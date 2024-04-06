#include "Character.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"
#include "../Engine/Audio.h"
#include "../Engine/VFX.h"
#include "../Stage/CreateMode/StageSource/Bullet.h"
#include "../Stage/CreateMode/StageSource/Needle.h"
#include "../Stage/CreateMode/StageSource/StageSourceBase.h"
#include "../UI/PlayerUI.h"
#include "CharacterState/CharacterStateManager.h"
#include "../VFXData/VFXData.h"

//基礎ステータス等
namespace {
	const int CHARACTER_HP = 100;
	const int CHARACTER_ATTACK_POWER = 25;
	const XMFLOAT3 BODY_COLLISION_CENTER = XMFLOAT3(ZERO, 1, ZERO);
	const XMFLOAT3 BODY_COLLISION_SIZE = XMFLOAT3(0.9, 2, 0.9);
	const XMFLOAT3 ATTACK_COLLISION_CENTER = XMFLOAT3(ZERO, 1, 1);
	const XMFLOAT3 ATTACK_COLLISION_SIZE = XMFLOAT3(1.5, 0.5, 3);

	const int PLAYER_MAX_NUM = 4;
}

//namespace HitEffectData {
//	std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
//	XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, 0.5f, 0.5f);	//位置の誤差
//	XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//移動方向の誤差（各軸の角度）
//	float	 SPEED = 0.2f;			//1フレームの速度
//	float	 SPEEDRND = ZERO;		//速度誤差（0～1）
//	float	 ACCEL = 1.0f;			//加速度
//	float	 GRAVITY = 0.0f;		//重力
//	XMFLOAT4 COLOR = XMFLOAT4(1, 1, ZERO, 1);					//色（RGBA 0～1）
//	XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -0.03f, ZERO, -0.02f);	//色の変化量
//	XMFLOAT3 ROTATE = XMFLOAT3(ZERO, ZERO, ZERO);		//各軸での角度
//	XMFLOAT3 ROTATERND = XMFLOAT3(ZERO, ZERO, ZERO);	//角度誤差
//	XMFLOAT3 SPIN = XMFLOAT3(ZERO, ZERO, ZERO);			//回転速度
//	XMFLOAT2 SIZE = XMFLOAT2(0.3, 0.3f);			//サイズ
//	XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//サイズ誤差（0～1）
//	XMFLOAT2 SCALE = XMFLOAT2(0.9f, 0.9f);			//1フレームの拡大率
//	DWORD	 LIFETIME = 15;		//パーティクルの寿命（フレーム数）
//	DWORD	 DELAY = ZERO;		//何フレームおきにパーティクルを発生させるか
//	DWORD	 NUMBER = 40;		//1度に出すパーティクル量
//	bool	 ISBILLBOARD;		//ビルボードかどうか
//}
//
//namespace DieEffect {
//	namespace Explosion {
//		std::string FILENAME = "VFX/cloudA.png";				//画像ファイル名	
//		XMFLOAT3 POSITIONRND = ZERO_FLOAT3;						//位置の誤差
//		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1.0f, ZERO);		//移動方向
//		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);			//移動方向の誤差（各軸の角度）
//		float	 SPEED = 0.1f;			//1フレームの速度
//		float	 SPEEDRND = 0.8f;		//速度誤差（0～1）
//		float	 ACCEL = 1.0f;			//加速度
//		float	 GRAVITY = 0.0f;		//重力
//		XMFLOAT4 COLOR = XMFLOAT4(1.0f, 1.0f, 0.1f, 1.0f);					//色（RGBA 0～1）
//		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, -1.0 / 20, ZERO, -1.0 / 20);	//色の変化量
//		XMFLOAT3 ROTATE;		//各軸での角度
//		XMFLOAT3 ROTATERND;		//角度誤差
//		XMFLOAT3 SPIN;			//回転速度
//		XMFLOAT2 SIZE = XMFLOAT2(1.2f, 1.2f);			//サイズ
//		XMFLOAT2 SIZERND = XMFLOAT2(0.4, 0.4f);			//サイズ誤差（0～1）
//		XMFLOAT2 SCALE = XMFLOAT2(1.05f, 1.05f);			//1フレームの拡大率
//		DWORD	 LIFETIME = 30;		//パーティクルの寿命（フレーム数）
//		DWORD	 DELAY = ZERO;		//何フレームおきにパーティクルを発生させるか
//		DWORD	 NUMBER = 80;		//1度に出すパーティクル量
//		bool	 ISBILLBOARD;		//ビルボードかどうか
//	}
//	namespace FireSpark {
//		std::string FILENAME = "VFX/cloudA.png";			//画像ファイル名
//		XMFLOAT3 POSITIONRND = XMFLOAT3(0.5f, ZERO, 0.5f);	//位置の誤差
//		XMFLOAT3 DIRECTION = XMFLOAT3(ZERO, 1, ZERO);		//移動方向
//		XMFLOAT3 DIRECTIONRND = XMFLOAT3(90, 90, 90);		//移動方向の誤差（各軸の角度）
//		float	 SPEED = 0.25f;			//1フレームの速度
//		float	 SPEEDRND = 1.0f;		//速度誤差（0～1）
//		float	 ACCEL = 0.93f;			//加速度
//		float	 GRAVITY = 0.003f;		//重力
//		XMFLOAT4 COLOR = XMFLOAT4(1, 1, 0.1f, 1);					//色（RGBA 0～1）
//		XMFLOAT4 DELTACOLOR = XMFLOAT4(ZERO, ZERO, ZERO, ZERO);		//色の変化量
//		XMFLOAT3 ROTATE;		//各軸での角度
//		XMFLOAT3 ROTATERND;		//角度誤差
//		XMFLOAT3 SPIN;			//回転速度
//		XMFLOAT2 SIZE = XMFLOAT2(0.1f, 0.1f);				//サイズ
//		XMFLOAT2 SIZERND = XMFLOAT2(0.4f, 0.4f);			//サイズ誤差（0～1）
//		XMFLOAT2 SCALE = XMFLOAT2(0.99f, 0.99f);			//1フレームの拡大率
//		DWORD	 LIFETIME = 100;		//パーティクルの寿命（フレーム数）
//		DWORD	 DELAY = ZERO;			//何フレームおきにパーティクルを発生させるか
//		DWORD	 NUMBER = 80;			//1度に出すパーティクル量
//		bool	 ISBILLBOARD;			//ビルボードかどうか
//	}
//
//}

//コンストラクタ
Character::Character(GameObject* parent,std::string name)
	:GameObject(parent, name), hModel_(-1),status_(Status(CHARACTER_HP, CHARACTER_ATTACK_POWER, false, ZERO, ZERO, ZERO, "NONE")),
	pState_(nullptr), pBodyCollision_(nullptr), pAttackCollision_(nullptr), startPos_(ZERO_FLOAT3), hSoundEffect_{-1,-1}
	,pPlayerUI_(Instantiate<PlayerUI>(this))
{
}

//デストラクタ
Character::~Character()
{
}

//初期化
void Character::Initialize()
{
	pBodyCollision_ = new BoxCollider(BODY_COLLISION_CENTER, BODY_COLLISION_SIZE, ZERO_FLOAT3);
	pAttackCollision_ = new BoxCollider(ATTACK_COLLISION_CENTER, ATTACK_COLLISION_SIZE, ZERO_FLOAT3);

	//モデルデータのロード
	std::string fileName = "PlayerFbx/player" + std::to_string(GetObjectID()) + ".fbx";
	hModel_ = Model::Load(fileName);
	assert(hModel_ >= ZERO);

	pState_ = new CharacterStateManager(this, hModel_);

	pPlayerUI_->SetMaxHp(status_.hp, status_.hp);


	//音声データのロード
	std::string str[SE_NUM] = { "Damage","Dead", };

	for (int i = ZERO; i < SE_NUM; i++) {

		std::string dir = "Audio/SE/";
		std::string extention = ".wav";

		std::string fileName = dir + str[i] + extention;

		hSoundEffect_[i] = Audio::Load(fileName,false,PLAYER_MAX_NUM);
		assert(hSoundEffect_[i] >= ZERO);

		Audio::Stop(hSoundEffect_[i]);
	}
	
	ChildInitialize();
}

//更新
void Character::Update()
{
	//動いてほしくないとき
	if (IsEntered() == false) {
		return;
	}

	//今いる位置をprevPosに置いておく
	prevPos_ = transform_.position_;

	

	pState_->Update();

	

	//ノックバック中は移動の処理をしない
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(KNOCKBACK) && pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK) && status_.dead == false) {
		ChildUpdate();
	}


}

//描画
void Character::Draw()
{

	if (IsVisibled())
		return;

	ChildDraw();
}

//開放
void Character::Release()
{
	ChildRelease();

	//試合中以外、Collisionは消しているのでここでDELETEする。

	//コリジョンをcolliderListから外してるときは自動開放されないので、特定の条件の時のみ自分で開放する
	if (pState_->characterState_ != pState_->pCharacterStateList_.at(ATTACK)) {

		SAFE_DELETE(pAttackCollision_);
	}
	else if (pState_->characterState_ == pState_->pCharacterStateList_.at(DIE)) {
		SAFE_DELETE(pAttackCollision_);
		SAFE_DELETE(pBodyCollision_);
	}

	SAFE_DELETE(pState_);

	
	
}

// 別のcolliderに衝突したときに呼ばれる関数
void Character::OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType)
{
	//死んでいたら判定しない様に
	if (status_.dead) {
		return;
	}

	//壁にぶつかったら前にいた座標に戻す
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BROCK) {
		SetPosition(prevPos_);
	}

	//ノックバック中は当たり判定を無くす
	if (pState_->pCharacterStateList_.at(KNOCKBACK) == pState_->characterState_)
		return;

	//球に当たった時の処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_BULLET) {

		HitDamage(static_cast<Bullet*>(pTarget)->GetAttackPower());

		SetTargetRotate(pTarget->GetRotate());

		pState_->ChangeState(KNOCKBACK);

	}

	//トゲに当たった時の処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_OBSTRYCTION) {
		HitDamage(static_cast<Needle*>(pTarget)->GetNeedlePower());
	}

	//攻撃に当たったときの処理
	if (myType == COLLIDER_BODY && targetType == COLLIDER_ATTACK)
	{
		//敵の方向に向きなおす
		SetTargetRotate(pTarget->GetRotate());
		pState_->ChangeState(KNOCKBACK);

		//攻撃を食らったのがEnemyの場合、一定確率で狙いを攻撃してきた相手に変える
		ChangeTarget(pTarget);

		//その攻撃でやられたら、相手のキルポイントを増やす
		if (HitDamage(((Character*)pTarget)->GetStatus().attackPower)) {
			Status status = ((Character*)pTarget)->GetStatus();
			status.killPoint++;
			((Character*)pTarget)->SetStatus(status);
			((Character*)pTarget)->TellStatus();
			DieEffect();
		}
		else {
			HitEffect();
		}
	}
}

// 攻撃に当たった時にHPを減らす関数
// 引数：食らったダメージ量
// 戻り値：そのダメージで死亡したらtrue
bool Character::HitDamage(int damage)
{
	status_.hp -= damage;
	pPlayerUI_->SetNowHp(status_.hp);

	//HPが0になったら
	if (status_.hp <= 0) {
		status_.dead = true;
		Audio::Play(hSoundEffect_[DEAD]);
		return status_.dead;
	}

	Audio::Play(hSoundEffect_[HIT]);
	return status_.dead;
}

// ステータスをゲーム開始時にリセットする関数（winPointはそのまま）
void Character::ResetStatus()
{
	EraseCollider(COLLIDER_ATTACK);
	EraseCollider(COLLIDER_BODY);

	//開始地点に移動する
	SetPosition(startPos_);

	//addcolliderしたら勝手に開放されるからね
	AddCollider(pBodyCollision_, ColliderAttackType::COLLIDER_BODY);

	status_.hp = CHARACTER_HP;
	status_.dead = false;
	status_.killPoint = ZERO;
	status_.trapKillPoint = ZERO;

	pPlayerUI_->SetMaxHp(status_.hp, CHARACTER_HP);

	TellStatus();

	ChangeState(IDLE);
}

//描画を止める
void Character::StopDraw()
{
	Visible();
	pPlayerUI_->StopDraw();
}

//描画を許可する
void Character::StartDraw()
{
	Invisible();
	pPlayerUI_->StartDraw();
}

//UIの描画を止める
void Character::StopDrawUI()
{
	pPlayerUI_->StopDraw();
}

//ステータスのdeadをtrueにする（未使用）
void Character::Dead()
{
	status_.dead = true;
}


// 現在のstateを変える
// 引数：次のstate
void Character::ChangeState(CharacterStateList nextState)
{
	pState_->ChangeState(nextState);
}

//プレイヤーUIの場所をセットする
void Character::SetUIPos(XMFLOAT3 pos)
{
	pPlayerUI_->SetPlayerUIPos(pos);
}

//キャラクターの名前をセットする
void Character::SetCharacterName(std::string name)
{
	status_.playerName = name;
	pPlayerUI_->SetPlayerName(name);
}

//攻撃を食らった時のエフェクト
void Character::HitEffect()
{
	using namespace HitEffectData;

	//火の粉
	EmitterData data;
	data.textureFileName = FILENAME;
	data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
	data.positionRnd = POSITIONRND;
	data.direction = targetRot_;
	data.directionRnd = DIRECTIONRND;
	data.speed = SPEED;
	data.speedRnd = SPEEDRND;
	data.color = COLOR;
	data.deltaColor = DELTACOLOR;
	data.size = HitEffectData::SIZE;
	data.sizeRnd = SIZERND;
	data.scale = SCALE;
	data.lifeTime = LIFETIME;
	data.delay = DELAY;
	data.number = NUMBER;

	
	VFX::Start(data);
}

//死んだ時にでるエフェクト
void Character::DieEffect()
{

	using namespace DieEffect;

	EmitterData data;

	//炎（爆発本体）
	{
		using namespace Explosion;

		data.textureFileName = FILENAME;
		data.position = XMFLOAT3(transform_.position_.x, transform_.position_.y + 1.5f, transform_.position_.z);
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.size = Explosion::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;

		VFX::Start(data);
	}
	

	//火の粉
	{
		using namespace FireSpark;

		data.positionRnd = POSITIONRND;
		data.direction = DIRECTION;
		data.directionRnd = DIRECTIONRND;
		data.speed = SPEED;
		data.speedRnd = SPEEDRND;
		data.accel = FireSpark::ACCEL;
		data.gravity = GRAVITY;
		data.color = COLOR;
		data.deltaColor = DELTACOLOR;
		data.size = FireSpark::SIZE;
		data.sizeRnd = SIZERND;
		data.scale = SCALE;
		data.lifeTime = LIFETIME;
		data.delay = DELAY;
		data.number = NUMBER;

		VFX::Start(data);
	}

}


