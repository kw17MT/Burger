#include "stdafx.h"
#include "PopUp2D.h"
//#include "ModelRender.h"
#include "Guzai.h"
#include "Kitchen.h"
#include "Counter.h"
#include<vector>

bool PopUp2D::Start()
{
	////���g�̏�Ԃɉ����Č���������̂�����(�f�t�H���g��P1)
	//if (m_self == enPlayer01 && m_player == nullptr) {
	//	m_player = FindGO<ModelRender>("player01");
	//	m_kitchen = FindGO<Kitchen>("kitchen01");
	//	m_counter = FindGO<Counter>("counter01");
	//}
	//else if(m_self == enPlayer02 && m_player == nullptr){
	//	m_player = FindGO<ModelRender>("player02");
	//	m_kitchen = FindGO<Kitchen>("kitchen02");
	//	m_counter = FindGO<Counter>("counter02");
	//}
	//else {
	//	//�������Ȃ�
	//}

	//m_guzai = FindGO<Guzai>("guzai");

	//���f���̏���������
	//�������p�f�[�^�̍\�z
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/popup/invisible.tkm"; //�s���̃|���S���ɂ��Ă���
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	m_model.Init(modeldata);
	//�������I���//

	//�g�嗦��ݒ�
	m_scale *= 7.0f;

	return true;
}

void PopUp2D::Move()
{
	////���s�ړ�
	////�\���e�X�g(P1�̕t�߂ɕ\���A�Ǐ])
	//Vector3 posToPlayer = { 200.0f,100.0f,0.0f };
	////�v���C���[�ʒu���擾
	//Vector3 position = m_player->GetPosition();
	//m_position = position + posToPlayer;
}

void PopUp2D::Rotation()
{
	//�J�����ʒu�ɍ��킹�Ċp�x���ς�鏈��
	//x����]
	Quaternion rotX;
	//�J�����ʒu���擾
	Vector3 CameraPos = g_camera3D->GetPosition();
	//���g����J�����ʒu�ւ̃x�N�g��
	Vector3 toCameraPos = CameraPos - m_position;
	toCameraPos.Normalize();
	float angleX = atan2(toCameraPos.z, toCameraPos.y);
	if (angleX > 0.0f * PI) {
		angleX = 0.0f;
	}
	rotX.SetRotation(Vector3::AxisX, angleX);
	m_rotation = rotX;

	//�����̂Ƃ�x����]�����ł��悳����
	////z����]
	//Quaternion rotZ;
	////����ݒ�
	//Vector3 AxisZ = Cross(toCameraPos, Vector3::AxisY);
	//float angleZ = atan2(toCameraPos.x, toCameraPos.z);
	//if (angleZ < 0.0f * PI) {
	//	angleZ = 0.0f;
	//}
	//rotZ.SetRotation(AxisZ, angleZ);
	//m_rotation = rotZ;

	////�����p�N�H�[�^�j�I��
	//Quaternion mulRot;
	//mulRot *= rotX;
	//mulRot *= rotZ;
	//
	//m_rotation = mulRot;

}

void PopUp2D::ChangeState()
{
	
}

void PopUp2D::ChangeModel()
{
	ModelInitData modeldata;

	switch (m_state) {
	case enNone:
		modeldata.m_tkmFilePath = "Assets/modelData/popup/invisible.tkm";
		break;
	case enNearFood:
		modeldata.m_tkmFilePath = "Assets/modelData/popup/press_a_get.tkm";
		break;
	case enDisposable:
		modeldata.m_tkmFilePath = "Assets/modelData/popup/hold_x_disposal.tkm";
		break;
	
	default:
		break;
	}

	modeldata.m_fxFilePath = "Assets/shader/model.fx";
	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";
	modeldata.m_modelUpAxis = enModelUpAxisY;
	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);
	
	m_model.Init(modeldata);
}

void PopUp2D::Update()
{
	/*vecGuzaiSize = vecGuzai.size();

	if (vecGuzaiSize > MAXSIZE) {
		vecGuzai.erase(vecGuzai.begin());
	}*/
	
	//m_guzai = FindGO<Guzai>("guzai");
	////vecGuzai.push_back(m_guzai);


	//if (m_guzai != nullptr && m_guzai->GetGuzaiToPlayer() != 0.0f) {
	//	if (m_guzai->GetGuzaiToPlayer() < 200.0f && m_state == enNone) {
	//		ChangeModel("Assets/modelData/popup/press_a_get.tkm", "Assets/shader/model.fx");
	//		m_state = enNearFood;
	//	}
	//	else if (m_guzai->GetGuzaiToPlayer() >= 200.0f && m_state != enNone) {
	//		ChangeModel("Assets/modelData/popup/invisible.tkm", "Assets/shader/model.fx");
	//		m_state = enNone;
	//	}
	//}

	//�e�X�g:�蓮��]�p
	/*if (g_pad[0]->IsPress(enButtonRight)) {
		rotX += 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonLeft)) {
		rotX -= 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonUp)) {
		rotY += 1.0f;
	}
	else if (g_pad[0]->IsPress(enButtonDown)) {
		rotY -= 1.0f;
	}*/

	//m_rotation.SetRotationDeg(Vector3::AxisZ, rotX);
	//m_rotation.SetRotationDeg(Vector3::AxisX, rotY);
	
	//���s�ړ�
	Move();
	//�J�����ʒu�ɍ��킹�ĉ�]
	Rotation();


	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}