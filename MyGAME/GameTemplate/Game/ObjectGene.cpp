#include "stdafx.h"
#include "ObjectGene.h"
#include "Guzai.h"
#include "Buff.h"

#include <ctime>        // time
#include <cstdlib>      // srand,rand

ObjectGene::ObjectGene()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	modeldata.m_modelUpAxis = enModelUpAxisZ;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	Vector3 pos = { 0.0f,200.0f,-500.0f };

	m_charaCon.Init(40.0f, 100.0f, pos);
}

void ObjectGene::SetPosition(Vector3 pos)
{
	m_charaCon.SetPosition(pos);
}

bool ObjectGene::Start()
{
	

	return true;
}

Vector3 ObjectGene::GetPosition()
{
	return m_charaCon.GetPosition();
}

void ObjectGene::Update()
{
	timer++;
	std::srand(time(NULL));
	int randNum = rand() % 10;

	if (timer == 50 && randNum != 1) {
		m_guzai = NewGO<Guzai>(0,"guzai");
		m_guzai->SetGuzaiNo(GeneNo);
		m_guzai->SetPosition(m_charaCon.GetPosition());
		timer = 0;
	}

	if (timer == 50 && randNum == 1) {
		if (Buffnum == 0) {
			m_buff = NewGO<Buff>(0, "buff");
			m_buff->SetBuffNo(GeneNo);
			m_buff->SetPosition(m_charaCon.GetPosition());
			timer = 0;
			Buffnum = 1;
		}
		else {
			m_guzai = NewGO<Guzai>(0, "guzai");
			m_guzai->SetGuzaiNo(GeneNo);
			m_guzai->SetPosition(m_charaCon.GetPosition());
			timer = 0;
		}
	}

	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}