#include "stdafx.h"
#include "ObjectGene.h"
#include "Guzai.h"
#include "Buff.h"
#include "DeBuff.h"

#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include <random>		//���������p

ObjectGene::ObjectGene()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/gu/egg.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	modeldata.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	modeldata.m_modelUpAxis = enModelUpAxisZ;

	model.Init(modeldata);

	Vector3 pos = { 0.0f,200.0f,-500.0f };

	m_charaCon.Init(40.0f, 100.0f, pos);
}

void ObjectGene::Update()
{
	timer++;
	/*std::srand(time(NULL));
	int randNum = rand() % 10;*/

	//rand()(���`�����@)���ǂ����ȕʂ̕��@
	std::random_device rnd; //�񌈒�I����������(pc�����̏�񂩂痐���𐶐�) �V�[�h�l�𐶐�����̂Ɏg�p
	std::mt19937 mt(rnd()); //����I���������� �����Z���k�c�C�X�^32bit�� rnd���o�͂���l���V�[�h�l�Ƃ���
	std::uniform_int_distribution<int> rand10(0, 9); //�͈͎w�藐������(����0�`9)
	int randNum = rand10(mt);
	//2���鐶����ŋ�ނ̏o���p�^�[�����قړ����ɂȂ��肠��

	if (timer >= 50 && randNum != 1) {
		m_guzai = NewGO<Guzai>(0,"guzai");
		m_guzai->SetGuzaiNo(GeneNo);
		m_guzai->SetPosition(m_charaCon.GetPosition());
		timer = 0;
	}

	////�T�O�t���[���o������A�����_���ȕϐ����P�̎��i10%�j
	//if (timer == 50 && randNum == 1) {
	//	//�o�t�A�C�e������ʂɏo�Ă��Ȃ��Ƃ��B
	//	if (Buffnum == 0) {
	//		m_buff = NewGO<Buff>(0, "buff");
	//		m_buff->SetBuffNo(GeneNo);
	//		m_buff->SetPosition(m_charaCon.GetPosition());
	//		timer = 0;
	//		Buffnum = 1;
	//	}
	//	else if (DeBuffnum == 0)
	//	{
	//		DeBuff* deBuff = NewGO<DeBuff>(0, "debuff");
	//		deBuff->SetBuffNo(GeneNo);
	//		deBuff->SetPosition(m_charaCon.GetPosition());
	//		timer = 0;
	//		DeBuffnum = 1;
	//	}
	//	//�o�t�A�C�e������ʂɏo�Ă���Ƃ��A�o�t�A�C�e�����o�����ɋ�ނ������B
	//	else {
	//		m_guzai = NewGO<Guzai>(0, "guzai");
	//		m_guzai->SetGuzaiNo(GeneNo);
	//		m_guzai->SetPosition(m_charaCon.GetPosition());
	//		timer = 0;
	//	}
	//}
	
	
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}