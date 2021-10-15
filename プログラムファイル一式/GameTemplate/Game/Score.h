#pragma once
class FixedUI;
class FontRender;
class CSoundSource;

class Score : public IGameObject
{
private:
	Vector2 m_score00Pos = { -400.0f,-250.0f };					//1P�p�̈ʒu
	Vector2 m_score01Pos = { 450.0f,-250.0f };					//2P�p�̈ʒu

	int m_score00 = 0;											//�ŏI�I�ɕ\������X�R�A�@���@��ނ̐� * 100
	int m_score01 = 0;											//�ŏI�I�ɕ\������X�R�A�@���@��ނ̐� * 100
	int m_basePoint00 = 0;										//�J�E���^�[���ŉ��w�̃n���o�[�K�[��񋟂������B
	int m_basePoint01 = 0;										//�񋟂�����ނ𐔂��Ă����B
	
	bool m_isTimeUp = false;									//�^�C���A�b�v�t���O
	bool m_isChangeColor00 = false;								//�����̐F��ς���ׂ��������łȂ���
	bool m_isChangeColor01 = false;								//�����̐F��ς���ׂ��������łȂ���
			
	std::wstring m_nowScore00 = L"0";							//�v���C���[1�̌��݂̃X�R�A
	std::wstring m_prevScore00 = L"0";							//�v���C���[1�̑O�̃X�R�A
	std::wstring m_nowScore01 = L"0";							//�v���C���[2�̌��݂̃X�R�A
	std::wstring m_prevScore01 = L"0";							//�v���C���[2�̑O�̃X�R�A

public:
	//���s�̏��
	//�v���C���[1

	/**
	 * @brief �v���C���[1�̏��s�̏��
	*/
	enum EnResultP1 {
		enResultP1_draw,	//0
		enResultP1_win,		//1
		enResultP1_lose,	//2
		enResultP1Num		//�_�~�[(3)
	}ResultP1;

	/**
	 * @brief �v���C���[2�̏��s�̏��
	*/
	enum EnResultP2 {
		enResultP2_draw,	//0
		enResultP2_win,		//1
		enResultP2_lose,	//2
		enResultP2Num		//�_�~�[(3)
	}ResultP2;

	~Score();

	/**
	 * @brief �X�R�A�̃e�L�X�g�f�[�^�̏�����
	 * @return true
	*/
	bool Start();

	/**
	 * @brief ���w�̃n���o�[�K�[���o�ł�����
	 * @param num �n���o�[�K�[�̑w
	*/
	void SetBasePoint01(int num) { m_basePoint00 += num; }

	/**
	 * @brief ���w�̃n���o�[�K�[���o�ł�����
	 * @param num �n���o�[�K�[�̑w
	*/
	void SetBasePoint02(int num) { m_basePoint01 += num; }

	/**
	 * @brief �^�C���A�b�v���̌��ʂ��L�^
	*/
	void SetResult();

	/**
	 * @brief �v���C���[1�̓_����Ԃ�
	 * @return �v���C���[1�̓_��
	*/
	int GetPlayer00Score() const { return m_score00; }

	/**
	 * @brief �v���C���[2�̓_����Ԃ�
	 * @return �v���C���[2�̓_��
	*/
	int GetPlayer01Score() const { return m_score01; }

	/**
	 * @brief �^�C���A�b�v�t���O��true�ɂ���
	*/
	void SetIsTimeUp() { m_isTimeUp = true; }

	/**
	 * @brief �X�R�A�̌v�Z���s�������ƁA���Z����Ă����琔���̐F�������\���̂��߂ɕς���
	*/
	void AddScoreNChangeColor();

	/**
	 * @brief �^�C���A�b�v�ɂȂ����瓾�_����łȂ�̉摜���o�������߂�
	*/
	void Update();
private:
	
	FixedUI* m_ui = nullptr;								//�Q�[�����^�C���A�b�v���Ă��邩�ǂ����m�邽��
	FontRender* m_score[2] = { nullptr, nullptr };			//�X�R�A�̕\���p
	CSoundSource* m_moneySound = nullptr;					//�L���b�V���[�̉��p
};

