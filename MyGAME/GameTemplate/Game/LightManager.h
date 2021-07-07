#pragma once

struct AllLight
{
	//�f�B���N�V�������C�g
	Vector3 directionalDirection = { 0.0f,1.0f,0.0f };				//�f�B���N�V�������C�g�̕���
	float pad0;
	Vector3 directionalColor = { 10.0f, 10.0f, 10.0f };				//�f�B���N�V�������C�g�̐F
	float pad1;
	Vector3 eyePos = Vector3::Zero;									//�ڂ̈ʒu�i�J�����̈ʒu�j
	float specPow = 0.5f;											//���˂̓x����
	//����
	Vector3 ambientLight = { 0.6f, 0.6f, 0.6f };					//����
};

class LightManager : public IGameObject
{
private:
	static LightManager* instance;
	AllLight s_allLight;
public:
	LightManager();
	/**
	 * @brief �C���X�^���X�����
	*/
	static LightManager CreateInstance()
	{
		instance = new LightManager;
	}

	/**
	 * @brief �C���X�^���X���擾����
	 * @return �V���O���g���C���X�^���X
	*/
	static LightManager& GetInstance()
	{
		static LightManager instance;
		return instance;
	}

	/**
	 * @brief �C���X�^���X���폜����B
	*/
	static LightManager DeleteInstance()
	{
		delete instance;
	}

	AllLight& GetLightData()
	{
		return s_allLight;
	}

	void UpdateEyePos()
	{
		s_allLight.eyePos = g_camera3D->GetPosition();
	}
};

