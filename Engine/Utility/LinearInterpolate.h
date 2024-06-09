#pragma once
#include <DirectXMath.h>
#include "../Direct3D.h"

namespace LinearInterpolate {

	/// <summary>
	/// ���`��Ԃ��g�����݂̒l�����߂�֐�
	/// </summary>
	/// <param name="begin">�͂��߂̒l</param>
	/// <param name="end">�I���̒l</param>
	/// <param name="rate">���[�g(0�`1)</param>
	/// <returns></returns>
	float GetRateValue(float begin, float end, float rate);

	/// <summary>
	/// ���[�g�ɉ����Ċ��炩�Ɉړ�������֐�(position���X�V��������Ȃ�萔�œ��������^���ɂȂ�)
	/// </summary>
	/// <param name="position">���݂̍��W</param>
	/// <param name="lastPos">�ŏI�̍��W</param>
	/// <param name="moveRate">���݂̃��[�g�l(0�`1)</param>
	/// <returns>�ړ���̒l</returns>
	XMFLOAT3 RateMovePosition(XMFLOAT3 position, XMFLOAT3 lastPos, float moveRate);
}