#include "stdafx.h"
#include "CaslFile.h"
#include <string>
//#include "ExEngine.h"

void CaslFile::Load(const char* filePath)
{
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		MessageBoxA(nullptr, "casl�t�@�C���̃I�[�v���Ɏ��s���܂����B", "�G���[", MB_OK);
		return;
	}

	int numLevel = ReadInteger(fp);
	for (int i = 0; i < numLevel; i++)
	{
		//std::unique_ptr<Level2DObject> levelOnject;�Ɠ����Ӗ�
		//���x���t�@�C���ɕۑ����Ă���̂́A�ȉ��S��char�^�ŕۑ����Ă���B
		//����(,)�ŋ�؂肪���Ă���B
		//���O�̒���(int)�A���O(char)�A�t�@�C���p�X�̒���(int)�A�t�@�C���p�X(char)
		//���Wx,y(float)
		//�摜�̑傫��x,y(int)
		//���C���[�D��xx,y(int)
		//�X�P�[���{��x,y(float)
		//��̒l���\���̂ɋL�^�����B
		auto caslData = std::make_unique<CaslData>();

		//�摜�̖��O�̒������擾����B
		int nameCount = ReadInteger(fp);
		//�摜�̖��O���擾����B
		caslData.get()->name = std::make_unique<char[]>(nameCount + 1);
		fread(caslData.get()->name.get(), nameCount, 1, fp);
		ReadOnlyOneCharacter(fp);

		//�t�@�C���p�X�̖��O�̒������擾�B
		int fileNameCount = ReadInteger(fp);
		//�t�@�C���p�X���擾�B
		caslData.get()->filePath = std::make_unique<char[]>(fileNameCount + 1);
		fread(caslData.get()->filePath.get(), fileNameCount, 1, fp);
		ReadOnlyOneCharacter(fp);

		//���W���擾�B
		caslData.get()->position.x = ReadDecimal(fp);
		caslData.get()->position.y = ReadDecimal(fp);

		//���ƍ������擾�B
		caslData.get()->width = ReadInteger(fp);
		caslData.get()->height = ReadInteger(fp);

		//���C���[�D��x���擾�B
		caslData.get()->numberLayer = ReadInteger(fp);

		//�傫���̔{�����擾�B
		caslData.get()->scale.x = ReadDecimal(fp);
		caslData.get()->scale.y = ReadDecimal(fp);

		//dds�t�@�C���p�X�̖��O�̒������擾�B
		int ddsFileNameCount = ReadInteger(fp);
		//dds�t�@�C���p�X���擾�B
		caslData.get()->ddsFilePath = std::make_unique<char[]>(ddsFileNameCount + 1);
		fread(caslData.get()->ddsFilePath.get(), ddsFileNameCount, 1, fp);


		//ReadOnlyOneCharacter(fp);
		//���s�R�[�h��ǂݔ�΂��B
		char dummy[256];
		fgets(dummy, 256, fp);

		m_caslDataList.push_back(std::move(caslData));
	}
}

void CaslFile::ReadOnlyOneCharacter(FILE* file) const
{
	char a;
	fread(&a, 1, 1, file);
}

int CaslFile::ReadInteger(FILE* file) const
{
	std::string number;
	while (true)
	{
		char c;
		fread(&c, 1, 1, file);
		if (c != ',' && c != '\n')
		{
			number += c;
		}
		else {
			break;
		}
	}
	//string�^��int�^�ɕϊ�����B
	return atoi(number.c_str());
}

float CaslFile::ReadDecimal(FILE* file) const
{
	std::string number;
	while (true)
	{
		char c;
		fread(&c, 1, 1, file);
		if (c != ',' && c != '\n')
		{
			number += c;
		}
		else {
			break;
		}
	}
	//string�^��float�^�ɕϊ�����B
	return atof(number.c_str());
}