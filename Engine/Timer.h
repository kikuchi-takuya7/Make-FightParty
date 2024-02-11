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

	void SetLimit(float seconds);

	void Start();

	void Stop();

	void Reset();

	void StartDraw();

	void StopDraw();
	
	bool IsFinished();



private:
	
	int flame_;
	int startFlame_;
	bool activeUpdate_;
	bool activeDraw_;
	float drawX_;
	float drawY_;
	Text* num_;

	

};

