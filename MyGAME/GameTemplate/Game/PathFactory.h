#pragma once
#include "Path.h"

enum EnLane
{
	enNonLane = -1,
	enNormalLane = 0,		//���ʂ̃��[���B
	enDeBuffLane = 1,		//�f�o�t�A�C�e���̃��[���B
	enLaneNum = 2		//���[���̐��B
};

class PathFactory
{
private:
	PathFactory();
	~PathFactory() {}

public:
	static PathFactory& GetInstance()
	{
		static PathFactory instance;
		return instance;
	}
	Path* GetPath(EnLane enLane, const int guzaiNo)
	{
		return &m_pathVector[guzaiNo - 1][enLane];
	}

private:
	std::vector<Path> m_pathVector[2];
};

