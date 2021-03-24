#pragma once

#include "MapChip2D.h"

struct CaslData;

struct Level2DObjectData {
	//���W�B�O�ŏ�����
	Vector3 position = Vector3::Zero;
	//��]�B�O�ŏ�����
	Quaternion rotation = Quaternion::Identity;
	//�g�嗦�B�P�ŏ�����
	Vector3 scale = Vector3::One;
	int width = 0;
	int height = 0;
	const char* name;
	const char* ddsFilePath;

	//���x���̓��̃I�u�W�F�N�g�̖��O�𒲂ׂē������i�O�j�Ȃ��TURE
	bool EqualObjectName(const char* objName) const
	{
		return strcmp(objName, name) == 0;
	}

	bool ForwardMatchName(const char* n) const
	{
		auto len = strlen(n);
		auto namelen = strlen(name);
		if (len > namelen) {
			return false;
		}
		return strncmp(n, name, len) == 0;
	}
};

class Level2D {
private:
	using MapChip2DPtr = std::unique_ptr<MapChip2D>;
public:
	void Init(const char* filePath, std::function<bool(Level2DObjectData& objData)> hookFunc);

	void Update() const;
	/// �}�b�v�`�b�v2D�̕`�揈���B
	void Draw(RenderContext& renderContext) const;
private:
	/// �}�b�v�`�b�v2D��ǉ�����B
	void AddMapChip2D(CaslData* caslData);
private:
	std::vector<MapChip2DPtr> m_mapChip2DPtrList;		//�}�b�v�`�b�v2D�B
};