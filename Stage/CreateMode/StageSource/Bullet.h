#pragma once
#include "../../../Engine/GameObject.h"


/// <summary>
/// Cannon�N���X�����g�����̃N���X�B�����蔻��̑傫�����͂��ꂼ��̐e�N���X�Ŏw�肵�Ă��炤
/// </summary>
class Bullet : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
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

	void SetBulletData(SphereCollider* collider, ColliderAttackType type, int attackPower, float speed);
	

	int GetAttackPower() { return attackPower_; }

private:

	//�ړ���������
	float moveLen_;

	//���f���ԍ�
	int hModel_;

	//�U����
	int attackPower_;
	
	//���̃X�s�[�h
	float bulletSpeed_;

};