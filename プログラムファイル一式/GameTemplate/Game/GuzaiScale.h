#pragma once
class GuzaiScale
{
public:
	/**
	 * @brief ��ނ̃^�[�Q�b�g��Ԃɂ��A�g�嗦��ύX������B
	 * @param isTargeted �^�[�Q�b�g����Ă��邩�ǂ���
	 * @param typeNumber ��ނ̎�ޔԍ�
	 * @param nowScale ���݂̊g�嗦
	 * @return 
	*/
	static Vector3 ChangeScaleDependOnTargetedState(bool isTargeted, int typeNumber, Vector3 nowScale);
};

