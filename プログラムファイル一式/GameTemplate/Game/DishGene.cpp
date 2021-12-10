#include "stdafx.h"
#include "DishGene.h"
#include "Level.h"
#include "Dish.h"
#include "SoundSource.h"

#include "FontRender.h"

#include <string>

namespace
{
	const int NAME_SIZE_WAYPOINT = 8;
	const int NAME_SIZE_HITOKETA = 9;
	const int NAME_SIZE_HUTAKETA = 10;
	const int LETTER_FIRST_FROM_LEFT = 8;
	const int LETTER_SECOND_FROM_LEFT = 9;
}

DishGene::~DishGene()
{
	for (int i = 0;i < m_popedDishNum; i++) {
		DeleteGO(m_Dish[i]);
	}
}

bool DishGene::Start()
{
	Level level;

	//WayPoint�Ɩ��O�̕t�����I�u�W�F�N�g��T���B
	const wchar_t* wayPoint = L"WayPoint";
	std::vector<DishData> dishData;
	level.Init("Assets/level/dishWayPoint.tkl", [&](ObjectData& objectData) {
		//WayPoint���܂ޖ��O�̃I�u�W�F�N�g�ŁA
		if (wcsncmp(objectData.name, wayPoint, NAME_SIZE_WAYPOINT) == 0) {
			int dishNumber = 0;
			//������1�����񂯂�����������
			//�ꌅ��������name[8]�����Ƃ��Ă���΂���
			//WayPoint1~9�̎�
			if (wcslen(objectData.name) == NAME_SIZE_HITOKETA) {
				//���������̍�����1�Ԗڂ��Ƃ��Ă��āA�M�̔ԍ��ɐݒ肷��B
				dishNumber = _wtoi(&objectData.name[LETTER_FIRST_FROM_LEFT]);
				/*if (dishNumber != 1 && dishNumber != 36)
				{
					return true;
				}*/

#ifdef DEBUG
				FontRender* test;
				test = NewGO<FontRender>(0);
				test->SetText(objectData.name);
				Vector2 pos;
				g_camera3D->CalcScreenPositionFromWorldPosition(pos, objectData.Pos);
				test->SetScale(0.3f);
				test->SetPosition(pos);
#endif

				DishData dishdata;
				dishdata.s_dishPosition = objectData.Pos;
				dishdata.s_number = dishNumber;

				m_dishData[dishNumber - 1] = dishdata;
			}
			//�񂯂���������name[8][9]�����ɂƂ��Ă���cat���遨int�ɂ����Ă��
			//WayPoint10~
			else
			{
				//���������̍�����1�ԖځA2�Ԗڂ��Ƃ��Ă���
				wchar_t c_num10 = objectData.name[LETTER_FIRST_FROM_LEFT];
				wchar_t c_num1 = objectData.name[LETTER_SECOND_FROM_LEFT];
				int i_num10 = _wtoi(&c_num10);
				int i_num1 = _wtoi(&c_num1);
				string str10 = to_string(i_num10);
				string str1 = to_string(i_num1);
				str10 = str10 + str1;
				//�M�̔ԍ��ɐݒ肵�Ă��
				dishNumber = atoi(str10.c_str());
				/*if (dishNumber != 1 && dishNumber != 36)
				{
					return true;
				}*/
				DishData dishdata;
				dishdata.s_dishPosition = objectData.Pos;
				dishdata.s_number = dishNumber;

#ifdef DEBUG
				FontRender* test;
				test = NewGO<FontRender>(0);
				test->SetText(objectData.name);
				Vector2 pos;
				g_camera3D->CalcScreenPositionFromWorldPosition(pos, objectData.Pos);
				test->SetScale(0.3f);
				test->SetPosition(pos);
#endif

				m_dishData[dishNumber - 1] = dishdata;
			}


			m_Dish[m_popedDishNum] = NewGO<Dish>(0);
			m_Dish[m_popedDishNum]->SetPosition(objectData.Pos);
			//�M����o�����̂ŕϐ����C���N�������g
			m_popedDishNum++;

			if (m_popedDishNum == m_dishMaxNum) return true;

			return true;
		}
		return true;
	});
	//�����܂ł�����S���o���͂��Ȃ̂ŉғ���Ԃ�FALSE��
	m_dishGeneState = false;

	return true;
}

Vector3 DishGene::GetDishPositionBasedNumber(int number)
{
	return m_dishData[number].s_dishPosition;
}