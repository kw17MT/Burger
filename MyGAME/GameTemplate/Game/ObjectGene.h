#pragma once
class Guzai;
class Buff;

#include <vector>

class ObjectGene : public IGameObject
{
private:
	//Generator�p�̃��f��
	Model model;
	ModelInitData modeldata;
	Skeleton m_skeleton;
	CharacterController m_charaCon;

	//�W�F�l���[�^�[�̔ԍ��B1���E�A2����
	int GeneNo = 0;

public:
	//������̍��W�ݒ�B
	ObjectGene();
	//��ނ�o�t�A�C�e���𐶐�����B
	//�����_���ϐ���p���ăo�t���o�����ۂ������߂Ă���B
	void Update();
	void SetPosition(Vector3 pos) { m_charaCon.SetPosition(pos); }
	Vector3 GetPosition() { return m_charaCon.GetPosition(); }
	//�����킪�����E���ǂ���ɂ��邩�ݒ肵�Ă����B�@�P�A���@�Q�A�E
	void SetGeneNo(int num) { GeneNo = num; }
	
	void Render(RenderContext& rc) { model.Draw(rc); }

	//��ނ𗬂��^�C�~���O�����߂���́B
	int timer = 0;
	//�o�t�����݂��Ă���ƂP�A�Ȃ��ƂO�B�@�O�łȂ��ƃo�t�A�C�e���͗���Ȃ��B
	int Buffnum = 0;
	int DeBuffnum = 0;

	Guzai* m_guzai;
	Buff* m_buff;
};
