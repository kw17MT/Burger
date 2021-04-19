#include "stdafx.h"
#include "PopUp2D.h"
#include "ModelRender.h"

bool PopUp2D::Start()
{
	//�v���C���[������
	m_player01 = FindGO<ModelRender>("player01");
	m_player02 = FindGO<ModelRender>("player02");

	//���f���̏���������
	//�������p�f�[�^�̍\�z
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/popup/press_a_flat.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	m_model.Init(modeldata);
	//�������I���//

	m_scale *= 10.0f;

	return true;
}

void PopUp2D::Update()
{
	//�r���{�[�h�I�ȏ���
	//�J�����ʒu���擾
	Vector3 toCameraPos = g_camera3D->GetPosition();
	toCameraPos.Normalize();
	float angle = atan2(toCameraPos.x, toCameraPos.z);
	m_rotation.SetRotation(Vector3::AxisZ, angle);


	//�\���e�X�g(P1�̕t�߂ɕ\���A�Ǐ])
	Vector3 posToPlayer = { -200.0f,100.0f,0.0f };
	//�v���C���[�ʒu���擾
	Vector3 position = m_player01->GetPosition();

	m_position = position + posToPlayer;
	
	//m_rotation.SetRotationDeg(Vector3::AxisX, 90.0f);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}