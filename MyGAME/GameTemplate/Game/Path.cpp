#include "stdafx.h"
#include "Path.h"
#include "Level.h"

Path::Path()
{

}

Path::~Path()
{

}

void Path::Load(const char* filePath,int guzaiNo)
{
	Level level;
	const wchar_t* side;
	//�������E�������߂�B
	if (guzaiNo == 1)
	{
		side = L"R";
	}
	else if (guzaiNo == 2)
	{
		side = L"L";
	}
	std::vector<Point> poinstList;
	level.Init(filePath, [&](ObjectData& objectData) {
		if (wcsncmp(objectData.name, side,1) == 0) {
			//�������int�^�ɕϊ�
			int pointNm = _wtoi(&objectData.name[1]);
			Point point;
			point.s_vector = objectData.Pos;
			point.s_number = pointNm;
			m_pointList[pointNm - 1] = point;
			//m_pointList.insert(pointNm, point);
			return true;
		}

		return true;
	});
}

Point* Path::GetNearPoint(const Vector3& pos)
{
	Point* point = &m_pointList[0];
	Vector3 diff = m_pointList[0].s_vector - pos;
	//���̏ꏊ�����ԋ߂��|�C���g�T��
	for (int i = 1; i < m_pointList.size(); i++) {
		Vector3 diff2 = m_pointList[i].s_vector - pos;
		if (diff.LengthSq() > diff2.LengthSq()) {
			diff = diff2;
			point = &m_pointList[i];
		}
	}
	return point;
}

Point* Path::GetPoint(const int& number)
{
	//�ԍ����Ō�̃|�C���g��������ŏ��̃|�C���g
	if (number == m_pointList.size()) {
		return &m_pointList[0];
	}
	else {
		return &m_pointList[number];
	}
}