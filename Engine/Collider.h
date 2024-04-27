#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <../../Global.h>


using namespace DirectX;

//�N���X�̑O���錾
class GameObject;
class BoxCollider;
class SphereCollider;

//�����蔻��̃^�C�v
enum ColliderType
{
	COLLIDER_BOX,		//���^
	COLLIDER_CIRCLE		//����
};

//�ǂ��̓����蔻�肩(�̂��U�����肩)
enum ColliderAttackType 
{
	COLLIDER_BODY,				//��
	COLLIDER_ATTACK,			//�̂ł̍U��(����Ƃ�)
	COLLIDER_WEAPON,			//����ł̍U��
	COLLIDER_BROCK,				//�u���b�N�̃I�u�W�F�N�g
	COLLIDER_OBSTRYCTION,		//�g�Q���̃I�u�W�F�N�g
	COLLIDER_OBJ_ATTACK			//���ł̍U��
};

//3�����̃x�N�g��
enum ColliderVec {
	VEC_X,
	VEC_Y,
	VEC_Z,
	VEC_NUM
};

//-----------------------------------------------------------
//�����蔻����Ǘ�����N���X(������������g�p)
//�Q�l�ɂ����T�C�g�Fhttp://marupeke296.com/COL_3D_No13_OBBvsOBB.html
//-----------------------------------------------------------
class Collider
{
	//���ꂼ��̃N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class BoxCollider;
	friend class SphereCollider;

protected:
	GameObject*		pGameObject_;					//���̔���������Q�[���I�u�W�F�N�g
	ColliderType	type_;							//���
	ColliderAttackType attackType_;					//�ǂ��̓����蔻�肾������
	XMVECTOR		center_;						//���S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	XMVECTOR		directionNormalVec_[VEC_NUM];	//�e���x�N�g���i�e���̕������w���j
	float			length_[VEC_NUM];				//����T�C�Y(�e���̃x�N�g���̒���)

	XMFLOAT3		rotate_;				//�R���C�_�[���̂ɐݒ肳�ꂽ��]
	XMFLOAT3		size_;					//�R���C�_�[��size
	
	int				hDebugModel_;			//�f�o�b�O�\���p�̃��f����ID

public:
	//�R���X�g���N�^
	Collider();

	//�f�X�g���N�^
	virtual ~Collider();

	//�ڐG����i�p�����SphereCollider��BoxCollider�ŃI�[�o�[���C�h�j
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	virtual bool IsHit(Collider* target) = 0;

	//���^���m�̏Փ˔���
	//�����FboxA	�P�ڂ̔��^����
	//�����FboxB	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//���^�Ƌ��̂̏Փ˔���
	//�����Fbox	���^����
	//�����Fsphere	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//���̓��m�̏Փ˔���
	//�����FcircleA	�P�ڂ̋��̔���
	//�����FcircleB	�Q�ڂ̋��̔���
	//�ߒl�F�ڐG���Ă����true
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	// �����F�������ƂȂ�x�N�g��
	// �����F��ڂ̕����x�N�g��
	// �����F��ڂ̕����x�N�g��
	// �����F�O�ڂ̕����x�N�g���i�K�v�Ȃ�j
	float LenSegOnSeparateAxis(XMVECTOR* Sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3 = 0);

	//�e���̕����x�N�g�����v�Z
	void Calclation();

	//�e�X�g�\���p�̘g��`��
	//�����Fposition	�I�u�W�F�N�g�̈ʒu
	void Draw(XMFLOAT3 position);

	//////////�A�N�Z�X�֐�////////////
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }
	void SetAttackType(ColliderAttackType type) { attackType_ = type; }
	void SetCenter(XMFLOAT3 center);
	void SetSize(XMFLOAT3 size);
	void SetRotate(XMFLOAT3 rotate);

	ColliderAttackType GetAttackType() { return attackType_; }
	XMVECTOR GetDirect(int elem) { return directionNormalVec_[elem]; }   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen(int elem) { return length_[elem]; }          // �w�莲�����̒������擾
	XMVECTOR GetCenter() { return center_; }             // ���S���擾

};

