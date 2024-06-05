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
		//mapの全てを更新
		for (auto it = data.begin(); it != data.end(); it++) {

			//更新するかどうかを聞く
			if (it->second.isUpdate) {
				it->second.frame += it->second.rate;

				//1以上なら1に戻す
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

