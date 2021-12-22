#pragma once
#include "effect/Effect.h"
class CSoundSource;
class Effect;
class GuzaiOkiba;
class Kitchen;
class Meter;
class Player;
class PlayerGene;
class SkinModelRender;
class TrashCan;

/**
 * @brief ��ނ̃N���X
 * 7��ނ���B
*/
class Guzai : public IGameObject
{
private:
	Vector3 m_position = Vector3::Zero;					//��ނ̍��W
	Vector3 m_scale = Vector3::One;						//��ނ̊g�嗦
	const Vector3 m_TargetedScale = { 1.3f,1.3f,1.3f }; //�^�[�Q�b�g���ꂽ���̊g�嗦
	Quaternion m_rotation = Quaternion::Identity;		//��ނ̉�]
	int m_typeNo = 9;									//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g�@�T�D�I�j�I���@�U�D�x�[�R��
	int m_decrementTime = 10;							//HOLDTIME���҂����ԁBDECREMENTTIME�����X�Ɍ��炵�Ă�������������B
	int m_whichPlayerGet = 0;							//���̋�ނ͂ǂ���̃v���C���[�ɂ��܂ꂽ��
	int m_whichPlayerTargetMe = 0;						//�ǂ���̃v���C���[�Ƀ^�[�Q�b�g���ꂽ��
	int m_setKitchenNum = 9;							//���g���Z�b�g���ꂽ��ޒu����̔ԍ�
	int m_hold01 = 0;									//1P�̒������̎��ԁB
	int m_hold02 = 0;									//2P�̒������̎��ԁB
	int m_myNo = 100;									//�����̔ԍ�
	const int m_cookingTime = 60;						//�����ɂ����鎞�ԁB
	const int m_holdTime = 10;							//��x�^�[�Q�b�e�B���O�������̂�������x���߂邽�߂̎��ԁB
	const int m_targetRangeNear = 140;					//�^�[�Q�b�g����ŒZ�����B
	const int m_targetRangeFar = 150;					//�^�[�Q�b�e�B���O��؂�n�߂鋗���B�i���ۂ̓f�B���C�����邽�ߏ�����̂͂���������Ɛ�ɂȂ�j
	const static int m_maxGuzaiTypeNum = 7;
	const static int m_maxFilePathSize = 256;
	float m_guzai2Pl00 = 0.0f;							//��ނ���v���C���[1�ւ̋���
	float m_guzai2Pl01 = 0.0f;							//��ނ���v���C���[2�ւ̋���
	float m_kit2Pl00 = 0.0f;							//�L�b�`������v���C���[1�ւ̋���
	float m_kit2Pl01 = 0.0f;							//�L�b�`������v���C���[2�ւ̋���
	float m_angle = 0.0f;								//��]�̍ۂ̊p�x
	float m_adjustCutPos;
	bool m_isTargeted = false;							//�^�[�Q�e�B���O���ꂽ��ނ�ݒ肷��悤�B
	bool m_guzaiOkibaSet = false;						//���g����ޒu����ɃZ�b�g����Ă��邩�H
	bool m_isCooked = false;							//���g����������Ă��邩�H
	bool m_soundFlag01 = false;							//1P�̉���炵�����̃t���O
	bool m_soundFlag02 = false;							//2P�̉���炵�����̃t���O
	bool m_isSetOnTrashCan = false;						//�S�~���ɒu�����̂��ǂ���
	bool m_canPutOnGuzaiOkiba = true;					//��ޒu����ɂ������Ԃł��邩
	bool m_isHad = false;								//�P�Ȃ�Ύ�����Ă���B
	bool m_returnedFromKitchen = false;					//��x�L�b�`���ɒu����Ă���A�܂����ꂽ�Ƃ�
	bool m_isPutOnKitchen = false;						//TRUE�Ȃ�΂����L�b�`���ɒu����Ă���B

