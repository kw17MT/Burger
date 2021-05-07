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
	side = L"WayPoint";

	std::vector<Point> poinstList;
	level.Init(filePath, [&](ObjectData& objectData) {
		if (wcsncmp(objectData.name, side,8) == 0) {
			//�������int�^�ɕϊ�
			int pointNm = _wtoi(&objectData.name[8]);
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
	//�ŏ��̃|�C���g�������Ă���B
	Point* point = &m_pointList[0];
	//�������W����ŏ��̃|�C���g�Ɍ������x�N�g�������߂�B
	Vector3 diff = m_pointList[0].s_vector - pos;
	//���̏ꏊ�����ԋ߂��|�C���g�T���B
	for (int i = 1; i < m_pointList.size(); i++) {
		//�������W����i�Ԗڂ̃|�C���g�Ɍ������x�N�g�������߂�B
		Vector3 diff2 = m_pointList[i].s_vector - pos;
		//���߂��x�N�g���̒����̂ق����Z��������B
		if (diff.LengthSq() > diff2.LengthSq()) {
			//diff�ɋ��߂��x�N�g�������B
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