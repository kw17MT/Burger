#include "stdafx.h"
#include "DishGene.h"
#include "Level.h"
#include "Dish.h"


#include <string>

DishGene::~DishGene()
{
	for (int i = 0;i < DishNum; i++) {
		DeleteGO(m_Dish[i]);
	}
}

bool DishGene::Start()
{
	Level level;

	const wchar_t* WayPoint = L"WayPoint";
	std::vector<DishData> dishData;
	level.Init("Assets/level/WayPoint_new.tkl", [&](ObjectData& objectData) {
		if (wcsncmp(objectData.name, WayPoint, 8) == 0) {
			int dishNumber = 0;
			//������1�����񂯂�����������
			//�ꌅ��������name[9]�����Ƃ��Ă���΂���
			if (wcslen(objectData.name) == 9) {
				dishNumber = _wtoi(&objectData.name[8]);
				DishData dishdata;
				dishdata.s_dishPosition = objectData.Pos;
				dishdata.s_number = dishNumber;

				m_dishData[dishNumber - 1] = dishdata;
			}

			//�񂯂���������name[9][10]�����ɂƂ��Ă���cat���遨int�ɂ����Ă��
			else
			{
				wchar_t c_num10 = objectData.name[8];
				wchar_t c_num1 = objectData.name[9];
				int i_num10 = _wtoi(&c_num10);
				int i_num1 = _wtoi(&c_num1);
				string str10 = to_string(i_num10);
				string str1 = to_string(i_num1);
				str10 = str10 + str1;
				dishNumber = atoi(str10.c_str());
				DishData dishdata;
				dishdata.s_dishPosition = objectData.Pos;
				dishdata.s_number = dishNumber;

				m_dishData[dishNumber - 1] = dishdata;
			}


			m_Dish[DishNum] = NewGO<Dish>(0);
			m_Dish[DishNum]->SetPosition(objectData.Pos);
			DishNum++;
			return true;
		}
	});

	DishGeneState = false;

	return true;
}

Vector3 DishGene::GetDishPositionBasedNumber(int number)
{
	return m_dishData[number].s_dishPosition;
}