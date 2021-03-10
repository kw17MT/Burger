#include "stdafx.h"
#include "Kitchen.h"
#include "ModelRender.h"
#include "Burger.h"
#include "Guzai.h"


bool Kitchen::Start()
{
	ModelInitData modeldata;
	modeldata.m_tkmFilePath = "Assets/modelData/ches.tkm";
	modeldata.m_fxFilePath = "Assets/shader/model.fx";

	modeldata.m_vsEntryPointFunc = "VSMain";
	modeldata.m_vsSkinEntryPointFunc = "VSSkinMain";

	modeldata.m_modelUpAxis = enModelUpAxisY;

	modeldata.m_expandConstantBuffer = &g_lig;
	modeldata.m_expandConstantBufferSize = sizeof(g_lig);

	m_skeleton.Init("Assets/modelData/unityChan.tks");
	modeldata.m_skeleton = &m_skeleton;

	model.Init(modeldata);

	m_charaCon.Init(0.0f, 0.0f, KitchenPos);

	return true;
}

void Kitchen::Stack(int num)
{
	ModelRender* pl = FindGO<ModelRender>("player01");

	if (nextStackNum < stack) {
		StackedGuzai[nextStackNum] = NewGO<Guzai>(0);
		StackedGuzai[nextStackNum]->put = 1;
		StackedGuzai[nextStackNum]->ChangeGuzai(pl->GuzaiNo[nextStackNum]);
		
		nextStackNum++;
	}
}

void Kitchen::Delete()
{
	for (int i = 0;i < nextStackNum; i++) {
		DeleteGO(StackedGuzai[i]);
	}
	stack = 0;
	nextStackNum = 0;
	DeleteTimer = 0;
	ModelRender* pl = FindGO<ModelRender>("player01");
	pl->have = 0;
}

// Delay�͕K�v
// �Ȃ��ƃG���[
//5�ς񂾂�o�[�K�[�ɕϊ�
void Kitchen::BornBurger()
{
	if (nextStackNum >= 1 && g_pad[0]->IsPress(enButtonY)) {
		Delay--;
		if (Delay == 0) {
			ModelRender* pl = FindGO<ModelRender>("player01");
			
			//�����ŋ�ނ������Ă�����No.���v���C���[�������Ă���No.�i�[�p�z��ɂ���Ă����B
			for (int i = 0;i < nextStackNum; i++) {
				pl->GuzaiNo[i] = StackedGuzai[i]->GetTypeNo();
			}
			Delete();
			pl->have = 1;
			bur = NewGO<Burger>(0,"burger");
			bur->burgerExist = 1;
			
			Delay = 60;
		}
	}
}

void Kitchen::ClearNo()
{
	ModelRender* pl = FindGO<ModelRender>("player01");

	for (int i = 0;i < nextStackNum; i++) {
		pl->GuzaiNo[i] = 0;
	}
}

void Kitchen::Update()
{
	Stack(stack);

	if (g_pad[0]->IsPress(enButtonX)) {
		DeleteTimer++;
		if (DeleteTimer > 50) {
			ClearNo();
			Delete();
		}
	}

	//��ނ��L�b�`���̏�ɍڂ��邽�߂̍��W�ݒ�
	for (int i = 0;i < nextStackNum;i++) {
		Vector3 GuzaiPos = KitchenPos;
		GuzaiPos.y = (i + 1) * 100.0f;
		StackedGuzai[i]->SetPosition(GuzaiPos);
	}

	//�L�b�`����5�ȏ��ނ�����Ǝ��Ȃ��悤�ɂ���B
	if (nextStackNum >= 5) {
		ModelRender* pl = FindGO<ModelRender>("player01");
		pl->have = 1;
	}

	BornBurger();
	model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}