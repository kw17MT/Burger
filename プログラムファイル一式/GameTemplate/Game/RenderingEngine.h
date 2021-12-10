#pragma once
#include "postEffect.h"
#include "ForwardBloom.h"

enum EnRenderTypes
{
	enRenderNormal,							//�ʏ�`��
	enRenderShade,							//�e�̕`��
	enRenderLuminance,						//�P�x�̕`��
	enRenderUI								//UI�̕`��
};

class RenderingEngine
{
	static RenderingEngine* instance;
public:
	RenderingEngine();
	/**
	 * @brief �C���X�^���X�̎擾
	 * @return ��ފǗ��̃C���X�^���X
	*/
	static RenderingEngine& GetInstance()
	{
		static RenderingEngine instance;
		return instance;
	}

	/**
	 * @brief �C���X�^���X�̍쐬
	*/
	static void CreateInstance()
	{
		instance = new RenderingEngine;
	}

	/**
	 * @brief �C���X�^���X�̍폜
	*/
	static void DeleteInstance()
	{
		delete instance;
	}

	Camera& GetLightCamera()
	{
		return lightCamera;
	}

	const EnRenderTypes& GetRenderTypes() const
	{
		return m_renderTypes;
	}

	void SetRenderTypes(EnRenderTypes TypeNumber)
	{
		m_renderTypes = TypeNumber;
	}

	void PrepareRender();

	void InitRenderTarget();

	void InitSprite();

	void InitLightCamera();

	void CreateShadowMap(RenderContext& rc);
	void CreateDeffered(RenderContext& rc);
	void CreateMainRenderTarget(RenderContext& rc);
	void CreateForwardBloom(RenderContext& rc);
	void CreateUI(RenderContext& rc);

	void Render(RenderContext& rc);

private:
	//�w��̂��̂������_�����O����B
	EnRenderTypes m_renderTypes = enRenderNormal;
	//���C�������_�[�^�[�Q�b�g
	RenderTarget mainRenderTarget;
	//�t���[���o�b�t�@�ɃR�s�[���Ă����摜�̓\��t��
	SpriteInitData finalSpriteData;
	Sprite finalSprite;
	//�V���h�E�֘A
	float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
	RenderTarget shadowMap;
	//���C�g���W���猩���e����邽�߂̂���
	Camera lightCamera;
	//�f�B�t�@�[�h�����_�����O�֘A
	//�A���x�h�}�b�v
	RenderTarget albedoMap;
	//�@���}�b�v
	RenderTarget normalMap;
	//���[���h���W�}�b�v
	RenderTarget specAndDepthMap;
	RenderTarget* defferedTargets[3] = { &albedoMap, &normalMap, &specAndDepthMap };
	//�f�B�t�@�[�h���C�e�B���O�쐬�̉摜
	SpriteInitData defferedSpriteData;
	Sprite defferedSprite;
	//�t�H���[�h�����_�����O�p�̃u���[���쐬�^�[�Q�b�g
	RenderTarget forwardBloomTarget;
	//���ʂɃt�H���[�h�����_�����O�Ńu���[���������������̂����邽��
	ForwardBloom m_forwardBloom;
	//�|�X�g�G�t�F�N�g���܂Ƃ߂�����
	PostEffect m_postEffect;

	GaussianBlur shadowBlur;
};

