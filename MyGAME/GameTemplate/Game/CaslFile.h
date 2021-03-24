#pragma once
#include <list>
#include <vector>

struct CaslData {
	//���x���̒��̉摜�̖��O
	std::unique_ptr<char[]> name;
	//���x���̃t�@�C���̃p�X�B
	std::unique_ptr<char[]> filePath;
	//DDS�̃t�@�C���̃p�X�B
	std::unique_ptr<char[]> ddsFilePath;
	//���W�A�g�嗦�B
	Vector2 position;
	Vector2 scale;
	//�����A�c���A���C���[�̗D��x
	int width;
	int height;
	int numberLayer = 0;
};
class CaslFile
{
private:
	//1���������ǂݍ��ނ̂Ɏg���B
	// , �� \n�@��ǂݍ��ނ̂Ɏg���B
	void ReadOnlyOneCharacter(FILE* file) const;
	//int�^��ǂݍ��ނ̂Ɏg���B
	int ReadInteger(FILE* file) const;
	//float�^��ǂݍ��ނ̂Ɏg���B
	float ReadDecimal(FILE* file) const;

	std::vector<std::unique_ptr<CaslData>> m_caslDataList;		//Casl�f�[�^�B

public:
	//Casl�t�@�C�������[�h����B
	void Load(const char* filePath);
	//Casl�f�[�^�̐���Ԃ��B����const�͂��̃����o�֐��̓����o�ϐ���ύX���Ȃ��Ƃ����Ӗ��B
	const int GetNumCaslData() const
	{
		return m_caslDataList.size();
	}
	//number�ڂ�Casl�f�[�^���擾����B
	CaslData* GetCaslData(int number) const {
		return m_caslDataList[number].get();
	}
};

