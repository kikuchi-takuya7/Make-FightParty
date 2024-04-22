#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "Global.h"

//�R���X�g���N�^
Collider::Collider():
	pGameObject_(nullptr)
{
}

//�f�X�g���N�^
Collider::~Collider()
{
}

//���^���m�̏Փ˔���
//�����FboxA	�P�ڂ̔��^����
//�����FboxB	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{
	//���[���h���W��rotate���m��
	XMFLOAT3 rotA = boxA->pGameObject_->GetRotate();
	XMFLOAT3 rotB = boxB->pGameObject_->GetRotate();

	// �e�����x�N�g���̊m�ہ@�W�������ꂽ�����x�N�g��
    //�iN***:�W���������x�N�g���j
	XMVECTOR NAe1 = boxA->GetDirect(VEC_X);
	XMVECTOR NAe2 = boxA->GetDirect(VEC_Y);
	XMVECTOR NAe3 = boxA->GetDirect(VEC_Z);
	XMVECTOR NBe1 = boxB->GetDirect(VEC_X);
	XMVECTOR NBe2 = boxB->GetDirect(VEC_Y);
	XMVECTOR NBe3 = boxB->GetDirect(VEC_Z);

	//����ɒ����������Ė{���̒����ɖ߂����x�N�g��
	XMVECTOR Ae1 = NAe1 * boxA->GetLen_W(VEC_X);
	XMVECTOR Ae2 = NAe2 * boxA->GetLen_W(VEC_Y);
	XMVECTOR Ae3 = NAe3 * boxA->GetLen_W(VEC_Z);
	XMVECTOR Be1 = NBe1 * boxB->GetLen_W(VEC_X);
	XMVECTOR Be2 = NBe2 * boxB->GetLen_W(VEC_Y);
	XMVECTOR Be3 = NBe3 * boxB->GetLen_W(VEC_Z);
	
	//��̔��̒��S�_�Ԃ̋��������߂鏀��
	XMVECTOR aCenter = XMVector3TransformCoord(boxA->GetPos_W(), boxA->pGameObject_->GetWorldMatrix());
	XMVECTOR bCenter = XMVector3TransformCoord(boxB->GetPos_W(), boxB->pGameObject_->GetWorldMatrix());
	XMVECTOR Interval = aCenter - bCenter; 
	
	float tes1 = Length(XMVector3TransformCoord(boxA->GetPos_W(), boxA->pGameObject_->GetWorldMatrix()));
	float tes2 = Length(XMVector3TransformCoord(boxB->GetPos_W(), boxB->pGameObject_->GetWorldMatrix()));

	// ������ : Ae1 ��A�̕����x�N�g���ƕ������Ƃ̓��ς�2�����Ɣ��a���̕�������̒��������߂��āA����̍��v��L��蒷���Ȃ�Ԃ����Ă�\������
	float rA = Length(Ae1);
	float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	float L = fabs(Length(XMVector3Dot(Interval, NAe1)));
	if (L > rA + rB)
		return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = Length(Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, NAe2)));
	if (L > rA + rB)
		return false;

	// ������ : Ae3
	rA = Length(Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, NAe3)));
	if (L > rA + rB)
		return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Length(Be1);
	L = fabs(Length(XMVector3Dot(Interval, NBe1)));
	if (L > rA + rB)
		return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Length(Be2);
	L = fabs(Length(XMVector3Dot(Interval, NBe2)));
	if (L > rA + rB)
		return false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Length(Be3);
	L = fabs(Length(XMVector3Dot(Interval, NBe3)));
	if (L > rA + rB)
		return false;

	// ������ : C11
	XMVECTOR Cross;
	Cross = XMVector3Cross(NAe1, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C12
	Cross = XMVector3Cross(NAe1, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C13
	Cross = XMVector3Cross(NAe1, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C21
	Cross = XMVector3Cross(NAe2, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C22
	Cross = XMVector3Cross(NAe2, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C23
	Cross = XMVector3Cross(NAe2, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C31
	Cross = XMVector3Cross(NAe3, NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C32
	Cross = XMVector3Cross(NAe3, NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// ������ : C33
	Cross = XMVector3Cross(NAe3, NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(Length(XMVector3Dot(Interval, Cross)));
	if (L > rA + rB)
		return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

//���^�Ƌ��̂̏Փ˔���
//�����Fbox	���^����
//�����Fsphere	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	/*XMFLOAT3 circlePos = Float3Add(sphere->pGameObject_->GetWorldPosition(), sphere->CalclationCenter());
	XMFLOAT3 boxPos = Float3Add(box->pGameObject_->GetWorldPosition(), box->CalclationCenter());



	if (circlePos.x > boxPos.x - box->size_.x - sphere->size_.x &&
		circlePos.x < boxPos.x + box->size_.x + sphere->size_.x &&
		circlePos.y > boxPos.y - box->size_.y - sphere->size_.x &&
		circlePos.y < boxPos.y + box->size_.y + sphere->size_.x &&
		circlePos.z > boxPos.z - box->size_.z - sphere->size_.x &&
		circlePos.z < boxPos.z + box->size_.z + sphere->size_.x )
	{
		return true;
	}*/

	return false;
}

//���̓��m�̏Փ˔���
//�����FcircleA	�P�ڂ̋��̔���
//�����FcircleB	�Q�ڂ̋��̔���
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	/*XMFLOAT3 centerA = circleA->CalclationCenter();
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->CalclationCenter();
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}*/

	return false;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
// �����F�������ƂȂ�x�N�g��
// �����F�������Ƃ̊p�x�𑪂��ڂ̕����x�N�g��
// �����F��ڂ̕����x�N�g��
// �����F�O�ڂ̕����x�N�g���i�K�v�Ȃ�j
float Collider::LenSegOnSeparateAxis(XMVECTOR* Sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
    // ������Sep�͕W��������Ă��邱��
	float r1 = fabs(Length(XMVector3Dot(*Sep, *e1)));
	float r2 = fabs(Length(XMVector3Dot(*Sep, *e2)));
	float r3 = e3 ? (fabs(Length(XMVector3Dot(*Sep, *e3)))) : 0;
	return r1 + r2 + r3;
}

//�e�x�N�g�����v�Z
void Collider::Calclation()
{
	XMFLOAT3 rot = pGameObject_->GetRotate() + rotate_;

	//rotate����e���̒P�ʃx�N�g�����擾(X,Y,Z)
	XMVECTOR vec = XMVectorSet(1, ZERO, ZERO, ZERO);
	directionNormalVec_[VEC_X] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationX(XMConvertToRadians(rot.x))));
	vec = XMVectorSet(ZERO, 1, ZERO, ZERO);
	directionNormalVec_[VEC_Y] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationY(XMConvertToRadians(rot.y))));
	vec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	directionNormalVec_[VEC_Z] = XMVector3Normalize(XMVector3TransformCoord(vec, XMMatrixRotationZ(XMConvertToRadians(rot.z))));

}

//�e�X�g�\���p�̘g��`��
//�����Fposition	�I�u�W�F�N�g�̈ʒu
void Collider::Draw(XMFLOAT3 position)
{
	Transform transform;

	transform.position_ = VectorToFloat3(XMVector3TransformCoord(center_, pGameObject_->GetWorldMatrix()));
	transform.rotate_ = pGameObject_->GetRotate() + rotate_;
	transform.scale_ = size_ * 2;

	//transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}

void Collider::SetCenter(XMFLOAT3 center)
{
	center_ = XMLoadFloat3(&center);
}

void Collider::SetSize(XMFLOAT3 size)
{
	//�e�������x�N�g���̒�����size����m��
	length_[VEC_X] = size.x / 2;
	length_[VEC_Y] = size.y / 2;
	length_[VEC_Z] = size.z / 2;

	size_ = size / 2;
}

void Collider::SetRotate(XMFLOAT3 rotate)
{

	XMFLOAT3 rot = pGameObject_->GetRotate() + rotate;

	//rotate����e���̒P�ʃx�N�g�����擾(X,Y,Z)
	XMVECTOR vec = XMVectorSet(1, ZERO, ZERO, ZERO);
	directionNormalVec_[VEC_X] = XMVector3TransformCoord(vec, XMMatrixRotationX(XMConvertToRadians(rot.x)));
	vec = XMVectorSet(ZERO, 1, ZERO, ZERO);
	directionNormalVec_[VEC_Y] = XMVector3TransformCoord(vec, XMMatrixRotationY(XMConvertToRadians(rot.y)));
	vec = XMVectorSet(ZERO, ZERO, 1, ZERO);
	directionNormalVec_[VEC_Z] = XMVector3TransformCoord(vec, XMMatrixRotationZ(XMConvertToRadians(rot.z)));

	rotate_ = rotate;
}
