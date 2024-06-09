#include "EasingFunction.h"

namespace LinearInterpolate {

	/// <summary>
	/// ���`��Ԃ��g�����݂̒l�����߂�֐�
	/// </summary>
	/// <param name="begin">�͂��߂̒l</param>
	/// <param name="end">�I���̒l</param>
	/// <param name="rate">���[�g(0�`1)</param>
	/// <returns></returns>
	float GetRateValue(float begin, float end, float rate)
	{
		//1�ȏ�Ȃ�1�ɖ߂�.RateFrame�N���X���g���ă��[�g���Ǘ����Ă��炢��Ȃ�����K�v�Ȃ������H
		if (rate > 1.0f) {
			rate = 1.0f;
		}
		return (end - begin) * rate + begin;
	}

	/// <summary>
	/// ���[�g�ɉ����Ċ��炩�Ɉړ�������֐�
	/// </summary>
	/// <param name="position">���݂̍��W</param>
	/// <param name="lastPos">�ŏI�̍��W</param>
	/// <param name="moveRate">���݂̃��[�g�l(0�`1)</param>
	/// <returns>�ړ���̒l</returns>
	XMFLOAT3 RateMovePosition(XMFLOAT3 position, XMFLOAT3 lastPos, float moveRate)
	{
		position.x = GetRateValue(position.x, lastPos.x, moveRate);
		position.y = GetRateValue(position.y, lastPos.y, moveRate);
		position.z = GetRateValue(position.z, lastPos.z, moveRate);

		return position;
	}
}