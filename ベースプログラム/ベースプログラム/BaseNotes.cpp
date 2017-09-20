#include "BaseNotes.h"
#include "TimeServer.h"

CBaseNotes::CBaseNotes()
{
	m_Timer = 0.0f;
	m_dBPM = 0.0f;
	m_dHiSpeed = 1.0f;
	m_dMajorTime = 0.0f;
	m_dLifeTime = 0.0f;
	m_bUse = false;
	m_vNotexVec.x = 0.0f;
	m_vNotexVec.y = 0.0f;
}

CBaseNotes::~CBaseNotes()
{
	CBaseNotes::Finalise();
}

void CBaseNotes::Initialize(char* filePass, LaneData data)
{
	m_Data = data;

	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num = 1;

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_3D_Data = new TEXTURE_3D_DATA[nObject_Num];

	//bLife = new bool[nObject_Num];
	//Move_Speed = new D3DXVECTOR3[nObject_Num];
	//nSet_Texture = new int[nObject_Num];
	//nDir = new int[nObject_Num];

	// 各種設定を指定
	//**********************************************************************
	bBillboard = false;	// ビルボードにするかどうか
	bAlphaTest = true;	// αテストを適用するかどうか

	D3DXGetImageInfoFromFile(filePass, &info);

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(55.0f, 55.0f);

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// 画像のRGBA値
		//******************************************************************
		Tex_3D_Data[i].Red = 255;
		Tex_3D_Data[i].Green = 255;
		Tex_3D_Data[i].Brue = 255;
		Tex_3D_Data[i].Alpha = 255;

		// 画像の拡大率( 0.0f～ )
		//******************************************************************
		Tex_3D_Data[i].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// 画像の回転角度( 0.0f～ )
		//******************************************************************
		Tex_3D_Data[i].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//bLife[i] = false;
		//nSet_Texture[i] = 0;
		//nDir[i] = NULL;
	}

	CTexture_3D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture(filePass, 0);
}

void CBaseNotes::Finalize()
{
	CTexture_3D_Base::Finalise();
}

void CBaseNotes::Update()
{
	if (!m_bUse)
		return;
	double timer = CTimeServer::GetDifference();
	m_Timer += timer;

	if (m_Timer < m_dLifeTime)
	{// 判定時間以前
		switch (m_nLaneType)
		{
		case LANE_LEFT:
			//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed + (m_Data.m_vTriSize.x * (m_Timer / m_dMajorTime)) * m_dHiSpeed;
			//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed + (m_Data.m_vTriSize.y * (m_Timer / m_dMajorTime)) * m_dHiSpeed;
			Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * timer;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * timer;
			break;
		case LANE_RIGHT:
			Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * timer;
			Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * timer;
			//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed - (m_Data.m_vTriSize.x * (m_Timer / m_dMajorTime)) * m_dHiSpeed;
			//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[m_nLaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed + (m_Data.m_vTriSize.y * (m_Timer / m_dMajorTime)) * m_dHiSpeed;
			break;
		default:
			break;
		}
	}
	else
	{// 判定時間後
		switch (m_nLaneType)
		{
		case LANE_LEFT:
			Tex_3D_Data[0].Obj_Pos.x = m_Data.Pos[0].x + m_Data.m_vTriSize.x / 2;
			Tex_3D_Data[0].Obj_Pos.y = m_Data.Pos[0].y + m_Data.m_vTriSize.y / 2;
			//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[m_nLaneType].x + m_Data.m_vTriSize.x / 2);
			//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[m_nLaneType].y + m_Data.m_vTriSize.y / 2);
			break;
		case LANE_RIGHT:
			Tex_3D_Data[0].Obj_Pos.x = m_Data.Pos[1].x - m_Data.m_vTriSize.x / 2;
			Tex_3D_Data[0].Obj_Pos.y = m_Data.Pos[1].y + m_Data.m_vTriSize.y / 2;
			//Tex_3D_Data[0].Obj_Pos.x = (m_Data.Pos[m_nLaneType].x - m_Data.m_vTriSize.x / 2);
			//Tex_3D_Data[0].Obj_Pos.y = (m_Data.Pos[m_nLaneType].y + m_Data.m_vTriSize.y / 2);
			break;
		default:
			break;
		}

		// 画像縮小
		Tex_3D_Data[0].Obj_Scale = D3DXVECTOR3((HIT_TIMING - (m_Timer - m_dLifeTime)) * (1.0f / HIT_TIMING), 1.0f, (HIT_TIMING - (m_Timer - m_dLifeTime)) * (1.0f / HIT_TIMING));

		//if(time >= m_dMajorTime)
		//	m_bUse = false;
		if (m_Timer > m_dLifeTime + HIT_TIMING)
		{
			m_bUse = false;
		}
	}

	CTexture_3D_Base::Update();
}

void CBaseNotes::Draw()
{
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_3D_Base::Draw(i, 0);
	}
}

// ノーツ生成関数（レーンが左か右か、レーンの上からの番号、1小節の時間、生成予定から超過した時間）
void CBaseNotes::Create(int LaneType, int LaneNum, double CourceTime)
{
	if (m_bUse)
		return;
	m_Timer = CourceTime;
	//m_Timer.TimerInit(m_dMajorTime);
	//m_Timer.TimerActiv(false);
	m_nLaneType = LaneType;							// レーンが左か右か格納
	m_nLaneNum = LaneNum;
	Tex_3D_Data[0].Obj_Rot = m_Data.m_vRad[LaneType];	// レーンの傾きに合わせてノーツも傾ける

	if (LaneType == LANE_LEFT)
	{// 左レーンに生成
		Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[LaneType].x - m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[LaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[LaneType].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (LaneNum * m_Data.m_fLaneSize));
		Tex_3D_Data[0].Obj_Pos.x += m_vNotexVec.x * CourceTime;
		Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
	}
	else if (LaneType == LANE_RIGHT)
	{// 右レーンに生成
		Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3((m_Data.Pos[LaneType].x + m_Data.m_vTriSize.x / 2) * m_dHiSpeed, (m_Data.Pos[LaneType].y - m_Data.m_vTriSize.y / 2) * m_dHiSpeed, (m_Data.Pos[LaneType].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (LaneNum * m_Data.m_fLaneSize));
		Tex_3D_Data[0].Obj_Pos.x -= m_vNotexVec.x * CourceTime;
		Tex_3D_Data[0].Obj_Pos.y += m_vNotexVec.y * CourceTime;
	}

	Tex_3D_Data[0].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bUse = true;	// 使用フラグを立てる
}

// ハイスピ格納
void CBaseNotes::SetSpeed(double bpm, double hispeed, double majorTime)
{
	m_dBPM = bpm;
	m_dHiSpeed = hispeed;
	m_dMajorTime = majorTime;
	m_dLifeTime = m_Data.m_vTexSize.x / ((bpm * hispeed) * BPM_SPEED);
	m_vNotexVec.x = (m_Data.m_vTriSize.x * m_dHiSpeed) / (m_dLifeTime);
	m_vNotexVec.y = (m_Data.m_vTriSize.y * m_dHiSpeed) / (m_dLifeTime);
}

// 
double CBaseNotes::GetTiming()
{
	double timing = m_Timer - m_dLifeTime;

	return timing;
}