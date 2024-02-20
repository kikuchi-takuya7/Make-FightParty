#pragma once
#include "GameObject.h"

class Text;

class Timer :
	public GameObject 
{
public:

	Timer(GameObject* parent);
	~Timer();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	//タイマーセット
	void SetLimit(float seconds);

	//タイマースタート
	void Start();

	//タイマーストップ
	void Stop();

	//タイマーリセット（ストップもされる）
	void Reset();

	//Drawする
	void StartDraw();

	//Drawしない
	void StopDraw();
	
	//終わったらtrue
	bool IsFinished();

	/////////////アクセス関数///////////////////

	int GetNowFlame() { return flame_; }

private:
	
	int flame_;
	int startFlame_;
	float drawX_;
	float drawY_;
	Text* num_;

	

};