	//�ʏ펞�̃��f���̃p�X�W
	char m_normalFilePaths[m_maxGuzaiTypeNum][m_maxFilePathSize] = {
		"Assets/modelData/food/cheese.tkm",
		"Assets/modelData/food/egg.tkm",
		"Assets/modelData/food/lettuce.tkm",
		"Assets/modelData/food/patty.tkm",
		"Assets/modelData/food/tomato.tkm",
		"Assets/modelData/food/onion.tkm",
		"Assets/modelData/food/bacon.tkm",
	};

	//��ނ��L�b�`���ɉ^�΂ꂽ���̃��f���̃p�X�W
	char m_changedFilePaths[m_maxGuzaiTypeNum][m_maxFilePathSize] = {
		"Assets/modelData/food/cheese_kitchen.tkm",
		"Assets/modelData/food/egg_kitchen.tkm",
		"Assets/modelData/food/lettuce_kitchen.tkm",
		"Assets/modelData/food/patty_kitchen.tkm",
		"Assets/modelData/food/tomato_kitchen.tkm",
		"Assets/modelData/food/onion_kitchen.tkm",
		"Assets/modelData/food/bacon_kitchen.tkm",
	};

public:	
	Guzai() {};
	~Guzai();
	bool Start();
	void Update();

	/**
	 * @brief �n�_�P�ƒn�_�Q�̋������͂���
	 * @param pos1 �n�_�P
	 * @param pos2 �n�_�Q
	 * @return �Q�n�_�Ԃ̋���
	*/
	float CalcDistance(Vector3 pos1, Vector3 pos2);

	/**
	 * @brief �|�W�V�����̃Q�b�^�\
	 * @return ��ނ̈ʒu���W
	*/
	Vector3 GetPosition() const { return m_position; }

	Vector3 GetScale() { return m_scale; }

	/**
	 * @brief �����̋�ރi���o�[�̃Q�b�^�\
	 * @return ��ގ�ނ̔ԍ�
	*/
	int GetTypeNo() const { return m_typeNo; }
	/**
	 * @brief �����ɐݒ肳�ꂽ�ԍ������
	 * @return �}�C�i���o�[�̎擾
	*/
	int GetGuziNo() const { return m_myNo; }		
	/**
	 * @brief �����������ꂽ���ǂ�����Ԃ��B
	 * @return ������Ă��邩�ǂ����B
	*/
	bool GetisHadState() const { return m_isHad; }							
	/**
	 * @brief �ʒu���W��ݒ肷��B
	 * @param pos �ʒu���W
	*/
	void SetPosition(const Vector3 pos) { m_position = pos; }
	/**
	 * @brief �g�嗦��ݒ肷��B
	 * @param scale �g�嗦
	*/
	void SetScale(const Vector3 scale) { m_scale = scale; }
	/**
	 * @brief �ǂ���̃v���C���[�Ɏ�����Ă��邩��ݒ肷��B
	 * @param num �v���C���[�ԍ�
	*/
	void SetWhichPlayerGet(const int num) { m_whichPlayerGet = num; }
	/**
	 * @brief �����̔ԍ���ݒ肷��B
	 * @param number �}�C�i���o�[
	*/
	void SetGuzaiNo(const int number) { m_myNo = number; }					
	/**
	 * @brief �L�b�`���ɒu����Ă��邩�ǂ�����ݒ肷��B
	 * @param state �L�b�`���ɒu����Ă��遁TRUE�B
	*/
	void SetPutState(const bool isPut) { m_isPutOnKitchen = isPut; }			//�L�b�`���ɒu����Ă��邩�̕ϐ��̕ύX
	/**
	 * @brief �v���C���[�Ɏ�����Ă��邩�ǂ�����ݒ肷��B
	 * @param state �v���C���[�Ɏ�����Ă��遁TRUE�B
	*/
	void SetisHadState(const bool beHad) { m_isHad = beHad; }
	/**
	 * @brief �L�b�`������A���Ă�����ނ��ǂ�����ݒ肷��B
	 * @param state �L�b�`������A���Ă�����TRUE�B
	*/
	void SetReturnedState(const bool returned) { m_returnedFromKitchen = returned; }
	/**
	 * @brief �L�b�`���ɒu�����Ƃ��ɈႤ���f���ɍ����ւ���
	 * @param guzaiType ��ނ̎�ނ̔ԍ�
	*/
	void ChangeModel(const int guzaiType);
	/**
	 * @brief ��ނ�������
	*/
	void Grab();

