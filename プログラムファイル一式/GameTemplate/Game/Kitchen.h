#pragma once
class Guzai;
class Burger;
class SkinModelRender;
class Player;
class CSoundSource;
class Meter;
class Counter;

class Kitchen : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;						//�L�b�`���̍��W							
	Vector3 m_scale = { 0.3f,0.3f,0.3f };					//�L�b�`���̊g�嗦
	Vector3 m_slidePos = Vector3::Zero;						//��ނ��n���o�[�K�[�ɂȂ�Ƃ��Ɉꂩ���ɏW�܂�Ƃ��̃X�s�[�h
	
	int m_kitchenNo = 0;									//�ǂ������̃L�b�`�����B�O�����A�P���E
	int m_stack = 0;											//���܉���ނ�ς�ł��邩		
	int m_delay = 60;											//��ނ��������x�����N�����p�̕ϐ�
	const int m_maxStack = 5;									//�L�b�`���ɂ�����ő吔

	float m_distance = 0.0f;

	bool m_soundFlag = false;								//�����o�Ă��邩�H
	bool m_canGrab = true;									//���݂��߂邩�i�t���[���̂�����N�����p�j
	bool m_isPlayerCookingOnKitchen = false;							//��ނ��������Ƃ����܂��Ă��邩�ǂ���

public:

	~Kitchen();

	/**
	 * @brief �L�b�`�����f���̏�������A�K�v�I�u�W�F�N�g�̃f�[�^�擾�B
	 * @return true
	*/
	bool Start();

	/**
	 * @brief �n���o�[�K�[�𐶂ݏo�����̔����A�L�b�`���ォ���ނ���邩�̔���𖈃t���[���s��
	*/
	void Update();

	/**
	 * @brief �L�b�`���ԍ���ݒ肷��B
	 * @param num �L�b�`���̔ԍ��@�O�����A�P���E
	*/
	void SetKitchenNo(int num) { m_kitchenNo = num; }

	/**
	 * @brief �L�b�`���̍��W��ݒ肷��B
	 * @param pos �V�����L�b�`���̍��W
	*/
	void SetKitchenPos(Vector3 pos) { m_position = pos; }

	/**
	 * @brief �L�b�`���̍��W���擾
	 * @return ���݂̃L�b�`���̍��W
	*/
	Vector3 GetKitchenPos() const { return m_position; }

	/**
	 * @brief �L�b�`����̋�ނ�S�������A�n���o�[�K�[�𐶂ݏo�����Ɏg�p����
	*/
	void Delete();

	/**
	 * @brief �L�b�`����ɂ����ނ̐����C���N�������g
	*/
	void PlusStack() { m_stack++; }

	/**
	 * @brief �X�^�b�N�����w�����f�N�������g
	*/
	void MinusStack() { m_stack--; }

	/**
	 * @brief �L�b�`����ɂ͋�ނ����݂��Ȃ����Ƃ�ݒ肷��
	*/
	void SetStack0() { m_stack = 0; }

	/**
	 * @brief ���݉��i��ނ��ς܂�Ă��邩��`����֐�
	 * @return ���݁A�ς܂�Ă����ނ̐�
	*/
	int GetStackNum() const { return m_stack; }

	/**
	 * @brief ��ނ��n���o�[�K�[�ɉ��H����B
	*/
	void BornBurger();

	/**
	 * @brief ��ނ��������ɁA�v���C���[�Ɋi�[����Ă�����No.���X�ŏ���������B
	 * ���̊֐��͋�ނ������O�Ɏg�����ƁB
	*/
	void ClearNo();

	/**
	 * @brief �L�b�`���̊g�嗦��ύX����B
	 * @param scale �ύX�������g�嗦
	*/
	void SetScale(Vector3 scale) { m_scale = scale; }

	/**
	 * @brief ���̃t���[�����ɃL�b�`�������ނ����ꂽ��
	 * @param state TRUE�����ꂽ�B
	*/
	void ChangeGrabState(bool state) { m_canGrab = state; }

	/**
	 * @brief �L�b�`����ɂ����ނ̓o�^
	 * �����̋�ނ͕�������K�v���Ȃ��A�p�����[�^�[�������肽���̂�const�s�v
	 * Delete�֐��Ŏg�p����B
	*/
	void RegistStackedGuzai(Guzai* m_guzai) { m_stackedGuzai[m_stack - 1] = m_guzai; }

	/**
	 * @brief �v���C���[�̓L�b�`���Ńn���o�[�K�[������Ă���r����
	 * @return TRUE���쐬���B�L�b�`����̋�ނ��Ƃ�Ȃ�����B
	*/
	bool GetIsPlayerCookingOnKitchen() const { return m_isPlayerCookingOnKitchen; }

	/**
	 * @brief �L�b�`���̏�ɂ����Ԍ�ɒu���ꂽ��ނ��v���C���[�Ɏ�������B
	*/
	void TakePlayerLastestGuzai();

private:
	Player* m_player = nullptr;
	Burger* bur = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	CSoundSource* m_soundSource = nullptr;
	Meter* m_meter = nullptr;
	Counter* m_counter = nullptr;
	std::array<Guzai*, 5> m_stackedGuzai = { nullptr };					//�L�b�`���̏�ɂ�����
};

