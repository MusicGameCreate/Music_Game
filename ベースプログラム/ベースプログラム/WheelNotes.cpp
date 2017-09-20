#include "WheelNotes.h"

CWheelNotes::~CWheelNotes()
{
	CWheelNotes::Finalize();
}

void CWheelNotes::Initialize(char* fileName, LaneData data)
{
	CBaseNotes::Initialize(fileName, data);
}

void CWheelNotes::Finalize()
{
	CBaseNotes::Finalise();
}

void CWheelNotes::Update()
{
	CBaseNotes::Update();
}

void CWheelNotes::Draw()
{
	CBaseNotes::Draw();
}

// �z�C�[���m�[�c�����֐�(���[���f�[�^�A���[���������E���A���[�����ォ����)
void CWheelNotes::Create(int laneType, int laneNum, double CourceTime)
{
	if (m_bUse)// �g���Ă����琶�����Ȃ�
		return;
	m_Timer = CourceTime;
	//m_Timer.TimerInit(m_dMajorTime);
	//m_Timer.TimerActiv(false);
	m_nLaneType = laneNum;								// ���[���������E���i�[
	Tex_3D_Data[0].Obj_Rot = m_Data.m_vRad[m_nLaneType];	// ���[���̌X���ɍ��킹�ăm�[�c���X����

	if (m_nLaneType == 0)
	{// �����[���ɐ���
		if (laneType == 0)
		{// �ヌ�[���ɐ���
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z + (m_Data.m_vTexSize.y / 2)) + (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
		else if (laneType == 1)
		{// �����[���ɐ���
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z - (m_Data.m_vTexSize.y / 2)) - (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
	}
	else if (m_nLaneType == 1)
	{// �E���[���ɐ���
		if (laneType == 0)
		{// �ヌ�[���ɐ���
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z + (m_Data.m_vTexSize.y / 2)) + (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
		else if (laneType == 1)
		{// �����[���ɐ���
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z - (m_Data.m_vTexSize.y / 2)) - (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
	}

	Tex_3D_Data[0].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bUse = true;	// �g�p�t���O�𗧂Ă�
}