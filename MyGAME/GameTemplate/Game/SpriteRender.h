#pragma once
class SpriteRender : public IGameObject
{
private:
	Sprite m_sprite;
	SpriteInitData m_spriteData;

	Vector3 m_Pos;
	Vector3 m_Scale = { 1.0f, 1.0f, 1.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector2 m_Pivot = { 0.5f,0.5f };

public:
	SpriteRender() {};
	/// <summary>
	/// ����������֐��B
	/// </summary>
	/// <param name="name">�摜�̃p�X</param>
	/// <param name="a">�\�����鉡��</param>
	/// <param name="b">�\������c��</param>
	void Init(const char* name, int a, int b);

	void SetPosition(Vector3 pos){ m_sprite.Update(pos, m_Rot, m_Scale, m_Pivot); }
	void SetScale(Vector3 scale) { m_sprite.Update(m_Pos, m_Rot, scale, m_Pivot); }
	
	void Render(RenderContext& rc) { m_sprite.Draw(rc); }
};


