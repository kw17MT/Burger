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

	/**
	 * @brief �����ǂ�ȃV�[�����擾�B
	 * @return ���̃V�[����
	*/
	EnScene GetGameScene() const
	{
		return m_enScene;
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
};

//GameDirector�̃C���X�^���X���擾�B
static inline GameDirector& GetGameDirector()
{
	return GameDirector::GetInstance();
}



