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

GuzaiGene::~GuzaiGene()
{
	//DeleteGO(m_skinModelRender);

	////��ނ��폜
	//DeleteGO(m_skinModelRender);
	/*for (int i = 0; i < guzaiNum; i++) {
		if (m_guzai[i] != nullptr) {
			DeleteGO(m_guzai[i]);
		}
	}*/
	for (int i = 0; i < 99; i++) {
		if (m_guzaiFlag[i] == true) {
			DeleteGO(m_guzai[i]);
		}
	}
}

bool GuzaiGene::Start()
{
	/*m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/gu/egg.tkm", nullptr, enModelUpAxisY, m_position);
	m_skinModelRender->InitShader("Assets/shader/model.fx", "VSMain", "VSSkinMain", DXGI_FORMAT_R32G32B32A32_FLOAT);*/

	//m_dishGene = FindGO<DishGene>("dishGene");

	return true;
}

void GuzaiGene::Update()
{
	////�܂��M�𐶐����ł����Update�֐����X���[
	//if (m_dishGene->GetDishGeneState() == true) {
	//	return;
	//}

	////�܂��ŏ��̋�ނ���ׂ�̂�����ĂȂ��I
	//if (isCompletedSetGuzai == false) {
	//	for (int i = 0;i < guzaiNum; i++)
	//	{
	//		m_guzai[i] = NewGO<Guzai>(0);
	//		//WayPoint�P���珇�ɋ�ނ�ݒu
	//		m_guzai[i]->SetPosition(m_dishGene->GetDishPositionBasedNumber(i));
	//		//�����i��ށj�͂��܁A���Ԗڂ̎M�̏�ɂ��邩���o������
	//		m_guzai[i]->SetDishNumber(i + 1);
	//	}

	//	//�S�Ă̎M�̏�ɋ�ނ�u���I�����I
	//	isCompletedSetGuzai = true;
	//}

	////��̎M���v�����An�ȏ�ɂȂ�����A��C�ɕ�[
	//if (emptyDishCounter >= LostNumber) {
	//	for (int i = 0; i < emptyDishCounter; i++) {
	//		m_guzai[emptyDishNumber[i]] = NewGO<Guzai>(0);
	//		m_setPos = m_dishGene->GetDishPositionBasedNumber(emptyDishNumber[i]);
	//		m_setPos.y += 1000.0f;
	//		//m_guzai[emptyDishNumber[i]]->SetPosition(m_dishGene->GetDishPositionBasedNumber(emptyDishNumber[i]));
	//		m_guzai[emptyDishNumber[i]]->SetPosition(m_setPos);
	//		m_guzai[emptyDishNumber[i]]->SetDishNumber(emptyDishNumber[i]);
	//	}

	//	for (int i = 0;emptyDishCounter < i; i++)
	//	{
	//		emptyDishNumber[i] = 0;
	//	}
	//	emptyDishCounter = 0;
	//}
	
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
	
//m_skinModelRender->SetScale(m_scale);
}