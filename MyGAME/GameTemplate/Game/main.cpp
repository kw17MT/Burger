#include "stdafx.h"
#include "system/system.h"
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
	
	//�v���C���[�A�����A�I�u�W�F�N�g�Ȃǂ̐���
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
		//�I�u�W�F�N�g�̃A�b�v�f�[�g�֐�����C�ɍs��
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//�I�u�W�F�N�g�̃h���[���s��
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

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
			b.x -= 20.0f;
			g_camera3D->SetPosition(a);
			g_camera3D->SetTarget(b);
		}
		if (g_pad[0]->IsPress(enButtonDown)) {
			Vector3 a = g_camera3D->GetPosition();
			a.x += 20.0f;
			Vector3 b = g_camera3D->GetTarget();
			b.x += 20.0f;
			g_camera3D->SetPosition(a);
			g_camera3D->SetTarget(b);
		}
		if (g_pad[0]->IsPress(enButtonX)) {
			Vector3 a = g_camera3D->GetPosition();
			a.z -= 20.0f;
			g_camera3D->SetPosition(a);
		}
		if (g_pad[0]->IsPress(enButtonY)) {
			Vector3 a = g_camera3D->GetPosition();
			a.z += 20.0f;
			g_camera3D->SetPosition(a);
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

		//�Q�[���^�C����p���ăG�t�F�N�g�̍Đ��i�s�x�̍X�V
		EffectEngine::GetInstance()->Update(GameTime().GetFrameDeltaTime());
		//�G�t�F�N�g�̕`��
		EffectEngine::GetInstance()->Draw();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	//�T�E���h�G���W���̏���
	CSoundEngine::DeleteInstance();
	return 0;
}