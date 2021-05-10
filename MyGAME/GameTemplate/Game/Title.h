#pragma once
#include"SpriteRender.h"

class Fade;

class Title : public IGameObject
{
public:
	Title() {}
	~Title();
	//�����������B
	bool Start();
	//�X�V�����B
	void Update();
private:
	SpriteRender* m_spriteRender;
	Fade* m_fade = nullptr;
};