#include "LongNotes.h"
#include "TimeServer.h"

CLongNotes::~CLongNotes()
{
	CLongNotes::Finalize();
}

void CLongNotes::Initialize(char* fileName, LaneData data)
{
	NotesNum = 1;
	//HitFlag = false;
	MissFlag = false;
	DecitionFlag = false;
	UpdateFlag = false;
	CBaseNotes::Initialize(fileName, data);
}

void CLongNotes::Finalize()
{
	CBaseNotes::Finalise();
}

void CLongNotes::Update()
{
	if (!m_bUse)
		return;
	double timer = CTimeServer::GetDifference();
	float t = 0.0f;
	if (m_Timer < m_dLifeTime)
	{
		if (m_Timer + timer >= m_dLifeTime)
		{
			t = m_dLifeTime - m_Timer;
			UpdateFlag = true;
		}
	}
	m_Timer += timer;

	if (m_Timer < m_dLifeTime)
	{// 判定時間以前
		switch (m_nLaneType)
		{
		case LANE_LEFT:
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * timer;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * timer;
			//Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed) - TriDelta.x / 2) + ((m_Data.m_vTriSize.x * ((m_Timer / m_dMajorTime))) * m_dHiSpeed);
			//Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2) + ((m_Data.m_vTriSize.y * ((m_Timer / m_dMajorTime))) * m_dHiSpeed);
			//Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed) - TriDelta.x/2) + ((m_Data.m_vTriSize.x * (m_Timer / m_dMajorTime)) * m_dHiSpeed);
			//Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y/2) + ((m_Data.m_vTriSize.y * (m_Timer / m_dMajorTime)) * m_dHiSpeed);
			break;
		case LANE_RIGHT:
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * timer;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * timer;
			//Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed) + TriDelta.x/2) - ((m_Data.m_vTriSize.x * (m_Timer / m_dMajorTime)) * m_dHiSpeed);
			//Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y/2) + ((m_Data.m_vTriSize.y * (m_Timer / m_dMajorTime)) * m_dHiSpeed);
			break;
		default:
			break;
		}
	}
	else
	{// 判定時間後
		if (!UpdateFlag)
		{
			switch (m_nLaneType)
			{
			case LANE_LEFT:
				Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * (timer / 2);
				Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * (timer / 2);
				//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[0].x + ((m_Data.m_vTriSize.x / 2) * m_dHiSpeed)) + ((m_vNotexVec.x) * (m_Timer - m_dMajorTime))/2;
				//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[0].y + ((m_Data.m_vTriSize.y / 2) * m_dHiSpeed)) + ((m_vNotexVec.y) * (m_Timer - m_dMajorTime))/2;
				//Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed) - TriDelta.x / 2) + ((m_Data.m_vTriSize.x * m_dHiSpeed) + ((m_Data.m_vTriSize.x * (((m_Timer / m_dMajorTime)) - 1)) * (m_dHiSpeed / 2)));
				//Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2) + ((m_Data.m_vTriSize.y * m_dHiSpeed) + ((m_Data.m_vTriSize.y * (((m_Timer / m_dMajorTime)) - 1)) * (m_dHiSpeed / 2)));
				break;
			case LANE_RIGHT:
				Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * (timer / 2);
				Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * (timer / 2);
				//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[1].x - ((m_Data.m_vTriSize.x / 2) * m_dHiSpeed)) - ((m_vNotexVec.x) * (m_Timer - m_dMajorTime))/2;
				//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[1].y + ((m_Data.m_vTriSize.y / 2) * m_dHiSpeed)) + ((m_vNotexVec.y) * (m_Timer - m_dMajorTime))/2;
				//Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed) + TriDelta.x / 2) - ((m_Data.m_vTriSize.x * m_dHiSpeed) + ((m_Data.m_vTriSize.x * (((m_Timer / m_dMajorTime)) - 1)) * (m_dHiSpeed / 2)));
				//Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2) + ((m_Data.m_vTriSize.y * m_dHiSpeed) + ((m_Data.m_vTriSize.y * (((m_Timer / m_dMajorTime)) - 1)) * (m_dHiSpeed / 2)));
				break;
			default:
				break;
			}
		}
		else
		{
			UpdateFlag = false;
			switch (m_nLaneType)
			{
			case LANE_LEFT:
				Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed) - TriDelta.x / 2) + m_vNotexVec.x * m_dLifeTime;
				Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2) + m_vNotexVec.y * m_dLifeTime;
				Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * ((timer - t) / 2);
				Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * ((timer - t) / 2);
				break;

			case LANE_RIGHT:
				Tex_3D_Data[0].Obj_Pos.x = (((m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed) + TriDelta.x / 2) - m_vNotexVec.x * m_dLifeTime;
				Tex_3D_Data[0].Obj_Pos.y = (((m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2) + m_vNotexVec.y * m_dLifeTime;
				Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * ((timer - t) / 2);
				Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * ((timer - t) / 2);
				break;
			default:
				break;
			}
		}

		// 画像縮小
		// 判定レーンに入ってから終端になるまで縮小
		Tex_3D_Data[0].Obj_Scale.x = (((NotesNum * (m_dMajorTime / 16.0f))) - (m_Timer - m_dLifeTime)) / ((NotesNum * ((m_dMajorTime / 16.0f))));
		//Tex_3D_Data[0].Obj_Scale.x = ((((m_dBPM * m_dHiSpeed) * BPM_SPEED) * ((m_dMajorTime / 16.0f) * NotesNum)) * m_dHiSpeed) * (NotesNum * (m_dMajorTime / 16.0f)) * ;
		// 指定時間経過したら生存フラグを降ろす
		if (m_Timer > (m_dLifeTime + (((m_dMajorTime / 16.0f) * (NotesNum + 1)))) - (m_dMajorTime / 32))
		{
			m_bUse = false;
		}
	}

	// 判定タイミングに入ったかどうか
	if (m_Timer >= HitTimer + (m_dMajorTime / 16.0f))
	{
		if (DecitionFlag)
		{
			MissFlag = true;
		}
		DecitionFlag = true;
		HitTimer += (m_dMajorTime / 16.0f);
	}

	CTexture_3D_Base::Update();
}

