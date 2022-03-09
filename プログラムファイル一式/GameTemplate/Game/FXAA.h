#pragma once
class FXAA
{
private:
	//fxaa���|�����ʂ̏c�����f�[�^
	struct fxaa_data
	{
		float s_width;		//�}�b�v�̕�
		float s_height;		//�}�b�v�̍���
	};
public:
	/**
	 * @brief AA�쐬�̏��������s��
	 * @param rt AA���郌���_�����O�^�[�Q�b�g
	*/
	void Init(RenderTarget& rt);

	/**
	 * @brief �A���`�G�C���A�X����
	 * @param rc �����_�[�R���e�L�X�g
	 * @param TargetToApply �K�p�������^�[�Q�b�g
	*/
	void Render(RenderContext& rc, RenderTarget& TargetToApply);

private:
	Sprite m_finalSprite;			//�K�p�����摜
	fxaa_data s_data;				//fxaa���|�����ʂ̏c�����f�[�^
};

