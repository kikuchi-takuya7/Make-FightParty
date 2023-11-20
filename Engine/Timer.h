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

	bool IsFinished();

private:
	
	int frame;
	bool active;
	float drawX;
	float drawY;
	Text* num;

};

