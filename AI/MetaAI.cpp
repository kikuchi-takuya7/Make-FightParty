#include "MetaAI.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Engine/Camera.h"

MetaAI::MetaAI(GameObject* parent)
	:AI(parent, "MetaAI"), pNavigationAI_(nullptr), No1CharaID_(0),characterStatusList_(0)
{
}

MetaAI::~MetaAI()
{
}

void MetaAI::Initialize()
{

	//最初は誰が一位でも同じ
	No1CharaID_.emplace_back(ZERO);
}

void MetaAI::Release()
{
}

//狙うべき相手を決める関数
int MetaAI::Targeting(int ID)
{
	int targetFrag = rand() % 3;

	//自分が1位だった場合0に固定する（同率でも）
	if (characterStatusList_.at(No1CharaID_.at(ZERO)).winPoint == characterStatusList_.at(ID).winPoint) {

		targetFrag = 0;
	}

	//全体を見て一位のプレイヤーを優先的に狙うように
	switch (targetFrag)
	{

	//キャラクターの中からランダムで狙う	
	case 0:
		while (true)
		{
			int targetID = rand() % characterStatusList_.size();

			//狙った相手が自分じゃなければ
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
	int No1WinPoint = ZERO;
	int sameRateChara = ZERO;
	
	vector<pair<int,int>> ranking;

	//ソートする用の配列に入れる
	for (int i = ZERO; i < characterStatusList_.size(); i++) {

		//キャラのステータスとIDを入れる（リストに入ってる順番がそのままIDになってる）
		ranking.emplace_back(std::make_pair(characterStatusList_.at(i).winPoint,i));
	}

	//降順でソートする
	std::sort(ranking.rbegin(), ranking.rend());

	//一位のポイントとIDを覚えておく
	No1WinPoint = ranking.at(ZERO).first;
	No1CharaID_.emplace_back(ranking.at(ZERO).second);
	sameRateChara++;

	for (int i = 1; i < ranking.size(); i++) {

		//一位の人と同じポイントなら
		if (No1WinPoint == characterStatusList_.at(i).winPoint) {

			sameRateChara++;
			No1CharaID_.emplace_back(ranking.at(i).second);
		}
		else {
			//二位以下は探索しない
			break;
		}
	}

	
}

void MetaAI::NextGame()
{
	
	int deadNum = 0;
	
	//死んでる人数を数える
	for (int i = 0; i < characterStatusList_.size(); i++) {
		if (characterStatusList_.at(i).dead) {
			deadNum++;
		}
	}

	//3人以上死んでいたら
	if (deadNum >= 3 && pCreateMode_->GetState() == NONE) {
		pCreateMode_->ToSelectMode();
	}

	//デバック用
	if (Input::IsKeyDown(DIK_1) && pCreateMode_->GetState() == NONE) {
		pCreateMode_->ToSelectMode();
	}
}

void MetaAI::GameCameraSet()
{
	Camera::SetPosition(XMFLOAT3(15, 10, -20));
	Camera::SetTarget(XMFLOAT3(15, 0, 15));
}
