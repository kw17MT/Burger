#pragma once
class AjustGuzaiPosition
{
public:
	/**
	 * @brief ��ނ̈ʒu���v���C���[�̑O�ɂ���
	 * @param normalizedSpeed ���K�����ꂽ�v���C���[�̈ړ����x
	 * @param playerPosition ���݂̃v���C���[�̈ʒu
	 * @return �v���C���[�̑O���̍��W
	*/
	static Vector3 CalcAjustedPosition(Vector3 normalizedSpeed, Vector3 playerPosition);
};

