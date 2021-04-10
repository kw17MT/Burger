#include "stdafx.h"
#include "DeBuff.h"
#include "ModelRender.h"
#include "ObjectGene.h"

#include "PathMove.h"

#include "ObjectGene.h"
#include "Guzai.h"
#include "Buff.h"

namespace
{
	const float MOVESPEED = 130.0f;
	const float BLOWDISTANCE = 300.0f * 300.0f;
}

DeBuff::DeBuff()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	modeldata.m_fxFilePath = "Assets/shader/demodel.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	modeldata.m_modelUpAxis = enModelUpAxisY;

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	Vector3 pos = { 0.0f,100.0f,-500.0f };

	m_charaCon.Init(0.0f, 0.0f, pos);


}

bool DeBuff::Start()
{
	m_pathMove = std::make_unique<PathMove>();

	if (m_isDeBuffLane)
	{
		m_pathMove.get()->Init(m_charaCon.GetPosition(), MOVESPEED, enDeBuffLane, BuffNo);
	}
	else {
		m_charaCon.SetPosition({ 0.0f, 0.0f, -1000.0f });
		m_pathMove.get()->Init(m_charaCon.GetPosition(), MOVESPEED, enNormalLane, BuffNo);
	}

	return true;
}


Vector3 DeBuff::GetPosition()
{
	Vector3 Pos = m_charaCon.GetPosition();
	return Pos;
}

void DeBuff::SetPosition(Vector3 pos)
{
	m_charaCon.SetPosition(pos);
}

void DeBuff::Update()
{
	//�X�P���g�����X�V�B
	m_skeleton.Update(model.GetWorldMatrix());

	//�ړ�������B
	m_charaCon.SetPosition(m_pathMove.get()->Move());
	//�Ō�̃|�C���g�܂œ��B������B
	if (m_pathMove.get()->GetIsFinalPoint())
	{
		//���j������B
		if (m_isDeBuffLane)
		{
			QueryGOs<Guzai>("guzai", [&](Guzai* guzai)
			{
				//���Α��̐H�ނ������j���Ȃ��悤�ɁB
				if (BuffNo == guzai->GetGuzaiNo())
				{
					return true;
				}

				if ((guzai->GetPosition() - m_charaCon.GetPosition()).LengthSq() <= BLOWDISTANCE)
				{
					DeleteGO(guzai);
					return true;
				}	
				return true;
			});

			QueryGOs<Buff>("buff", [&](Buff* buff)
				{
					//���Α��̐H�ނ������j���Ȃ��悤�ɁB
					if (BuffNo == buff->GetBuffNo())
					{
						return true;
					}

					if ((buff->GetPosition() - m_charaCon.GetPosition()).LengthSq() <= BLOWDISTANCE)
					{
						DeleteGO(buff);
						return false;
					}
					return true;
				});

			QueryGOs<DeBuff>("debuff", [&](DeBuff* debuff)
				{
					//���Α��̐H�ނ������j���Ȃ��悤�ɁB
					if (BuffNo == debuff->BuffNo)
					{
						return true;
					}

					if ((debuff->GetPosition() - m_charaCon.GetPosition()).LengthSq() <= BLOWDISTANCE)
					{
						DeleteGO(debuff);
						return false;
					}
					return true;
				});
		
			//�폜����B
			DeleteGO(this);

			return;
		}

		ObjectGene* og = nullptr;
		if (BuffNo == 1)
		{
			og = FindGO<ObjectGene>("gene01");
		}
		else if (BuffNo == 2)
		{
			og = FindGO<ObjectGene>("gene02");
		}
		else {
			return;
		}

		og->DeBuffnum = 0;

		//�폜����B
		DeleteGO(this);
		return;

		
	}

	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);

	if (m_isDeBuffLane)
	{
		return;
	}


	if (BuffNo == 1) {
		Vector3 BuffPos = m_charaCon.GetPosition();
		ModelRender* pl01 = FindGO<ModelRender>("player01");
		Vector3 plPos01 = pl01->GetPosition();

		//�o�t�A�C�e���ƃv���C���[�̋����𑪂�B
		float Buff2Pl = (BuffPos.x - plPos01.x) * (BuffPos.x - plPos01.x) + (BuffPos.y - plPos01.y) * (BuffPos.y - plPos01.y) + (BuffPos.z - plPos01.z) * (BuffPos.z - plPos01.z);
		Buff2Pl = sqrt(Buff2Pl);

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ�����100���߂��ʒu�ɂ���B
		if (g_pad[0]->IsTrigger(enButtonA) && pl01->have == 0) {
			if (Buff2Pl < 150.0f) {
				//�v���C���[�Ƀo�t�A�C�e���̌��ʂ���������B
				//TRUE�ɂ���ƈړ����x���A�b�v����B�v���C���[���Ŏ��Ԃ𑪂��Ă��āA���������Ō��ʂ������B
				//TODO �o�t���v���C���[�ɕt�^�B
				DeleteGO(this);

				pl01->SetEnItem(enDebuffItem);
			}
		}
	}

	if (BuffNo == 2) {
		Vector3 BuffPos = m_charaCon.GetPosition();
		ModelRender* pl02 = FindGO<ModelRender>("player02");
		Vector3 plPos02 = pl02->GetPosition();

		//�o�t�A�C�e���ƃv���C���[�̋����𑪂�B
		float Buff2Pl = (BuffPos.x - plPos02.x) * (BuffPos.x - plPos02.x) + (BuffPos.y - plPos02.y) * (BuffPos.y - plPos02.y) + (BuffPos.z - plPos02.z) * (BuffPos.z - plPos02.z);
		Buff2Pl = sqrt(Buff2Pl);

		//A�{�^�����������Ƃ��A�v���C���[�͉��������Ă��Ȃ�����150���߂��ʒu�ɂ���B
		if (g_pad[1]->IsTrigger(enButtonA) && pl02->have == 0) {
			if (Buff2Pl < 150.0f) {
				//�v���C���[�Ƀo�t�A�C�e���̌��ʂ���������B
				//TRUE�ɂ���ƈړ����x���A�b�v����B�v���C���[���Ŏ��Ԃ𑪂��Ă��āA���������Ō��ʂ������B
				DeleteGO(this);

				pl02->SetEnItem(enDebuffItem);
			}
		}
	}

	
}