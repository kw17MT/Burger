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

//class PopUp2D;
class Game : public IGameObject
{
private:
	bool isTimeUp = false;
	int StockPlaceNum = 0;
	bool m_soundFlag00 = false; //0�̉������Ă��邩�H
	bool m_soundFlag01 = false; //1�̉������Ă��邩�H
	bool m_soundFlag02 = false; //2�̉������Ă��邩�H
	bool m_soundFlag03 = false; //3�̉������Ă��邩�H
public:
	//�I�u�W�F�N�g��UI�̕\��
	Game();
	~Game();

	bool Start();
	void Update();

	//�J�E���g�_�E������B
	void CountDown();

	CLevel2D* m_level2D = nullptr;
	FixedUI* ui = nullptr;											//���W�̓����Ȃ�UI�i���ԁA�X�R�A�A�~�X�j
	Counter* counter01 = nullptr;									//�J�E���^�\�P
	Counter* counter02 = nullptr;									//�J�E���^�\�Q
	Kitchen* kitchen01 = nullptr;									///�L�b�`���P
	Kitchen* kitchen02 = nullptr;									//�L�b�`���Q
	//SpriteRender* menu[3];										//���j���[�\���R����
	Player* player[2] = { nullptr };								//���v���C���[
	PlayerGene* playerGene = nullptr;								//�v���C���[�𐶐��������
	GuzaiGene* guzaiGene = nullptr;									//��ނ𐶐��������
	Score* m_score = nullptr;										//�v���C���[�̃X�R�A��\������B
	GuzaiOkiba* guzaiOkiba =  nullptr;								//��ޒu�����8�o��
	DishGene* dishGene = nullptr;									//�E�F�C�|�C���g�ɏ]���ĎM���o��
	DishSpeedManeger* m_speedManeger = nullptr;						//�M�̃X�s�[�h���Ǘ�����
	TrashCan* m_trashCan[2] = { nullptr };							//�S�~��
	Floor* floor_r = nullptr;										//�E�̏�
	Floor* floor_l = nullptr;										//���̏�	
	Result* m_result[3] = { nullptr };								//���s�\���p:���������̏ꍇ�A�v���C���[1�A�v���C���[2�ɗp��
	FontRender* m_font = nullptr;									//�t�H���g
	CSoundSource* m_bgm = nullptr;									//BGM�p
	CycleDirection* m_directionSprite[3] = {nullptr};
	Level* m_level = nullptr;

	//�������牺�͂���Ȃ��Ǝv��
	PostEffectTest* postTest = nullptr;
	ShadowTest* shadowTest = nullptr;
	Ground* ground = nullptr;

	//PopUp2D* m_popup2D_1 = nullptr;
	//PopUp2D* m_popup2D_2 = nullptr;

	bool GetTimeUp() { return isTimeUp; }
	void SetTimeUp() { isTimeUp = true; }

	//�J�E���g�_�E���p�B
	float m_timer = 4.0f;
	//FontRender* m_font;
	
	//�J�E���g�_�E���p�X�v���C�g
	SpriteRender* m_countSprite = nullptr;
	Vector3 m_ctScale = Vector3::One;
	int changeCount = 3;
	float scaleRate = 2.0f;
	float alpha = 0.0f;
	bool fadeOut = false;
};