	/**
	 * @brief �u������
	*/
	void Put();
	
	/**
	 * @brief ���͈͓��ň�ԋ߂���ނ��^�[�Q�b�g����
	*/
	void Targeting();
	/**
	 * @brief ��ޒu����ɒu���Ƃ��̏���
	*/
	void SetGuzaiOkiba();
	/**
	 * @brief ��ޒu���ꂩ����o�������B
	*/
	void AwayFromGuzaiOkiba();
	/**
	 * @brief ��ޒu����Œ������鏈���B
	*/
	void Cooking();
	/**
	 * @brief �S�~���̏�ɋ�ނ��Z�b�g��A�����B
	*/
	void SetOnTrashCan();
	/**
	 * @brief ��ނ̉�]�����B
	*/
	void Rotation();

	/**
	 * @brief �L�b�`�������ނ����ꂽ���̋�ނ̈ʒu���X�V
	*/
	void IfReturnedFromKitchen();

	/**
	 * @brief �v���C���[�̏��
	*/
	enum enPlayerState {
		enFullKitchen = -1,		//�L�b�`������t�̏�ԂŃ��[���̏ォ��͂Ƃ�Ȃ����A��ޒu���ꂩ�L�b�`���ォ��͂Ƃ��悤�ɂ���̂ɕK�v
		enNothing,				//���������Ă��Ȃ�
		enHaveGuzai,			//��ނ������Ă�����
		enHaveBurger,			//�n���o�[�K�[�������Ă�����
		enStateNum,				//�Ȃ肦���Ԃ̐�
	};

	/**
	 * @brief ��ނ̎�ރ��X�g
	*/
	enum enGuzaiType {
		enCheese,			//�O�D�`�[�Y
		enEgg,				//�P�D�G�b�O
		enLettuce,			//�Q�D���^�X�@
		enPatty,			//�R�D�p�e�@
		enTomato,			//�S�D�g�}�g
		enOnion,			//�T�D�I�j�I�� 
		enBacon,			//�U�D�x�[�R���@
		enGuzaiTypeNum		//��ނ̎�ސ�
	};
private:
	Player* m_player00 = nullptr;										//�v���C���[1�̃I�u�W�F�N�g�擾�p
	Player* m_player01 = nullptr;										//�v���C���[2�̃I�u�W�F�N�g�擾�p
	Kitchen* m_kitchen00 = nullptr;										//�L�b�`��1�̃I�u�W�F�N�g�擾�p
	Kitchen* m_kitchen01 = nullptr;										//�L�b�`��2�̃I�u�W�F�N�g�擾�p
	SkinModelRender* m_skinModelRender = nullptr;						//��ނ̃��f���ݒ�p
	PlayerGene* m_playerGene = nullptr;									//�v���C���[������̃I�u�W�F�N�g�擾�p
	GuzaiOkiba* m_guzaiOkiba = nullptr;									//�S��ޒu����̃I�u�W�F�N�g�擾�p
	std::array<TrashCan*, 2> m_trashCan = { nullptr, nullptr };			//�S�~���̃I�u�W�F�N�g�擾�p
	CSoundSource* m_cookingSe = nullptr;								//�����������̉�
	Meter* m_meter = nullptr;											//��������Ƃ��̃Q�[�W�p
};

