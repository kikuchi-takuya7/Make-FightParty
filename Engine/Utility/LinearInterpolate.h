#pragma once
#include <DirectXMath.h>
#include "../Direct3D.h"

namespace LinearInterpolate {

	float GetRateValue(float begin, float end, float rate)
	{
		//1�ȏ�Ȃ�1�ɖ߂�.RateFrame�N���X���g���ă��[�g���Ǘ����Ă��炢��Ȃ�����K�v�Ȃ������H
		if (rate > 1.0f) {
			rate = 1.0f;
		}
		return (end - begin) * rate + begin;
	}

	XMFLOAT3 RateMovePosition(XMFLOAT3 position, XMFLOAT3 lastPos, float moveRate)
	{
		position.x = GetRateValue(position.x, lastPos.x, moveRate);
		position.y = GetRateValue(position.y, lastPos.y, moveRate);
		position.z = GetRateValue(position.z, lastPos.z, moveRate);	

		return position;
	}
}