#pragma once
#include "../../../Engine/GameObject.h"
#include "StageSourceBase.h"

/// <summary>
/// Cannon�N���X�����g�����̃N���X�B�����蔻��̑傫�����͂��ꂼ��̐e�N���X�Ŏw�肵�Ă��炤
/// </summary>
class Bullet : public GameObject
{
public:

	//�R���X�g���N�^
	Bullet(GameObject* parent);
	~Bullet();


	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget, ColliderAttackType myType, ColliderAttackType targetType) override;

	/// <summary>
	/// ��C�̏����Z�b�g
	/// </summary>
	/// <param name="collider">���̓����蔻��</param>
	/// <param name="type">�R���C�_�[�̃^�C�v</param>
	/// <param name="attackPower">��C�̍U����</param>
	/// <param name="speed">���̃X�s�[�h</param>
	/// <param name="rotY">���𔭎˂������̃I�u�W�F�N�g�̊p�x</param>
	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed, float rotY);


	//�A�N�Z�X�֐�
	int GetBulletPower() { return attackPower_; }
	int GetAuthorID() { return authorID_; }
	void SetAuthorID(int id) { authorID_ = id; }


private:

	//�ړ���������
	float moveLen_;

	//���f���ԍ�
	int bulletModel_;
	
	//���̃X�s�[�h
	float bulletSpeed_;

	//���˂��ꂽ���̑�C�̊p�x
	float startRotateY_;

	//���̍U����
	int attackPower_;

	//���̃I�u�W�F�N�g�𐶐������v���C���[��ID
	int authorID_;

	//�������˂�������̃x�N�g��
	XMVECTOR forwardVec_;

	//�C��̔��肩��Ɨ������邽�߂̕ϐ�
	Transform bulletTrans_;

	SphereCollider* collider_;



};