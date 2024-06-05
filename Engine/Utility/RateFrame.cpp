#include "RateFrame.h"

namespace RateFrame {
	
	map<string, RateData> data;

	void SetData(string s, float rate, bool isUpdate)
	{
		data.insert(std::make_pair(s, RateData(rate, isUpdate)));
	}

	void SetFlag(string s, bool isUpdate)
	{
		data.at(s).isUpdate = isUpdate;
	}

	float GetNowFrame(string s)
	{
		return data.at(s).frame;
	}

	void Update()
	{
		//map�̑S�Ă��X�V
		for (auto it = data.begin(); it != data.end(); it++) {

			//�X�V���邩�ǂ����𕷂�
			if (it->second.isUpdate) {
				it->second.frame += it->second.rate;

				//1�ȏ�Ȃ�1�ɖ߂�
				if (it->second.frame > 1.0f) {
					it->second.frame = 1.0f;
				}
			}
		}
	}

	void Release(string s)
	{
		data.erase(s);
	}

	void Release()
	{
		data.clear();
	}
	
}

