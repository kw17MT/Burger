#include "stdafx.h"
#include "GuzaiGene.h"
#include "Guzai.h"
#include "Buff.h"
#include "DeBuff.h"
#include "SkinModelRender.h"
#include "DishGene.h"

#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include <random>		//���������p

bool GuzaiGene::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/egg.tkm", nullptr, enModelUpAxisY, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_dishGene = FindGO<DishGene>("dishGene");

	return true;
}

void GuzaiGene::Update()
{
	//�܂��M�𐶐����ł����Update�֐����X���[
	if (m_dishGene->GetDishGeneState() == true) {
		return;
	}

	//�܂��ŏ��̋�ނ���ׂ�̂�����ĂȂ��I
	if (isCompletedInitialAction == false) {
		for (int i = 0;i < guzaiNum; i++)
		{
			m_guzai[i] = NewGO<Guzai>(0);
			m_guzai[i]->SetPosition(m_dishGene->GetDishPositionBasedNumber(i));
		}



		isCompletedInitialAction = true;
	}


	//�S�Ă̎M�̏�ɋ�ނ�NewGO
	//�̂��߂ɂ�37�̂���̃|�W�V�������K�v�ɂȂ�B
	//�Ɠ����Ɏ����i��ށj�͂��܁A���Ԗڂ̎M�̏�ɂ��邩���o������


	//��������������t���O���M�����m�����瓮���n�߂�B
	//�M���������Ƃɋ�ނ�����
	//�����Guzaicpp�̂ق��ŏ��������̂ł���


	//��̎M���v�����An�ȏ�ɂȂ�����A��C�ɕ�[
	//����ɂ����ė����Ă���悤��

	//����
	//Game/DishGene/Dish/GuzaiGene/Guzai/Dish/GuzaiGene/Guzai...


	//�����A�M�ɂ���ϐ����U��������A���̎M�̏�ɋ�ނ�newGO






















	//timer++;

	////rand()(���`�����@)���ǂ����ȕʂ̕��@
	//std::random_device rnd; //�񌈒�I����������(pc�����̏�񂩂痐���𐶐�) �V�[�h�l�𐶐�����̂Ɏg�p
	//std::mt19937 mt(rnd()); //����I���������� �����Z���k�c�C�X�^32bit�� rnd���o�͂���l���V�[�h�l�Ƃ���
	//std::uniform_int_distribution<int> rand10(0, 9); //�͈͎w�藐������(����0�`9)
	//int randNum = rand10(mt);
	////2���鐶����ŋ�ނ̏o���p�^�[�����قړ����ɂȂ��肠��

	//if (timer >= 50 && randNum != 1) {
	//	m_guzai = NewGO<Guzai>(0,"guzai");
	//	//m_guzai->SetGuzaiNo(GeneNo);
	//	m_guzai->SetPosition(m_charaCon.GetPosition());
	//	timer = 0;
	//}

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
	
	
	m_skinModelRender->SetScale(m_scale);
}\