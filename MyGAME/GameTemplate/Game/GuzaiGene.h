#pragma once
class Guzai;
//class Buff;
class DishGene;
class SkinModelRender;

#include <vector>

class GuzaiGene : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;
	const Vector3 m_scale = Vector3::Zero;
	static const int guzaiNum = 37;

	bool isCompletedInitialAction = false;
public:
	GuzaiGene() {};
	~GuzaiGene() {};
	//������̍��W�ݒ�B
	bool Start();
	//��ނ𐶐�����B
	//�����_���ϐ���p���ăo�t���o�����ۂ������߂Ă���B
	void Update();

	bool GetInitialActionState() { return isCompletedInitialAction; }
	//��ނ𗬂��^�C�~���O�����߂���́B
	//int timer = 0;
	//�o�t�����݂��Ă���ƂP�A�Ȃ��ƂO�B�@�O�łȂ��ƃo�t�A�C�e���͗���Ȃ��B
	//int Buffnum = 0;
	//int DeBuffnum = 0;

	SkinModelRender* m_skinModelRender;
	Guzai* m_guzai[guzaiNum];
	DishGene* m_dishGene;
	//Buff* m_buff;
};
