#pragma once
#include "Path.h"

enum EnLane
{
	enNonLane = -1,
	enNormalLane = 0,		//���ʂ̃��[���B
	enLaneNum = 1			//���[���̐��B
};

class PathFactory
{
private:
	PathFactory();
	~PathFactory() {}
	static PathFactory* instance;
public:
	static PathFactory& GetInstance()
	{
		static PathFactory instance;
		return instance;
	}
	Path* GetPath(EnLane enLane)
	{
		return &m_pathVector[enLane];
	}

private:
	std::vector<Path> m_pathVector;
};

