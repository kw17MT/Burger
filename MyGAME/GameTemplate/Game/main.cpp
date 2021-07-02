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
			a.x -= 20.0f;
			b.z -= 20.0f;
			g_camera3D->SetPosition(a);
			//g_camera3D->SetTarget(b);
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			Vector3 a = g_camera3D->GetPosition();
			a.x += 20.0f;
			Vector3 b = g_camera3D->GetTarget();
			b.z += 20.0f;
			g_camera3D->SetPosition(a);
			//g_camera3D->SetTarget(b);
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