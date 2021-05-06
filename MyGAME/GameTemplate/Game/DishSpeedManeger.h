#pragma once
class DishSpeedManeger : public IGameObject
{
private:
	int countFrame = 0;
	int elapseTime = 0;						//�o�ߎ��ԁA�Q�[���X�^�[�g����ǂ̂��炢���Ԃ������Ă��邩
	int speedUpTimeStart = 20;					//�X�s�[�h�A�b�v�����������ԁA�����_���ɂ�����
	int speedUpTimeEnd = 25;						//�X�s�[�h�A�b�v���Ԃ̒����A�����_���Ȑ����ɂ�����

	bool isSpeedUp = false;
public:
	bool GetSpeedUpState() { return isSpeedUp; }

	void Update();

	static DishSpeedManeger& GetInstance()
	{
		static DishSpeedManeger instance;
		return instance;
	}
};

