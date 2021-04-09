#include "stdafx.h"
#include "PostEffectTest.h"

bool PostEffectTest::Start()
{
	modelData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modelData.m_fxFilePath = "Assets/shader/model.fx";

	modelData.m_vsEntryPointFunc = "VSMain";
	modelData.m_vsSkinEntryPointFunc = "VSSkinMain";

	modelData.m_modelUpAxis = enModelUpAxisZ;

	modelData.m_expandConstantBuffer = &g_lig;
	modelData.m_expandConstantBufferSize = sizeof(g_lig);

	modelData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modelData.m_skeleton = &m_skeleton;

	// �����_�����O����J���[�o�b�t�@�[�̃t�H�[�}�b�g���w�肷��
	//modelData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	model.Init(modelData);
	m_charaCon.Init(0.0f, 0.0f, m_pos);

	return true;
}

void PostEffectTest::Update()
{
	m_skeleton.Update(model.GetWorldMatrix());
	//Vector3 move0 = { 0.0f,0.0f,0.0f };
	//m_pos = m_charaCon.Execute( move0, 1.0f);
	model.UpdateWorldMatrix(m_pos, g_quatIdentity, g_vec3One);
	//RenderContext renderContext;
	//model.Draw(renderContext);
}