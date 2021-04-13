#pragma once

enum EnScene
{
	enNonScene = -1,
	enGameCountDown = 0,	//�Q�[���J�n�O�̃J�E���g�_�E���B
	enGamePlay = 1,		//�Q�[���v���C���B
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
	//GameDirector�̃C���X�^���X���擾�B
	static GameDirector& GetInstance()
	{
		static GameDirector instance;
		return instance;
	}

	//�Q�[���V�[����ݒ�B
	void SetGameScene(EnScene enScene)
	{
		m_enScene = enScene;
	}
	
	//�����ǂ�ȃV�[�����擾�B
	EnScene GetGameScene() const
	{
		return m_enScene;
	}
	
 	//�J�E���g�_�E�����H
	bool GetIsGameCountDown() const
	{
		return m_enScene == enGameCountDown;
	}

	//�Q�[���v���C���H
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



