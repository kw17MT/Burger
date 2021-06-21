#pragma once
class Level;
class CLevel2D;
class FixedUI;
class SpriteRender;
class Guzai;
class GuzaiGene;
class GuzaiOkiba;
class Kitchen;
class Counter;
class Score;
class Result;
class FontRender;
class Level;
class DishGene;
class DishSpeedManeger;
class TrashCan;
class Floor;
class SoundSource;
class Player;
class PlayerGene;
class PostEffectTest;
class ShadowTest;
class Ground;
class CycleDirection;

class CountDown;

class Game : public IGameObject
{
private:
	Vector4 m_countDownColor = { 1.0f,1.0f,1.0f,0.0f };			//�J�E���g�_�E���摜�̃J���[

	bool m_isTimeUp = false;									//�Q�[���̓^�C���A�b�v������
	bool m_soundFlag = false;									//���݂Ȃ�炩�̉��͂Ȃ��Ă��邩�i�J�E���g�_�E���֌W�j
	bool m_fadeOut = false;										//�t�F�[�h�A�E�g���J�n���邩

	int m_changeCount = 1;										//�J�E���g�_�E����
	float m_scaleRate = 2.0f;									//
	float m_alpha = 0.0f;										//
	float m_timer = 4.0f;										//�J�E���g�_�E���p�B
public:
	//�I�u�W�F�N�g��UI�̕\��
	Game() {};
	~Game();

	bool Start();
	void Update();

	void DoWhenTimeUp();

	bool GetTimeUp() { return m_isTimeUp; }
	void SetTimeUp() { m_isTimeUp = true; }

private:
	CLevel2D* m_level2D = nullptr;
	FixedUI* ui = nullptr;											//���W�̓����Ȃ�UI�i���ԁA�X�R�A�A�~�X�j
	Counter* counter00 = nullptr;									//�J�E���^�\�P
	Counter* counter01 = nullptr;									//�J�E���^�\�Q
	Kitchen* kitchen00 = nullptr;									///�L�b�`���P
	Kitchen* kitchen01 = nullptr;									//�L�b�`���Q
	Player* player[2] = { nullptr,nullptr };						//���v���C���[
	PlayerGene* playerGene = nullptr;								//�v���C���[�𐶐��������
	GuzaiGene* guzaiGene = nullptr;									//��ނ𐶐��������
	Score* m_score = nullptr;										//�v���C���[�̃X�R�A��\������B
	GuzaiOkiba* guzaiOkiba = nullptr;								//��ޒu�����8�o��
	DishGene* dishGene = nullptr;									//�E�F�C�|�C���g�ɏ]���ĎM���o��
	DishSpeedManeger* m_speedManeger = nullptr;						//�M�̃X�s�[�h���Ǘ�����
	TrashCan* m_trashCan[2] = { nullptr, nullptr};					//�S�~��
	Floor* floor_r = nullptr;										//�E�̏�
	Floor* floor_l = nullptr;										//���̏�	
	Result* m_result[3] = { nullptr,nullptr,nullptr };				//���s�\���p:���������̏ꍇ�A�v���C���[1�A�v���C���[2�ɗp��
	CSoundSource* m_bgm = nullptr;									//BGM�p
	CycleDirection* m_directionSprite[3] = {nullptr,nullptr,nullptr};
	Level* m_level = nullptr;
	CountDown* m_countDown = nullptr;								//�J�E���g�_�E��
};