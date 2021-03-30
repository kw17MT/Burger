#pragma once

//#include "Font.h"

class FontRender : public IGameObject
{
private:
	void Render(RenderContext& rc);

	Font m_font;
	std::wstring m_text;					//!<�e�L�X�g�B
	const wchar_t* m_textUnsafe = nullptr;	//!<�A���Z�[�t�ł̃e�L�X�g�B
	Vector2 m_position = Vector2::Zero;	//!<���W�Bx = 0.0f, y = 0.0f�ŉ�ʂ̒��S�B
	Vector4 m_color = Vector4::White;		//!<�J���[�B
	float m_rotation = 0.0f;				//!<��]�B
	float m_scale = 1.0f;					//!<�g�嗦�B
	Vector2 m_pivot;						//!<�s�{�b�g�B

public:
	void SetPosition(const Vector2& pos);
	void SetRotation(float rotation);
	void SetScale(float scale);

	void SetText(const wchar_t* text);

	
	
	void SetColor(const Vector3& color);
	void SetColor(const Vector4& color);
	void AddColorPoint(Vector4 colorPoint);
	Vector4 GetColor() { return m_color; }
	float GetColorVolume();
	void  AddFontScale(float size);

	void SetPivot(const Vector2& pivot);
};

