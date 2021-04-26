#pragma once
//class ModelRender;
class Kitchen;
class SpriteRender;

class Player;

class PathMove;

class SkinModelRender;


class Guzai : public IGameObject
{
private:
	/*Model model;
	ModelInitData modeldata;
	CharacterController m_charaCon;*/
	Vector3 m_position = { 0.0f,0.0f,-1000.0f };
	Vector3 m_scale = Vector3::One;
	
	//��ނ������ʒu�i������j�Ɉړ����������B
	bool isSetFirstPos = false;
	//Update()�ŃC���N�������g����B
	int timer = 0;
	//X�{�^���������Őςݏグ�Ă����ނ�S���폜����B���̂��߂̃^�C�}�[�B
	int DeleteTimer = 0;
	//�ǂ������ɗ���Ă����ނ��B
	int GuzaiNo = 0;
	//�O�D�`�[�Y�@�P�D�G�b�O�@�Q�D���^�X�@�R�D�p�e�@�S�D�g�}�g
	int TypeNo = 9;
	//��ނ���v���C���[�ւ̋���
	float guzai2Pl = 0;
	//�L�b�`������v���C���[�ւ̋���
	float kit2Pl = 0.0f;
	
	//�^�[�Q�e�B���O�֘A
	//�^�[�Q�e�B���O���ꂽ��ނ�ݒ肷��悤�B
	bool targeted = false;
	//1�x�����_�~�[��ނ��o���Ȃ��悤�ɂ��邽�߂̕ϐ��B1�Ȃ�_�~�[�����łɏo�����B
	bool isSetTargetDummy = false;
	//��x�^�[�Q�b�e�B���O�������̂�������x���߂邽�߂̎��ԁB
	//HOLDTIME���҂����ԁBDECREMENTTIME�����X�Ɍ��炵�Ă�������������B
	const int holdTime = 10;
	int decrementTime = holdTime;
	//�^�[�Q�b�g����ŒZ�����B
	const int TargetRangeNear = 100;
	//�^�[�Q�b�e�B���O��؂�n�߂鋗���B�i���ۂ̓f�B���C�����邽�ߏ�����̂͂���������Ɛ�ɂȂ�j
	const int TargetRangeFar = 110;
	//�g�������̂��߂Ɏg�p
	Vector3 GuzaiScale = { 1.0f,1.0f,1.0f };
	//���̋�ނ͉��ł��邩�̃����p�A�^�[�Q�e�B���O�̃I�u�W�F�N�g���쐬���Ɏg�p�B
	const char* NowModelPath;

	//�ȉ��ǉ��R�[�h�B
	std::unique_ptr<PathMove> m_pathMove;		//�ړ��������s���N���X�B

public:	
	//������p���ċ�ނ����܂��Ɠ����ɂǂ̋�ނ𗬂����ݒ肷��B
	Guzai();
	~Guzai();
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale) { GuzaiScale = scale; }
	float GetGuzaiToPlayer() { return guzai2Pl; }

	//��ނ��L�b�`���ɒu�����Ƃ��ɃI�u�W�F�N�g���������߁A���߂ɐݒ肵�Ă�����TypeNo�������Ă��܂��B
	//�܂�A���[����ɏo�����I�u�W�F�N�g�ƐV�����L�b�`����ɏo���I�u�W�F�N�g���Ⴄ�B
	//�v���C���[���ɕۑ����Ă���TypeNo���L�b�`������NewGO����I�u�W�F�N�g�ɗ^���Ă��B
	//�����Ƀv���C���[�Ɋi�[����Ă����ރi���o�[��^����B
	void ChangeGuzai(int num);
	//�ǂ��瑤�ɗ���Ă����ނ��ݒ肷��B
	void SetGuzaiNo(int num) { GuzaiNo = num; }
	int GetGuzaiNo() { return GuzaiNo; }

	int GetTypeNo() { return TypeNo; }

	//��ނ̈ړ��B
	void Move();
	//��ނ̔���
	void GrabNPut();
	//�^�[�Q�e�B���O�̑ΏۑI��ƃ^�[�Q�b�g�_�~�[���o���B
	//�����ƕʂ̃^�[�Q�b�g��T���B
	void TargetingNPopDummy();
	//�^�[�Q�e�B���O����Ă����ނ̏�ɉ摜��z�u�B��Ɏg�p���邩������Ȃ��̂Ŏ������Ă����B�폜���邩��
	//void PopTargetingIcon();

	//void Render(RenderContext& rc) { model.Draw(rc); }

	//�P�Ȃ�Ύ�����Ă���B
	int state = 0;
	//�P�Ȃ�΂����L�b�`���ɒu����Ă���B
	int put = 0;

	/*ModelRender*/Player* pl01 = nullptr;
	/*ModelRender*/Player* pl02 = nullptr;
	Kitchen* ki01 = nullptr;
	Kitchen* ki02 = nullptr;
	SkinModelRender* m_skinModelRender;
	//�X�v���C�g��3D��ԕ\�����\�ɂȂ�����g�p
	/*SpriteRender* sp01 = nullptr;
	SpriteRender* sp02 = nullptr;*/
};

