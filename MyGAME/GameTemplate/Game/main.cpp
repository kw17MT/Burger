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
	//g_lig.directionalLight.color = { 5.0f, 5.0f, 5.0f };
	//�|�X�g�G�t�F�N�g�̃e�X�g�p�B�ォ���������
	g_postLig.directionalLight.direction.Normalize();
	//g_postLig.directionalLight.direction.y = -1.0f
	g_postLig.directionalLight.color = { 20.0f, 20.0f, 20.0f };
	//////////////////////////////////////////////////////////////////////////////////////
	
	//�v���C���[�A�����A�I�u�W�F�N�g�Ȃǂ̐���////////////////////////////////////////////
	//NewGO<Game>(0, "game");
	NewGO<Title>(0, "title");
	//////////////////////////////////////////////////////////////////////////////////////
	
	
	

	////�e�`��p�̃��C�g�J�������쐬����B			�Z
	//Camera lightCamera;
	////�J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu�B
	//lightCamera.SetPosition(0, 500, 0);
	////�J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ�B
	//lightCamera.SetTarget(0, 0, 0);
	////�������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���B
	//lightCamera.SetUp({ 1, 0, 0 });
	////���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���B
	//lightCamera.Update();


	////�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����B			�Z
	//float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//RenderTarget shadowMap;
	//shadowMap.Create(
	//	1024,
	//	1024,
	//	1,
	//	1,
	//	DXGI_FORMAT_R8G8B8A8_UNORM,
	//	DXGI_FORMAT_D32_FLOAT,
	//	clearColor
	//);

	////�V���h�E�}�b�v�ɕ`�悷�郂�f��������������B		�Z
	//ModelInitData teapotShadowModelInitData;
	////�V���h�E�}�b�v�`��p�̃V�F�[�_�[���w�肷��B
	//teapotShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
	//teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//Model teapotShadowModel;
	//teapotShadowModel.Init(teapotShadowModelInitData);
	//teapotShadowModel.UpdateWorldMatrix(
	//	{ 0, 50, 0 },
	//	g_quatIdentity,
	//	g_vec3One
	//);


	///*�@	�~
	//�����܂ŗp�ӂł������̂ŉe���Ƃ����߂�model.Draw(rc, camera)������B
	//model���ォ�猩���Ƃ��̊D�F�摜��shadowTarget��p���Ĉڂ��B*/



	////�ʏ�`��̃e�B�[�|�b�g���f�����������B
	//Model teapotModel;
	//teapotShadowModelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//teapotShadowModelInitData.m_expandConstantBuffer = &g_lig;
	//teapotShadowModelInitData.m_expandConstantBufferSize = sizeof(g_lig);
	//teapotModel.Init(teapotShadowModelInitData);
	//teapotModel.UpdateWorldMatrix(
	//	{ 0, 50, 0 },
	//	g_quatIdentity,
	//	g_vec3One
	//);

	////step-1 �e���󂯂�w�i���f�����������B			
	//ModelInitData bgModelInitData;
	////�V���h�E���V�[�o�[(�e�����Ƃ���郂�f��)�p�̃V�F�[�_�[���w�肷��B
	//bgModelInitData.m_fxFilePath = "Assets/shader/ShadowReciever.fx";
	////�V���h�E�}�b�v���g��SRV�ɐݒ肷��B
	//bgModelInitData.m_expandShaderResoruceView = &shadowMap.GetRenderTargetTexture();
	////���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�ɐݒ肷��B
	//bgModelInitData.m_expandConstantBuffer = (void*)&lightCamera.GetViewProjectionMatrix();
	//bgModelInitData.m_expandConstantBufferSize = sizeof(lightCamera.GetViewProjectionMatrix());
	//bgModelInitData.m_tkmFilePath = "Assets/modelData/Floor.tkm";

	//Model bgModel;
	//bgModel.Init(bgModelInitData);


	

	
	
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







		/*renderContext.WaitUntilToPossibleSetRenderTarget(shadowMap);
		renderContext.SetRenderTargetAndViewport(shadowMap);
		renderContext.ClearRenderTargetView(shadowMap);


		teapotShadowModel.Draw(renderContext, lightCamera);


		renderContext.WaitUntilFinishDrawingToRenderTarget(shadowMap);


		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		renderContext.SetViewport(g_graphicsEngine->GetFrameBufferViewport());


		teapotModel.Draw(renderContext);

		bgModel.Draw(renderContext);*/






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

