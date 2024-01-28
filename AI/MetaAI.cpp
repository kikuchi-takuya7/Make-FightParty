#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"

MetaAI::MetaAI():pNavigationAI_(nullptr)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{
}

void MetaAI::Release()
{
}

int MetaAI::Targeting(int ID)
{
	Status tmp = characterStatusList_.at(ID);

	int targetFrag = rand() % 3;

	switch (targetFrag)
	{

		//一位の中から誰かを狙う
	case 0:
	case 1:
		return rand() % No1CharaID_.size();
		break;

		//プレイヤの中からランダムで狙う
	case 2:
		return rand() % 4;
	
	default:
		break;
	}

}

void MetaAI::CheckNo1Chara()
{

	//一位のポイントとそれと同じ点数が何人いるか
	int No1WinPoint = 0;
	int sameRateChara = 0;
	
	vector<pair<int,int>> ranking;

	//ソートする用の配列に入れる
	for (int i = 0; i < characterStatusList_.size(); i++) {

		//キャラのステータスとIDを入れる（リストに入ってる順番がそのままIDになってる）
		ranking.push_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//降順でソートする
	std::sort(ranking.rbegin(), ranking.rend());

	//一位のポイントとIDを覚えておく
	No1WinPoint = ranking.at(0).first;
	No1CharaID_.push_back(ranking.at(0).second);
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//一位の人と同じポイントなら
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
			No1CharaID_.push_back(ranking.at(i).second);
		}
		else {
			//二位以下は探索しない
			break;
		}
	}

	
}
