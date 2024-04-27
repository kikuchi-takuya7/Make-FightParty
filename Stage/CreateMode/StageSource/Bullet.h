#pragma once
#include "../../../Engine/GameObject.h"
#include "StageSourceBase.h"

/// <summary>
/// Cannon�N���X�����g�����̃N���X�B�����蔻��̑傫�����͂��ꂼ��̐e�N���X�Ŏw�肵�Ă��炤
/// </summary>
class Bullet : public StageSourceBase
{
public:

	//�R���X�g���N�^
	Bullet(GameObject* parent);
	~Bullet();


	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	//�`��
	void ChildDraw() override;

	//�J��
	void ChildRelease() override;

	void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed);

	void SetStartRot(float rotY);


private:

	//�ړ���������
	float moveLen_;

	//���f���ԍ�
	int bulletModel_;
	
	//���̃X�s�[�h
	float bulletSpeed_;

	//���˂��ꂽ���̑�C�̊p�x
	float startRotateY_;

	XMVECTOR vec_;

	//�C��̔��肩��Ɨ������邽�߂̕ϐ�
	Transform bulletTrans_;

	SphereCollider* collider_;



};