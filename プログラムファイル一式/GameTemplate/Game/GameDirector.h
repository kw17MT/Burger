#pragma once

enum EnScene
{
	enNonScene = -1,	//�^�C�g��
	enGameCountDown,	//�Q�[���J�n�O�̃J�E���g�_�E���B
	enGamePlay,			//�Q�[���v���C���B
	enPause,			//�|�[�Y��
	enResult,			//���U���g��
	enGameEnd,			//�Q�[���I��
	enSceneNumber
};

enum EnResult
{
	enPlayer1Win,
	enPlayer2Win,
	enDraw
};

/// <summary>
/// �Q�[���̃V�[����m���Ă�N���X�B
/// </summary>
class GameDirector
{
private:
	GameDirector() {}
	~GameDirector() {}
public:
	/**
	 * @brief GameDirector�̃C���X�^���X���擾�B
	 * @return GameDirector�̃C���X�^���X
	*/
	static GameDirector& GetInstance()
	{
		static GameDirector instance;
		return instance;
	}

	//�Q�[���V�[����ݒ�B

	/**
	 * @brief 
	 * @param enScene 
	*/
	void SetGameScene(EnScene enScene)
	{
		m_enScene = enScene;
	}

	void SetResult(EnResult enResult)
	{
		m_result = enResult;
	}

	/**
	 * @brief �����ǂ�ȃV�[�����擾�B
	 * @return ���̃V�[����
	*/
	EnScene GetGameScene() const
	{
		return m_enScene;
	}

	EnResult GetResult() const
	{
		return m_result;
	}

	/**
	 * @brief �J�E���g�_�E�����H
	 * @return �O���J�E���g�_�E����
	*/
	bool GetIsGameCountDown() const
	{
		return m_enScene == enGameCountDown;
	}

	/**
	 * @brief �Q�[���v���C���H
	 * @return �P���v���C��
	*/
	bool GetIsGamePlay() const
	{
		return m_enScene == enGamePlay;
	}
private:
	EnScene m_enScene = enNonScene;
	EnResult m_result = enPlayer1Win;
};

//GameDirector�̃C���X�^���X���擾�B
static inline GameDirector& GetGameDirector()
{
	return GameDirector::GetInstance();
}