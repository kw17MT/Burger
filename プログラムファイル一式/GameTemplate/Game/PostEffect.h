#pragma once
#include "Bloom.h"
#include "FXAA.h"

/**
 * @brief �|�X�g�G�t�F�N�g���ꊇ�ōs���N���X
*/
class PostEffect
{
public:
	/**
	 * @brief �|�X�g�G�t�F�N�g�Ŏg�p����Q�[����ʃ����_�[�^�[�Q�b�g��ݒ肷��
	 * @param mainRenderTarget �Q�[�����
	*/
	void Init(RenderTarget& mainRenderTarget);

	/**
	 * @brief �|�X�g�G�t�F�N�g���쐬�A�`�悷��
	 * @param rc �����_�[�R���e�L�X�g
	 * @param TargetToApply �K�p�������Q�[�����
	*/
	void Render(RenderContext& rc, RenderTarget& TargetToApply);
private:
	Bloom m_bloom;	//�u���[���쐬�C���X�^���X
	FXAA m_fxaa;	//FXAA�쐬�C���X�^���X
};