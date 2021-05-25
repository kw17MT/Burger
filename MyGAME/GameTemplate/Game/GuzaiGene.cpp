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

	//��ނ��폜
	DeleteGO(m_skinModelRender);
	for (int i = 0; i < guzaiNum; i++) {
		if (m_guzai[i] != nullptr) {
			DeleteGO(m_guzai[i]);
		}
	}
}

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

	//�ŏ���36�o��
	//�܂��ŏ��̋�ނ���ׂ�̂�����ĂȂ��I
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
	
	m_skinModelRender->SetScale(m_scale);
}