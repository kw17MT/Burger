#pragma once
class SpriteRender;
class Level2D;
class Result;
#include "Level2D.h"

class MissCounter : public IGameObject
{
private:
	int pl1MissCount = 0;
	int pl2MissCount = 0;

	bool pl1Win = false;
	bool pl2Win = false;

	bool shouldChangeFilePath = false;

	bool isGameSet = false;
public:
	~MissCounter();
	bool Start();
	void Update();

	void AddPl1MissCount() { pl1MissCount++; }
	void AddPl2MissCount() { pl2MissCount++; }

	void ChangeMarkState(bool state) { shouldChangeFilePath = state; }

	Level2D m_level2D;		//���x��2D�B
	Result* m_result[2] = {nullptr};
	SpriteRender* m_spriteRender[6];
};

