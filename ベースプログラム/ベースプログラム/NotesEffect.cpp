#include "NotesEffect.h"
#include "TimeServer.h"

CNotesEffect::CNotesEffect()
{
	m_bUse = false;
	m_LifeTime = 0.15f;
	m_Timer = 0.0f;
	m_nLaneNum = 0;
	m_nEffectType = 0;
}

CNotesEffect::~CNotesEffect()
{

}

void CNotesEffect::Initialize(LaneData data)
{
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

	D3DXIMAGE_INFO	info;			// 画像情報
	D3DXGetImageInfoFromFile("../DATA/TEXTURE/GameMain/NotesEffect/judge1-2.png", &info);

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(data.m_fLaneSize, data.m_fLaneSize);

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// アニメーション枚数
		m_AnimNum.push_back(12);
		m_AnimCount.push_back(1);

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		t = 1.0f / 12.0f;
		Tex_3D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, t);

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
	m_Data = data;

	CTexture_3D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/NotesEffect/judge1-2.png", 0);
}

void CNotesEffect::Finalize()
{
	CTexture_3D_Base::Finalise();
}

void CNotesEffect::Update()
{
	if (!m_bUse)
		return;
	double timer = CTimeServer::GetDifference();
	m_Timer += timer;

	if (m_Timer > (m_LifeTime / (m_AnimNum[0] + 0)) * m_AnimCount[0])
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			Tex_3D_Data[i].Tex_Pos.y += Tex_3D_Data[i].Tex_Anim.y;

			if (Tex_3D_Data[i].Tex_Pos.y >= 1.0f)
				Tex_3D_Data[i].Tex_Pos.y = 0.0f;
		}
		m_AnimCount[0] ++;
	}

	if (m_Timer > m_LifeTime)
	{
		m_AnimCount[0] = 1;
		Tex_3D_Data[0].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);
		m_bUse = false;
	}

	CTexture_3D_Base::Update();
}

void CNotesEffect::Draw()
{
	if (!m_bUse)
		return;
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_3D_Base::Draw(i, 0);
	}
}

void CNotesEffect::Create(int LaneNum)
{
	m_Timer = 0.0f;
	m_nLaneNum = LaneNum;

	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(m_Data.Pos[0].x + (m_Data.m_vTriSize.x / 2), m_Data.Pos[0].y + (m_Data.m_vTriSize.y / 2), (m_Data.Pos[0].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (LaneNum * m_Data.m_fLaneSize));
	}

	
	m_bUse = true;	// 使用フラグを立てる
}