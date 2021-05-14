#pragma once
class SpriteRender : public IGameObject
{
private:
	Sprite m_sprite;
	SpriteInitData m_spriteData;

	Vector3 m_pos;
	Vector3 m_scale = { 1.0f, 1.0f, 1.0f };
	Quaternion m_Rot = Quaternion::Identity;
	Vector2 m_pivot = { 0.5f,0.5f };

public:
	SpriteRender() {};

	void Update();

	/// <summary>
	/// ����������֐��B
	/// </summary>
	/// <param name="name">�摜�̃p�X</param>
	/// <param name="a">�\�����鉡��</param>
	/// <param name="b">�\������c��</param>
	void Init(const char* name, int a, int b);

	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetScale(Vector3 scale) {m_scale = scale;}
	void SetPivot(Vector2 pivot) { m_pivot = pivot; }
	//�J���[�ύX(Vector4��)
	void SetColor(const Vector4& color) { m_sprite.ColorUpdate(color); }
	//�J���[�ύX(float��)
	void SetColor(const float& r,const float& g,const float& b,const float& a) { m_sprite.ColorUpdate(r,g,b,a); }
	void Render(RenderContext& rc) { m_sprite.Draw(rc); }
};


