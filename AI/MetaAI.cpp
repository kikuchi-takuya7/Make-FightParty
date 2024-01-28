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
	//最初は誰が一位でも同じ
	No1CharaID_.push_back(0);
}

void MetaAI::Release()
{
}

//狙うべき相手を決める関数
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % 3;

	//殴られた相手を狙う可能性も残したい

	//自分が1位だった場合0に固定する（同率でも）
	if (characterStatusList_.at(No1CharaID_.at(0)).winPoint == characterStatusList_.at(ID).winPoint) {

		targetFrag = 0;
	}

	//全体を見て一位のプレイヤーを優先的に狙うように
	switch (targetFrag)
	{

	//プレイヤーの中からランダムで狙う	
	case 0:
		while (true)
		{
			//狙った相手が自分じゃなければ
			int targetID = rand() % characterStatusList_.size();
			if (targetID != ID)
				return targetID;
		}
		break;
	
	//一位の中から誰かを狙う
	case 1:
	case 2:
		while (true)
		{
			//狙った相手が自分じゃなければ
			int targetID = rand() % No1CharaID_.size();
			if (targetID != ID)
				return targetID;
		}
		break;

	default:
		break;
	}

	return 0;

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
