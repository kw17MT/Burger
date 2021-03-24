#pragma once
class SpriteRender;
#include "Level2D.h"

/// <summary>
/// ���x��2D�����̃T���v���N���X�B
/// </summary>
class CLevel2D : public IGameObject
{
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	//�s�v
	//Level2D����n���ꂽname(�p�X�̈ꕔ�j��p����SpriteRender�Ŏg��const char*�^�����B
	//const char* MakePathFromName(const char* name);
private:
	Level2D m_level2D;		//���x��2D�B
	//Sprite m_sprite;			//�X�v���C�g�B
	Vector3 m_position;		//���W�B
	Vector3 m_scale;		//�傫���B

	SpriteRender* sprite[3];
};