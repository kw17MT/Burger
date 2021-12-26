#pragma once
class SpriteRender;

class EmotionSmile : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;

	float m_angle = 0.0f;
	bool m_turnLikeWatch = true;
public:
	EmotionSmile() {}
	~EmotionSmile();
	bool Start();
	void Update();
	void SetPosition(Vector3 pos) { m_position = pos; }
private:
	SpriteRender* m_smile = nullptr;
};

