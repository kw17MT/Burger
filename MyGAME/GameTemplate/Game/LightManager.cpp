#include "stdafx.h"
#include "LightManager.h"

LightManager::LightManager()
{
	//�f�B���N�V�������C�g�̐��K��
	s_allLight.directionalDirection.Normalize();
	//���_�i���C���J�����̈ʒu�j
	s_allLight.eyePos = g_camera3D->GetPosition();
}
