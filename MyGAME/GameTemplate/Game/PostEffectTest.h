#pragma once
class RenderContext;

class PostEffectTest : public IGameObject
{
private:
	ModelInitData modelData;
	Model model;
	CharacterController m_charaCon;
	Skeleton m_skeleton;

	Vector3 m_pos = { 0.0f,0.0f,0.0f };
	Quaternion m_rot = Quaternion::Identity;
	Vector3 m_scale = { 1.0f,1.0f,1.0f };

	//�ȉ�GameObjectManager�ŏ������A���s�������́B
	//RootSignature root;
	////�ʏ�̃����_�����O�Ώ�
	//RenderTarget mainRenderTarget;
	////�P�x���o�p�̃����_�����O�Ώ�
	//RenderTarget luminanceRenderTarget;
	////�P�x�ˑ��̂ڂ�����K�������摜�p
	//SpriteInitData luminanceSpriteData;
	//Sprite luminanceSprite;

	////�쐬�\��
	////�K�E�V�A���u���[�������邽�߂̂��́B
	//GaussianBlur gaussianBlur;

	//SpriteInitData finalSpriteData;
	//Sprite finalSprite;

	//SpriteInitData copyToFrameBufferSpriteData;
	//Sprite copyToFrameBufferSprite;

	//RenderContext& renderContext = g_graphicsEngine->GetRenderContext();

public:
	PostEffectTest() {}
	~PostEffectTest() {}

	bool Start();
	void Update();

	void Render(RenderContext& rc) { model.Draw(rc); }
};

