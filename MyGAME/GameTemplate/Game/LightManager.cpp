#include "stdafx.h"
#include "LightManager.h"

LightManager::LightManager()
{
	//�f�B���N�V�������C�g�̐��K��
	//s_allLight.directionalLight.directionalDirection.Normalize();
	s_allLight.directionalDirection.Normalize();
	//���_�i���C���J�����̈ʒu�j
	//s_allLight.directionalLight.eyePos = g_camera3D->GetPosition();
	s_allLight.eyePos = g_camera3D->GetPosition();
	//�X�|�b�g���C�g2��ނ̏������A���K��
	s_allLight.spotDirection.Normalize();
	/*s_allLight.spotLight0.spotPosition = { 1000.0f, 300.0f, 0.0f };
	s_allLight.spotLight1.spotPosition = { -1000.0f,300.0f,0.0f };
	s_allLight.spotLight0.spotDirection = { -1.0f, -1.0f, 0.0 };
	s_allLight.spotLight0.spotDirection.Normalize();
	s_allLight.spotLight1.spotDirection = { 1.0f, -1.0f, 0.0 };
	s_allLight.spotLight1.spotDirection.Normalize();
	s_allLight.spotLight0.spotColor = { 1.0f,0.0f,0.0f };
	s_allLight.spotLight1.spotColor = { 0.0f,0.0f,1.0f };*/
}
