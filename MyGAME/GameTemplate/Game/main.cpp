#include "stdafx.h"
#include "system/system.h"

#include "Light.h"
#include "Game.h"
#include "Title.h"


// �E�B���h�E�v���O�����̃��C���֐��B
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//�T�E���h��炷�p�̃C���X�^���X
	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();

	//�ꏏ�����ɂ��Ȃ��Ɨ����̃��C�g�̉e�����󂯂Ȃ��Ȃ�B////////////////////////////////
	//�f�B���N�V�������C�g�̐��K���Ɩڂ̈ʒu���J�����̍��W�ɂ���B
	g_lig.directionalLight.direction.Normalize();
	//�|�X�g�G�t�F�N�g�̃e�X�g�p�B�ォ���������
	g_postLig.directionalLight.direction.Normalize();
	g_postLig.directionalLight.color = { 100.0f,100.0f,100.0f };
	//////////////////////////////////////////////////////////////////////////////////////
	
	//�v���C���[�A�����A�I�u�W�F�N�g�Ȃǂ̐���////////////////////////////////////////////
	//NewGO<Game>(0, "game");
	NewGO<Title>(0, "title");
	//////////////////////////////////////////////////////////////////////////////////////
	

	
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);
		
		g_lig.eyePos = g_camera3D->GetPosition();
		g_postLig.eyePos = g_camera3D->GetPosition();
		
		/*Quaternion RotY;
		RotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.03f);
		RotY.Apply(g_lig.spDirection);

		Vector3 rotAxis;
		rotAxis.Cross(g_vec3AxisY, g_lig.spDirection);
		Quaternion rotX;
		rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * -0.03f);
		rotX.Apply(g_lig.spDirection);*/

		//�J�����̈ړ�
		if (g_pad[0]->GetRStickYF()) {
			float move = g_pad[0]->GetRStickYF() * 30.0f;
			Vector3 camerapos = g_camera3D->GetPosition();
			Vector3 cameraTarget = g_camera3D->GetTarget();


			

			camerapos.z -= move;
			g_camera3D->SetPosition(camerapos);

			cameraTarget.z -= move;
			g_camera3D->SetTarget(cameraTarget);
			
		}
		if (g_pad[0]->GetRStickXF()) {
			float move = g_pad[0]->GetRStickXF() * 30.0f;
			Vector3 camerapos = g_camera3D->GetPosition();
			Vector3 cameraTarget = g_camera3D->GetTarget();

			

			camerapos.x -= move;
			g_camera3D->SetPosition(camerapos);
			cameraTarget.x -= move;
			g_camera3D->SetTarget(cameraTarget);
		}
		if (g_pad[0]->IsPress(enButtonSelect)) {
			float move = 30.0f;
			Vector3 camerapos = g_camera3D->GetPosition();
		
			camerapos.y -= move;
			g_camera3D->SetPosition(camerapos);
		}
		if (g_pad[0]->IsPress(enButtonStart)) {
			float move = 30.0f;
			Vector3 camerapos = g_camera3D->GetPosition();

			camerapos.y += move;
			g_camera3D->SetPosition(camerapos);
		}

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	CSoundEngine::DeleteInstance();
	return 0;
}

