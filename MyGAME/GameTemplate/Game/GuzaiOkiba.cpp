#include "stdafx.h"
#include "GuzaiOkiba.h"
#include "Level.h"
#include "Player.h"
#include "PlayerGene.h"
#include "Guzai.h"
#include "SkinModelRender.h"
#include "Kitchen.h"
#include "Arrow.h"

GuzaiOkiba::GuzaiOkiba()
{

}

GuzaiOkiba::~GuzaiOkiba()
{
	for (int i = 0; i < 8; i++) {
		//DeleteGO(stock[i]);
		DeleteGO(m_kitchenRender[i]);
	}
	/*DeleteGO(m_guzaiRender01);
	DeleteGO(m_guzaiRender02);*/
	
	DeleteGO(m_arrow01);
	DeleteGO(m_arrow02);

	//��ނ�����Ă��������
	if (guzai != nullptr) {
		DeleteGO(guzai);
	}

}

float GuzaiOkiba::TargetDistance(Vector3 v1, Vector3 v2)
{
	//�����v�Z�p�̊֐�
	Vector3 v3 = v1 - v2;
	float ans = v3.Length();

	return ans;
}

bool GuzaiOkiba::Start()
{
	pl01 = FindGO<Player>("player01");
	pl02 = FindGO<Player>("player02");

	Level level;

	//���x���f�[�^�����ޒu����̍��W���󂯎��A���f�����o���B
	const wchar_t* StockRight = L"StockRight";
	const wchar_t* StockLeft = L"StockLeft";
	level.Init("Assets/level/level_new4.tkl", [&](ObjectData& objectData) {
		if (wcsncmp(objectData.name, StockRight, 10) == 0) {
			m_kitchenNo = _wtoi(&objectData.name[10]);

			switch (m_kitchenNo)
			{
			case 1: {
				m_kitchenPos[m_kitchenNo - 1] = objectData.Pos;
				m_kitchenRender[m_kitchenNo - 1] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo - 1]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo - 1]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo - 1]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 2: {
				m_kitchenPos[m_kitchenNo - 1] = objectData.Pos;
				m_kitchenRender[m_kitchenNo - 1] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo - 1]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo - 1]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo - 1]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 3: {
				m_kitchenPos[m_kitchenNo - 1] = objectData.Pos;
				m_kitchenRender[m_kitchenNo - 1] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo - 1]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo - 1]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo - 1]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 4: {
				m_kitchenPos[m_kitchenNo - 1] = objectData.Pos;
				m_kitchenRender[m_kitchenNo - 1] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo - 1]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo - 1]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo - 1]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			default:
				break;
			}


		}
		if (wcsncmp(objectData.name, StockLeft, 9) == 0) {
			m_kitchenNo = _wtoi(&objectData.name[9]);

			switch (m_kitchenNo)
			{
			case 1: {
				m_kitchenPos[m_kitchenNo + 3] = objectData.Pos;
				m_kitchenRender[m_kitchenNo + 3] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo + 3]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo + 3]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo + 3]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 2: {
				m_kitchenPos[m_kitchenNo + 3] = objectData.Pos;
				m_kitchenRender[m_kitchenNo + 3] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo + 3]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo + 3]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo + 3]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 3: {
				m_kitchenPos[m_kitchenNo + 3] = objectData.Pos;
				m_kitchenRender[m_kitchenNo + 3] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo + 3]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo + 3]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo + 3]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			case 4: {
				m_kitchenPos[m_kitchenNo + 3] = objectData.Pos;
				m_kitchenRender[m_kitchenNo + 3] = NewGO<SkinModelRender>(0);
				m_kitchenRender[m_kitchenNo + 3]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_kitchenPos[m_kitchenNo - 1]);
				m_kitchenRender[m_kitchenNo + 3]->SetScale(m_kitchenScale);
				m_kitchenRender[m_kitchenNo + 3]->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);
				return true;
			}break;
			default:
				break;
			}
		}
	
	});

	//�^�[�Q�b�g���̋�ޒu����ɏo�������f��������������B

	m_arrow01 = NewGO<Arrow>(0);
	m_arrow01->SetPosition(m_Arrow01Pos);
	m_arrow02 = NewGO<Arrow>(0);
	m_arrow02->SetPosition(m_Arrow02Pos);
	/*m_guzaiRender01 = NewGO<SkinModelRender>(0);
	m_guzaiRender01->Init("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_targetPos01);
	m_guzaiRender02 = NewGO<SkinModelRender>(0);
	m_guzaiRender02->Init("Assets/modelData/Arrow/Arrow_Yellow.tkm", nullptr, enModelUpAxisZ, m_targetPos02);*/
	return true;
}

