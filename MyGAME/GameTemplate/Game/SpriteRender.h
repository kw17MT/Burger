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

	/**
	 * @brief �摜�̏��������s��
	 * @param name �t�@�C���p�X�̖��O
	 * @param width ����
	 * @param height �c��
	*/
	void Init(const char* name, int width, int height);

	void SetPosition(Vector3 pos) { m_pos = pos; }
	void SetScale(Vector3 scale) {m_scale = scale;}
	void SetRotation(Quaternion& rot) { m_Rot = rot; }
	void SetPivot(Vector2 pivot) { m_pivot = pivot; }
	//�J���[�ύX(Vector4��)
	void SetColor(const Vector4& color) { m_sprite.ColorUpdate(color); }
	//�J���[�ύX(float��)
	void SetColor(const float& r,const float& g,const float& b,const float& a) { m_sprite.ColorUpdate(r,g,b,a); }
	void Render(RenderContext& rc) { m_sprite.Draw(rc); }
};


