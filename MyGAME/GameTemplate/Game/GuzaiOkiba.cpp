#include "stdafx.h"
#include "GuzaiOkiba.h"
#include "Level.h"
#include "Player.h"
#include "PlayerGene.h"
#include "Guzai.h"
#include "SkinModelRender.h"
#include "Kitchen.h"
#include "Arrow.h"

namespace 
{
	const Vector3 POS_ANYONE_CANT_REACH = Vector3::Zero;

	const int NAME_SIZE_STOCKRIGHT = 10;
	const int NAME_SIZE_STOCKLEFT = 9;
	const int AJUST_ARRAY_NUM_RIGHT = 1;
	const int AJUST_ARRAY_NUM_LEFT = 3;
	const int NUMBER_OF_OKIBA_RIGHT = 10;
	const int NUMBER_OF_OKIBA_LEFT = 9;
	const int GUZAIOKIBA_NUM_MIN = 0;
	const int GUZAIOKIBA_NUM_MIDDLE = 4;
	const int GUZAIOKIBA_NUM_MAX = 8;
	const int GUZAIOKIBA_NUMBER_ONE = 1;
	const int GUZAIOKIBA_NUMBER_TWO = 2;
	const int GUZAIOKIBA_NUMBER_THREE = 3;
	const int GUZAIOKIBA_NUMBER_FOUR = 4;
	const int HAVE_GUZAI = 1;

	const float CAN_TARGET_DISTANCE = 100.0f;
	const float CAN_TARGET_POS_Y = 100.0f;
	const float AJUST_ARROW_HEIGHT = 80.0f;
}

GuzaiOkiba::~GuzaiOkiba()
{
	//��ޒu����̃I�u�W�F�N�g������
	for (int i = GUZAIOKIBA_NUM_MIN; i < GUZAIOKIBA_NUM_MAX; i++) {
		DeleteGO(m_guzaiOkibaRender[i]);
	}
	//���v���C���[�p�̖�������
	DeleteGO(m_arrow00);
	DeleteGO(m_arrow01);
}

float GuzaiOkiba::TargetDistance(Vector3 v1, Vector3 v2)
{
	//�����v�Z�p�̊֐�
	Vector3 v3 = v1 - v2;
	float ans = v3.Length();

	return ans;
}

