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
	COLLIDER_BODY,			//��
	COLLIDER_ATTACK,		//�̂ł̍U��(����Ƃ�)
	COLLIDER_WEAPON,		//����ł̍U��(�C��̋���������)
	COLLIDER_BROCK,			//�u���b�N�̃I�u�W�F�N�g
	COLLIDER_OBSTRYCTION,	//�g�Q���̃I�u�W�F�N�g

};

//-----------------------------------------------------------
//�����蔻����Ǘ�����N���X
//-----------------------------------------------------------
class Collider
{
	//���ꂼ��̃N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class BoxCollider;
	friend class SphereCollider;

protected:
	GameObject*		pGameObject_;	//���̔���������Q�[���I�u�W�F�N�g
	ColliderType	type_;			//���
	ColliderAttackType attackType_;	//�ǂ��̓����蔻�肾������
	XMFLOAT3		center_;		//���S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	XMFLOAT3		size_;			//����T�C�Y�i���A�����A���s���j
	XMFLOAT3		rotate_;		//center�����]������p�x�B�Ǝv�������ǌ��ǂ��̎l�p�`�̌`�̂܂ܓ������炿���Ɖ�]���Ă�킯�ł͂Ȃ��B
	//std::string		colliderName_;	//�R���C�_�[���̖��O�B������R���C�_�[���ɕς���p
	int				hDebugModel_;	//�f�o�b�O�\���p�̃��f����ID

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

	/// <summary>
	/// ��]�������pos���v�Z����
	/// </summary>
	/// <returns>��]���center</returns>
	XMFLOAT3 CalclationCenter();

	/// <summary>
	/// ��]�������Size���v�Z����i���ۂɂ͉�]���Ă��ł͖���������ۂ��ړ����Ă邾��������������������Ȃ��j
	/// </summary>
	/// <returns>��]���Size</returns>
	XMFLOAT3 CalclationSize();

	//�e�X�g�\���p�̘g��`��
	//�����Fposition	�I�u�W�F�N�g�̈ʒu
	void Draw(XMFLOAT3 position);

	//////////�A�N�Z�X�֐�////////////
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }
	//void SetName(std::string name) { colliderName_ = name; }
	void SetAttackType(ColliderAttackType type) { attackType_ = type; }
	void SetCenter(XMFLOAT3 center) { center_ = center; }
	void SetSize(XMFLOAT3 size) { size_ = size; }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	//std::string GetName() { return colliderName_; }
	ColliderAttackType GetAttackType() { return attackType_; }
	XMFLOAT3 GetCenter() { return center_; }
	XMFLOAT3 GetSize() { return size_; }
	XMFLOAT3 GetRotate() { return rotate_; }

};

