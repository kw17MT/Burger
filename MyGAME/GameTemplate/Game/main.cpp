#include "stdafx.h"
#include "system/system.h"
#include "Level.h"
#include "ModelRender.h"
#include "Light.h"
#include <string>
#include "FontRender.h"
#include "SpriteRender.h"
#include "Guzai.h"
#include "math.h"
#include "ObjectGene.h"
#include "Kitchen.h"
#include "Counter.h"

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

	//�f�B���N�V�������C�g�A�|�C���g���C�g
	//�ꏏ�����ɂ��Ȃ��Ɨ����̃��C�g�̉e�����󂯂Ȃ��Ȃ�B
	
	g_lig.DirDirection = { 0.5f,-1.0f,0.0f };
	g_lig.DirDirection.Normalize();
	g_lig.DirColor = { 1.0f,1.0f,1.0f };
	g_lig.eyePos = g_camera3D->GetPosition();
	
	//�|�C���g���C�g
	g_lig.ptPosition = { 0.0f, 300.0f,0.0f };
	g_lig.ptColor = { 100.0f, 50.0f,100.0f };
	g_lig.ptRange = 300.0f;

	//�X�|�b�g���C�g
	g_lig.spDirection = { 1.0f,-1.0f,0.0f };
	g_lig.spDirection.Normalize();
	
	g_lig.spAngle = Math::DegToRad(30.0f);


	//���C�g�p
	/*ModelInitData lightdata;
	lightdata.m_tkmFilePath = "Assets/modelData/light.tkm";

	lightdata.m_fxFilePath = "Assets/shader/model.fx";

	lightdata.m_expandConstantBuffer = &g_lig;
	lightdata.m_expandConstantBufferSize = sizeof(g_lig);

	Model Light;
	Light.Init(lightdata);*/

	//�����̕`��///////////////////////////////////////////////////////////////////////
	FontRender SCORE01;
	FontRender SCORE02;
	FontRender TIME;
	FontRender timer;
	
	NewGO<FontRender>(0);
	///////////////////////////////////////////////////////////////////////////////////


	//�����̍��W�����₷�����邽�߂̂���
	NewGO<Kitchen>(0, "kitchen");

	//�摜�̕`��///////////////////////////////////////////////////////////////////////
	SpriteRender* sp[3];
	
	for (int i = 0; i < 3; i++) {
		sp[i] = NewGO<SpriteRender>(2);
		sp[i]->Init("Assets/image/menu.dds", 128, 256);
		Vector3 pos = { -150.0f,-200.0f,0.0f };
		pos.x += i * 150.0f;
		sp[i]->SetPosition(pos);
	}
	//////////////////////////////////////////////////////////////////////////////////////


	//���x���\���p////////////////////////////////////////////////////////////////////////
	Level level;
	level.Init("Assets/level/level001.tkl", [&](ObjectData& objectData) {return false;});
	//////////////////////////////////////////////////////////////////////////////////////


	//�v���C���[�̃��f�����쐬x2//////////////////////////////////////////////////////////
	ModelRender* player[2];
	player[0] = NewGO<ModelRender>(0,"player01");
	player[0]->SetPlayerNo(1);
	player[1] = NewGO<ModelRender>(0,"player02");
	player[1]->SetPlayerNo(2);
	//////////////////////////////////////////////////////////////////////////////////////


	//��ނƃo�t���쐬////////////////////////////////////////////////////////////////////
	ObjectGene* generator;
	generator = NewGO<ObjectGene>(1, "gene");
	//////////////////////////////////////////////////////////////////////////////////////
	
	//�J�E���^�[�̍쐬////////////////////////////////////////////////////////////////////
	Counter* co;
	co = NewGO<Counter>(1,"counter");
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
		level.Draw();
		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		Quaternion RotY;
		RotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.03f);
		RotY.Apply(g_lig.spDirection);

		Vector3 rotAxis;
		rotAxis.Cross(g_vec3AxisY, g_lig.spDirection);
		Quaternion rotX;
		rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * -0.03f);
		rotX.Apply(g_lig.spDirection);

		//g_lig.ptPosition.x -= g_pad[0]->GetLStickXF() * 5.0f;
		//g_lig.ptPosition.z -= g_pad[0]->GetLStickYF() * 5.0f;

		/*Light.Draw(renderContext);
		Light.UpdateWorldMatrix(g_lig.ptPosition, g_quatIdentity, g_vec3One);*/

	

		//�J�����̈ړ�
		float move = g_pad[0]->GetRStickYF() * 30.0f;
		Vector3 camerapos = g_camera3D->GetPosition();
		camerapos.y -= move;
		g_camera3D->SetPosition(camerapos);

		//Light.Draw(renderContext);
		//level.Draw();

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