void GuzaiOkiba::PlayerDistance()
{
	//1P���̏��� 1P���̋�ޒu�����4�`7
	for (int i = 4; i < 8; i++) {
		//�v���C���[�Ƌ�ޒu����̋��������
		m_distance[i] = TargetDistance(m_kitchenPos[i], pl01->GetPosition());
	}

	//2P���̏��� 2P���̋�ޒu�����0�`3
	for (int i = 0; i < 4; i++) {
		m_distance[i] = TargetDistance(m_kitchenPos[i], pl02->GetPosition());
	}
}

void GuzaiOkiba::Targeted()
{
	//��ޒu����ƃv���C���[�̋����𑪂�A�͈͓��̈�̋�ޒu����ɂ̂݃A�N�Z�X�\�ɂ���B

	//1P���̏���

	for (int i = 4; i < 8; i++) {
		//�v���C���[�Ƌ�ޒu����̋��������ȉ��ŁA�^�[�Q�b�g���Ŗ����A��ނ��u����Ă��Ȃ��ꍇ�c
		if (m_distance[i] < 100.0f && m_targeted01 == false && m_guzaiSet[i] == false && pl01->have == 1) {
			//�^�[�Q�b�g���ɃA�N�Z�X�\�ȋ�ޒu����Ɉ��\�������邽�߂ɁA�^�[�Q�b�g���̋�ޒu����̍��W���L������B
			m_targetPos01 = m_kitchenPos[i];
			m_targetPos01.y += 100.0f;
			//�^�[�Q�b�g��ԂɈڍs���A�^�[�Q�b�g�����ԍ��̋�ޒu����ɃA�N�Z�X�\�ɂ���B
			m_targeted01 = true;
			m_targetNo01 = i;
			m_kitchenSet[m_targetNo01] = true;
			m_Arrow01Pos = m_kitchenPos[m_targetNo01];
			m_Arrow01Pos.y += 80.0f;
			m_arrow01->SetPosition(m_Arrow01Pos);
			//�^�[�Q�b�g���̏ꍇ�͋��������ȉ��ł����s����Ȃ��̂ŁA���������ɃA�N�Z�X���邱�Ƃ͂Ȃ��B
		}
	}
	//�^�[�Q�b�g���̏ꍇ�c
	if (m_targeted01 == true) {
		m_arrow01->Expansion();
		//�^�[�Q�b�g���̋�ޒu����ƃv���C���[�̋����𑪂�A���ȏ�ɂȂ����Ƃ��c
		m_targetDistance01 = TargetDistance(m_kitchenPos[m_targetNo01], pl01->GetPosition());
		if (m_targetDistance01 >= 100.0f || m_guzaiSet[m_targetNo01] == true) {
			//�^�[�Q�b�g��Ԃ���߂�A�^�[�Q�b�g����������ޒu����ɑ΂��ăA�N�Z�X�s�\�ɂ���B
			m_targeted01 = false;
			m_kitchenSet[m_targetNo01] = false;
		}
	}
	//�^�[�Q�b�g���Ă��Ȃ��ꍇ�c
	else {
		//�^�[�Q�b�g���W��0,0,0�ɂ���B
		m_arrow01->Shrink();
		//m_arrow01->SetPosition({ 0.0f,-1000.0f,0.0f });
		m_targetPos01 = { 0.0f,-200.0f,0.0f }/*Vector3::Zero*/;
	}

	//2P���̏����A1P�Ƃقړ����B

	for (int i = 0; i < 4; i++) {
		if (m_distance[i] < 100.0f && m_targeted02 == false && m_guzaiSet[i] == false && pl02->have == 1) {
			m_targetPos02 = m_kitchenPos[i];
			m_targetPos02.y += 100.0f;
			m_targeted02 = true;
			m_targetNo02 = i;
			m_kitchenSet[m_targetNo02] = true;
			m_Arrow02Pos = m_kitchenPos[m_targetNo02];
			m_Arrow02Pos.y += 80.0f;
			m_arrow02->SetPosition(m_Arrow02Pos);
		}
	}
	if (m_targeted02 == true) {
		m_arrow02->Expansion();
		m_targetDistance02 = TargetDistance(m_kitchenPos[m_targetNo02], pl02->GetPosition());
		if (m_targetDistance02 >= 100.0f || m_guzaiSet[m_targetNo02]) {
			m_targeted02 = false;
			m_kitchenSet[m_targetNo02] = false;
		}
	}
	else {
		m_arrow02->Shrink();
		//m_arrow02->SetPosition({ 0.0f,-1000.0f,0.0f });
		m_targetPos02 = { 0.0f,-200.0f,0.0f };/*Vector3::Zero;*/
	}
}


void GuzaiOkiba::Update()
{
	//�v���C���[�̏������
	pl01 = FindGO<Player>("player01");
	pl02 = FindGO<Player>("player02");

	PlayerDistance();

	Targeted();

	//��ޒu����̕\��
	for (int i = 0; i < 8; i++) {
		m_kitchenRender[i]->SetPosition(m_kitchenPos[i]);
	}
}