#include "stdafx.h"
#include "system/system.h"

#include "Light.h"
#include "Game.h"
#include "Title.h"
#include "effect/Effect.h"

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

	//�G�t�F�N�g���o���C���X�^���X
	EffectEngine::CreateInstance();

	//�Q�[���^�C���𑪂����
	CStopwatch stopWatch;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �e�`��p�̃��C�g�J�������쐬����
	Camera lightCamera;
	lightCamera.SetPosition(0, 1500, 0);
	lightCamera.SetTarget(0, 0, 0);
	lightCamera.SetUp({ 1, 0, 0 });
	lightCamera.Update();
	// �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	RenderTarget shadowMap;
	shadowMap.Create(
		1024,
		1024,
		1,
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_FORMAT_D32_FLOAT,
		clearColor
	);

	RenderTarget a = *GameObjectManager::GetInstance()->GetShadowMap();
	Camera b = *GameObjectManager::GetInstance()->GetLightCamera();

	// �V���h�E�}�b�v�ɕ`�悷�郂�f��������������
	ModelInitData shadowTestData;
	shadowTestData.m_fxFilePath = "Assets/shader/drawShadowMap.fx";
	shadowTestData.m_tkmFilePath = "Assets/modelData/Chef/ChefRed/Chef01.tkm";

	Model shadowTest;
	shadowTest.Init(shadowTestData);
	shadowTest.UpdateWorldMatrix(
		{ 0, 50, 0 },
		g_quatIdentity,
		g_vec3One
	);

	// step-1 �e���󂯂�w�i���f����������
	ModelInitData bgModelData;
	bgModelData.m_tkmFilePath = "Assets/modelData/floor/floor_red.tkm";
	bgModelData.m_fxFilePath = "Assets/shader/shadowReciever.fx";
	//�����I�����e�̃e�N�X�`���������Ă���
	bgModelData.m_expandShaderResoruceView = /*&a.GetRenderTargetTexture();*/&shadowMap.GetRenderTargetTexture();
	bgModelData.m_expandConstantBuffer = (void*)/*&b.GetViewProjectionMatrix();*/&lightCamera.GetViewProjectionMatrix();
	bgModelData.m_expandConstantBufferSize = sizeof(/*b.GetViewProjectionMatrix()*/lightCamera.GetViewProjectionMatrix());

	Model floor;
	floor.Init(bgModelData);

	
	//�ꏏ�����ɂ��Ȃ��Ɨ����̃��C�g�̉e�����󂯂Ȃ��Ȃ�B////////////////////////////////
	//�f�B���N�V�������C�g�̐��K���Ɩڂ̈ʒu���J�����̍��W�ɂ���B
	g_lig.directionalLight.direction.Normalize();
	//////////////////////////////////////////////////////////////////////////////////////
	
	//�v���C���[�A�����A�I�u�W�F�N�g�Ȃǂ̐���////////////////////////////////////////////
	NewGO<Title>(0, "title");
		
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

		//���C�g�J�������A�b�v�f�[�g���Ă݂Ă�
		//GameObjectManager::GetInstance()->GetLightCamera()->Update();

		//////////////////////////////////////////////////////////////////////////////////////////////////


		//renderContext.WaitUntilToPossibleSetRenderTarget(shadowMap);
		//renderContext.SetRenderTargetAndViewport(shadowMap);
		//renderContext.ClearRenderTargetView(shadowMap);

		//// �e���f����`��
		//shadowTest.Draw(renderContext, lightCamera);

		//// �������݊����҂�
		//renderContext.WaitUntilFinishDrawingToRenderTarget(shadowMap);

		//// �ʏ탌���_�����O
		//// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�[�ɖ߂�
		//renderContext.SetRenderTarget(
		//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		//);
		//renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

		//// step-2 �e���󂯂�w�i��`��
		//floor.Draw(renderContext);



		//�J�����̈ړ�
		if (g_pad[0]->IsPress(enButtonLeft)) {
			Vector3 a = g_camera3D->GetPosition();
			a.y -= 20.0f;
			g_camera3D->SetPosition(a);			
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			Vector3 a = g_camera3D->GetPosition();
			a.y += 20.0f;
			g_camera3D->SetPosition(a);
		}
		if (g_pad[0]->IsPress(enButtonUp)) {
			Vector3 a = g_camera3D->GetPosition();
			Vector3 b = g_camera3D->GetTarget();
			a.z -= 20.0f;
			b.z -= 20.0f;
			g_camera3D->SetPosition(a);
			g_camera3D->SetTarget(b);
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			Vector3 a = g_camera3D->GetPosition();
			a.z += 20.0f;
			Vector3 b = g_camera3D->GetTarget();
			b.z += 20.0f;
			g_camera3D->SetPosition(a);
			g_camera3D->SetTarget(b);
		}

		//�X�s�����b�N���s���B
		int restTime = 0;
		do {
			stopWatch.Stop();
			restTime = 16 - (int)stopWatch.GetElapsedMillisecond();
		} while (restTime > 0);
		//�X�g�b�v�E�H�b�`�̌v���I��
		stopWatch.Stop();
		//�f���^�^�C�����X�g�b�v�E�H�b�`�̌v�����Ԃ���A�v�Z����
		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());

		EffectEngine::GetInstance()->Update(GameTime().GetFrameDeltaTime());
		EffectEngine::GetInstance()->Draw();

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

