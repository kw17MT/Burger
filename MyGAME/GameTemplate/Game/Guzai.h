#pragma once

class Kitchen;
class SkinModelRender;
class Player;
class PlayerGene;
class PathMove;
class GuzaiGene;

class Guzai : public IGameObject
{
private:
	Vector3 m_position = { 0.0f,0.0f,-1000.0f };
	Vector3 m_scale = Vector3::One;
	//具材の枠線の拡大率
	const Vector3 expantionRate = { 0.3f,0.3f,0.3f };
	
	//Update()でインクリメントする。
	int timer = 0;
	//Xボタン長押しで積み上げている具材を全部削除する。そのためのタイマー。
	int DeleteTimer = 0;
	//０．チーズ　１．エッグ　２．レタス　３．パテ　４．トマト
	int TypeNo = 9;
	//具材からプレイヤーへの距離
	float guzai2Pl01 = 0.0f;
	float guzai2Pl02 = 0.0f;
	//キッチンからプレイヤーへの距離
	float kit2Pl01 = 0.0f;
	float kit2Pl02 = 0.0f;
	
	//ターゲティング関連
	//ターゲティングされた具材を設定するよう。
	bool targeted = false;
	//1度しかダミー具材を出さないようにするための変数。1ならダミーをすでに出した。
	bool isSetTargetDummy = false;
	//一度ターゲッティングしたものをある程度見つめるための時間。
	//HOLDTIMEが待ち時間。DECREMENTTIMEが徐々に減らしていく役割がある。
	const int holdTime = 10;
	int decrementTime = holdTime;
	//ターゲットする最短距離。
	const int TargetRangeNear = 100;
	//ターゲッティングを切り始める距離。（実際はディレイがあるため消えるのはもうちょっと先になる）
	const int TargetRangeFar = 110;
	//枠線強調のために使用
	Vector3 GuzaiScale = { 1.0f,1.0f,1.0f };
	//その具材は何であるかのメモ用、ターゲティングのオブジェクトを作成時に使用。
	const char* NowModelPath;

	//以下追加コード。
	std::unique_ptr<PathMove> m_pathMove;		//移動処理を行うクラス。

	//その具材はどちらのプレイヤーにつかまれたか
	int whichPlayerGet = 0;
	//どちらのプレイヤーにターゲットされたか
	int whichPlayerTargetMe = 0;
	//1~36
	int dishNumber = 0;

public:	
	//乱数を用いて具材が生まれると同時にどの具材を流すか設定する。
	Guzai();
	~Guzai();
	bool Start();
	void Update();
	
	Vector3 GetPosition();
	void SetPosition(Vector3 pos);
	void SetScale(Vector3 scale) { GuzaiScale = scale; }

	//具材をキッチンに置いたときにオブジェクトを消すため、初めに設定しておいたTypeNoも消えてしまう。
	//つまり、レーン上に出したオブジェクトと新しくキッチン上に出すオブジェクトが違う。
	//プレイヤー側に保存しているTypeNoをキッチン側でNewGOするオブジェクトに与えてやる。
	//引数にプレイヤーに格納されている種類ナンバーを与える。
	void ChangeGuzai(int num);

	int GetTypeNo() { return TypeNo; }

	//具材の移動。
	void Move();
	//具材の搬送
	void GrabNPut();
	//ターゲティングの対象選定とターゲットダミーを出す。
	//離れると別のターゲットを探す。
	void TargetingNPopDummy();
	//置かれた皿番号を記録する。
	void SetDishNumber(int num) { dishNumber = num; }

	//１ならば持たれている。
	int state = 0;
	//１ならばもうキッチンに置かれている。
	int put = 0;

	Player* pl01 = nullptr;
	Player* pl02 = nullptr;
	Kitchen* ki01 = nullptr;
	Kitchen* ki02 = nullptr;
	SkinModelRender* m_skinModelRender;
	PlayerGene* playerGene;
	GuzaiGene* m_guzaiGene;
};