void CLongNotes::Draw()
{
	CBaseNotes::Draw();
}

// ロングノーツ用の専用生成関数(レーンが左か右か、レーンが上か下か、一小節の時間、生成の遅れた時間)
void CLongNotes::Create(int laneType, int laneNum, double CourceTime)
{
	if (m_bUse)// 使っていたら生成しない
		return;
	//float size = ((((m_Data.m_vTexSize.x) / 16.0f) * NotesNum)) * (m_dHiSpeed);// 16分のサイズ * ロングの数でロングノーツの長さを計算
	float size = ((((m_dBPM * m_dHiSpeed) * BPM_SPEED) * ((m_dMajorTime / 16.0f) * NotesNum)) * m_dHiSpeed);
	Tex_3D_Data[0].Obj_Size.x = size;

	//HitFlag = false;
	HitTimer = m_dLifeTime - (m_dMajorTime / 32);
	m_Timer = CourceTime;
	m_nLaneType = laneType;							// レーンが左か右か格納
	m_nLaneNum = laneNum;
	TriDelta.x = fabs(size * cosf(m_Data.m_vRad[laneType].z));
	TriDelta.y = fabs(size * sinf(m_Data.m_vRad[laneType].z));
	Tex_3D_Data[0].Obj_Rot = m_Data.m_vRad[laneType];	// レーンの傾きに合わせてノーツも傾ける

	if (laneType == LANE_LEFT)
	{// 左レーンに生成
		Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3(((m_Data.Pos[laneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed) - TriDelta.x / 2, ((m_Data.Pos[laneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2, (m_Data.Pos[laneType].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (laneNum * m_Data.m_fLaneSize));
		Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
		Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
	}
	else if (laneType == LANE_RIGHT)
	{// 右レーンに生成
		Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3(((m_Data.Pos[laneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed) + TriDelta.x / 2, ((m_Data.Pos[laneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed) - TriDelta.y / 2, (m_Data.Pos[laneType].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (laneNum * m_Data.m_fLaneSize));
		Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
		Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
	}

	Tex_3D_Data[0].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bUse = true;	// 使用フラグを立てる
}

double CLongNotes::GetTiming()
{
	double timing = m_Timer - HitTimer;

	return timing;
}