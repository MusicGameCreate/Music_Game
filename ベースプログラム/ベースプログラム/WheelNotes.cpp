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

// ホイールノーツ生成関数(レーンデータ、レーンが左か右か、レーンが上か下か)
void CWheelNotes::Create(int laneType, int laneNum, double CourceTime)
{
	if (m_bUse)// 使っていたら生成しない
		return;
	m_Timer = CourceTime;
	//m_Timer.TimerInit(m_dMajorTime);
	//m_Timer.TimerActiv(false);
	m_nLaneType = laneNum;								// レーンが左か右か格納
	Tex_3D_Data[0].Obj_Rot = m_Data.m_vRad[m_nLaneType];	// レーンの傾きに合わせてノーツも傾ける

	if (m_nLaneType == 0)
	{// 左レーンに生成
		if (laneType == 0)
		{// 上レーンに生成
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z + (m_Data.m_vTexSize.y / 2)) + (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
		else if (laneType == 1)
		{// 下レーンに生成
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z - (m_Data.m_vTexSize.y / 2)) - (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
	}
	else if (m_nLaneType == 1)
	{// 右レーンに生成
		if (laneType == 0)
		{// 上レーンに生成
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z + (m_Data.m_vTexSize.y / 2)) + (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
		else if (laneType == 1)
		{// 下レーンに生成
			Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[m_nLaneType].z - (m_Data.m_vTexSize.y / 2)) - (Tex_3D_Data[0].Obj_Size.y / 2));
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
		}
	}

	Tex_3D_Data[0].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bUse = true;	// 使用フラグを立てる
}