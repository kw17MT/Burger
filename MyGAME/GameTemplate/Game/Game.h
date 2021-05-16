#pragma once
class Level;
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
class PostEffectTest;
class TrashCan;


class ShadowTest;
class Ground;

class Player;
class PlayerGene;
//class PopUp2D;

class DishGene;
class DishSpeedManeger;

class Floor;
class SoundSource;
	
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

	//���͓��ɖ����Ȃ��B
	void Update();

	//�J�E���g�_�E������B
	void CountDown();

	FixedUI* ui;
	Counter* counter01;
	Counter* counter02;
	Kitchen* kitchen01;
	Kitchen* kitchen02;
	SpriteRender* menu[3];
	SpriteRender* Buff[2];
	Player* player[2];
	PlayerGene* playerGene;
	GuzaiGene* guzaiGene;
	Score* m_score = nullptr;
	PostEffectTest* postTest;

	ShadowTest* shadowTest;
	Ground* ground;

	GuzaiOkiba* guzaiOkiba;

	DishGene* dishGene;
	DishSpeedManeger* m_speedManeger;
	//PopUp2D* m_popup2D_1 = nullptr;
	//PopUp2D* m_popup2D_2 = nullptr;

	TrashCan* m_trashCan[2];
	Floor* floor_r;
	Floor* floor_l;

	//���s�\���p:���������̏ꍇ�A�v���C���[1�A�v���C���[2�ɗp��
	Result* m_result[3];

	bool GetTimeUp() { return isTimeUp; }
	void SetTimeUp() { isTimeUp = true; }

	//�J�E���g�_�E���p�B
	float m_timer = 4.0f;
	FontRender* m_font;


};