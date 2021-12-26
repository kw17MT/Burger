#pragma once
class SpriteRender;
class EmotionCry : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	bool m_isExpand = true;
public:
	EmotionCry() {}
	~EmotionCry();
	bool Start();
	void Update();
	void SetPosition(Vector3 pos) { m_position = pos; }
private:
	SpriteRender* m_cry = nullptr;
};

