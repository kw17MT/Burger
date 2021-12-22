#pragma once
class SpriteRender;

class ToTitleSprite : public IGameObject
{
private:
	float m_alpha = 0.0f;
	bool m_addAlpha = true;
public:
	ToTitleSprite() {}
	~ToTitleSprite();
	bool Start();
	void Update();
private:
	SpriteRender* m_sprite = nullptr;
};