bool GuzaiOkiba::Start()
{
	m_player00 = FindGO<Player>("player00");
	m_player01 = FindGO<Player>("player01");

	Level level;

	//���x���f�[�^�����ޒu����̍��W���󂯎��A���f�����o���B
	//�s�ωӏ����`
	const wchar_t* StockRight = L"StockRight";
	const wchar_t* StockLeft = L"StockLeft";
	level.Init("Assets/level/level_new4.tkl", [&](ObjectData& objectData) {
		//�I�u�W�F�N�g�̖��O���r���āAStockRight����v������
		if (wcsncmp(objectData.name, StockRight, NAME_SIZE_STOCKRIGHT) == 0) {
			//���x����̃I�u�W�F�N�g�̔ԍ����擾
			int m_guzaiOkibaNo = _wtoi(&objectData.name[NUMBER_OF_OKIBA_RIGHT]);

			switch (m_guzaiOkibaNo)
			{
			case GUZAIOKIBA_NUMBER_ONE:
			case GUZAIOKIBA_NUMBER_TWO:
			case GUZAIOKIBA_NUMBER_THREE:
			case GUZAIOKIBA_NUMBER_FOUR: 
				//��ޒu����̃i���o�����O��1~4�̎��A��ޒu����̃C���X�^���X���쐬
				m_guzaiOkibaRender[m_guzaiOkibaNo - AJUST_ARRAY_NUM_RIGHT] = NewGO<SkinModelRender>(0);
				//�ʏ�`��p�̃��f��������
				m_guzaiOkibaRender[m_guzaiOkibaNo - AJUST_ARRAY_NUM_RIGHT]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_guzaiOkibaPos[m_guzaiOkibaNo - 1]);
				//�V���h�E�L���X�g�p�̏�����
				m_guzaiOkibaRender[m_guzaiOkibaNo - AJUST_ARRAY_NUM_RIGHT]->InitForCastShadow("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_guzaiOkibaPos[m_guzaiOkibaNo - 1], nullptr);
				//�ʒu�����x����Ɠ����ɂ���
				m_guzaiOkibaPos[m_guzaiOkibaNo - AJUST_ARRAY_NUM_RIGHT] = objectData.Pos;
				//�g�嗦�𒲐߁B
				m_guzaiOkibaRender[m_guzaiOkibaNo - AJUST_ARRAY_NUM_RIGHT]->SetScale(m_guzaiOkibaScale);
				return true;
				break;
			//�i���o�����O���������ł��Ă��Ȃ��Ƃ�
			default:
				//�����o���Ȃ�
				break;
			}
		}
		//�I�u�W�F�N�g�̖��O���r���āAStockLeft����v������
		if (wcsncmp(objectData.name, StockLeft, NAME_SIZE_STOCKLEFT) == 0) {
			//���x����̃I�u�W�F�N�g�̔ԍ����擾
			int m_guzaiOkibaNo = _wtoi(&objectData.name[NUMBER_OF_OKIBA_LEFT]);
			switch (m_guzaiOkibaNo)
			{
			case GUZAIOKIBA_NUMBER_ONE: 
			case GUZAIOKIBA_NUMBER_TWO:
			case GUZAIOKIBA_NUMBER_THREE:
			case GUZAIOKIBA_NUMBER_FOUR:
				m_guzaiOkibaRender[m_guzaiOkibaNo + AJUST_ARRAY_NUM_LEFT] = NewGO<SkinModelRender>(0);
				m_guzaiOkibaRender[m_guzaiOkibaNo + AJUST_ARRAY_NUM_LEFT]->Init("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_guzaiOkibaPos[m_guzaiOkibaNo - 1]);
				m_guzaiOkibaRender[m_guzaiOkibaNo + AJUST_ARRAY_NUM_LEFT]->InitForCastShadow("Assets/modelData/desk/desk_new.tkm", nullptr, enModelUpAxisZ, m_guzaiOkibaPos[m_guzaiOkibaNo - 1], nullptr);
				m_guzaiOkibaPos[m_guzaiOkibaNo + AJUST_ARRAY_NUM_LEFT] = objectData.Pos;
				m_guzaiOkibaRender[m_guzaiOkibaNo + AJUST_ARRAY_NUM_LEFT]->SetScale(m_guzaiOkibaScale);
				return true;
				break;
			default:
				break;
			}
		}
	
	});

	//��ޒu����ɋ߂Â����Ƃ��ɏo��������
	m_arrow00 = NewGO<Arrow>(0);
	//�PP���ɃZ�b�g
	m_arrow00->SetPosition(m_Arrow01Pos);
	m_arrow01 = NewGO<Arrow>(0);
	//�QP���ɃZ�b�g
	m_arrow01->SetPosition(m_Arrow02Pos);

	return true;
}

void GuzaiOkiba::PlayerDistance()
{
	//1P���̏��� 1P���̋�ޒu�����4�`7
	for (int i = GUZAIOKIBA_NUM_MIDDLE; i < GUZAIOKIBA_NUM_MAX; i++) {
		//�v���C���[�Ƌ�ޒu����̋��������
		m_distance[i] = TargetDistance(m_guzaiOkibaPos[i], m_player00->GetPosition());
	}

	//2P���̏��� 2P���̋�ޒu�����0�`3
	for (int i = GUZAIOKIBA_NUM_MIN; i < GUZAIOKIBA_NUM_MIDDLE; i++) {
		m_distance[i] = TargetDistance(m_guzaiOkibaPos[i], m_player01->GetPosition());
	}
}

void GuzaiOkiba::Targeted()
{
	//1P���̏���
	for (int i = GUZAIOKIBA_NUM_MIDDLE; i < GUZAIOKIBA_NUM_MAX; i++) {
		//�v���C���[�Ƌ�ޒu����̋��������ȉ��ŁA�^�[�Q�b�g���Ŗ����A��ނ��u����Ă��Ȃ��ꍇ�c
		if (m_distance[i] < CAN_TARGET_DISTANCE && m_targeted01 == false && m_guzaiSet[i] == false && m_player00->GetPlayerState() == HAVE_GUZAI) {
			//�^�[�Q�b�g���ɃA�N�Z�X�\�ȋ�ޒu����Ɉ��\�������邽�߂ɁA�^�[�Q�b�g���̋�ޒu����̍��W���L������B
			m_targetPos01 = m_guzaiOkibaPos[i];
			m_targetPos01.y += CAN_TARGET_POS_Y;
			//�^�[�Q�b�g��ԂɈڍs���A�^�[�Q�b�g�����ԍ��̋�ޒu����ɃA�N�Z�X�\�ɂ���B
			m_targeted01 = true;
			m_targetNo01 = i;
			m_guzaiOkibaSet[m_targetNo01] = true;
			m_Arrow01Pos = m_guzaiOkibaPos[m_targetNo01];
			m_Arrow01Pos.y += AJUST_ARROW_HEIGHT;
			m_arrow00->SetPosition(m_Arrow01Pos);
			//�^�[�Q�b�g���̏ꍇ�͋��������ȉ��ł����s����Ȃ��̂ŁA���������ɃA�N�Z�X���邱�Ƃ͂Ȃ��B
		}
	}
	//�^�[�Q�b�g���̏ꍇ�c
	if (m_targeted01 == true) {
		m_arrow00->Expansion();
		//�^�[�Q�b�g���̋�ޒu����ƃv���C���[�̋����𑪂�A���ȏ�ɂȂ����Ƃ��c
		m_targetDistance01 = TargetDistance(m_guzaiOkibaPos[m_targetNo01], m_player00->GetPosition());
		if (m_targetDistance01 >= CAN_TARGET_DISTANCE || m_guzaiSet[m_targetNo01] == true) {
			//�^�[�Q�b�g��Ԃ���߂�A�^�[�Q�b�g����������ޒu����ɑ΂��ăA�N�Z�X�s�\�ɂ���B
			m_targeted01 = false;
			m_guzaiOkibaSet[m_targetNo01] = false;
		}
	}
	//�^�[�Q�b�g���Ă��Ȃ��ꍇ�c
	else {
		//���̊g�嗦�����������Ă����A�����Ȃ��悤�ɂ���B
		m_arrow00->Shrink();
		m_targetPos01 = POS_ANYONE_CANT_REACH;
	}

	//2P���̏����A1P�Ƃقړ����B

	for (int i = GUZAIOKIBA_NUM_MIN; i < GUZAIOKIBA_NUM_MIDDLE; i++) {
		if (m_distance[i] < CAN_TARGET_DISTANCE && m_targeted02 == false && m_guzaiSet[i] == false && m_player01->GetPlayerState() == HAVE_GUZAI) {
			m_targetPos02 = m_guzaiOkibaPos[i];
			m_targetPos02.y += CAN_TARGET_POS_Y;
			m_targeted02 = true;
			m_targetNo02 = i;
			m_guzaiOkibaSet[m_targetNo02] = true;
			m_Arrow02Pos = m_guzaiOkibaPos[m_targetNo02];
			m_Arrow02Pos.y += AJUST_ARROW_HEIGHT;
			m_arrow01->SetPosition(m_Arrow02Pos);
		}
	}
	if (m_targeted02 == true) {
		m_arrow01->Expansion();
		m_targetDistance02 = TargetDistance(m_guzaiOkibaPos[m_targetNo02], m_player01->GetPosition());
		if (m_targetDistance02 >= CAN_TARGET_DISTANCE || m_guzaiSet[m_targetNo02]) {
			m_targeted02 = false;
			m_guzaiOkibaSet[m_targetNo02] = false;
		}
	}
	else {
		m_arrow01->Shrink();
		m_targetPos02 = POS_ANYONE_CANT_REACH;
	}
}


void GuzaiOkiba::Update()
{
	//�v���C���[�̏������
	if (m_player00 == nullptr) {
		m_player00 = FindGO<Player>("player00");
	}
	if (m_player01 == nullptr) {
		m_player01 = FindGO<Player>("player01");
	}

	PlayerDistance();

	Targeted();

	//��ޒu����̕\��
	for (int i = GUZAIOKIBA_NUM_MIN; i < GUZAIOKIBA_NUM_MAX; i++) {
		m_guzaiOkibaRender[i]->SetPosition(m_guzaiOkibaPos[i]);
	}
}