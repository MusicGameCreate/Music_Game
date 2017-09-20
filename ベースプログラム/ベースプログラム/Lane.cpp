#include "Lane.h"

D3DXVECTOR3 BaseLanePos(1238.0f, -856.0f, -58.0f);
//D3DXVECTOR3 BaseLanePos(0.0f, 0.0f, -55.0f);
//float fPos = 1536.0f;
//float fRot = 44.67f;
//float fRot = 7.10f;
float fRot = 0.60f;



CLane::CLane()
{
	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num = 2;

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

	D3DXGetImageInfoFromFile("../DATA/TEXTURE/GameMain/Lane/ノーツレーン.png", &info);

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(3000.0f, 440.0f);

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
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/Lane/ノーツレーン.png", 0);

	Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3(-BaseLanePos.x, BaseLanePos.y, BaseLanePos.z);
	Tex_3D_Data[0].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, fRot);
	Data.m_vRad[0] = D3DXVECTOR3(0.0f, 0.0f, fRot);

	Tex_3D_Data[1].Obj_Pos = D3DXVECTOR3(BaseLanePos.x, BaseLanePos.y, BaseLanePos.z);
	Tex_3D_Data[1].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, -fRot);
	Data.m_vRad[1] = D3DXVECTOR3(0.0f, 0.0f, -fRot);

	// オブジェクトの角度からオブジェクトの端から端までの距離を計算
	Data.m_vRot[0].z = fRot * 180.0f / D3DX_PI;
	while (Data.m_vRot[0].z >= 360.0f)
		Data.m_vRot[0].z -= 360.0f;
	Data.m_vRot[1].z = Data.m_vRot[0].z - 90.0f;
	//Data.m_vRot[0].z = -Data.m_vRot[1].z - 90.0f;
	Data.m_vTriSize.x = fabs((Tex_3D_Data[0].Obj_Size.x) * cosf(Data.m_vRad[0].z));
	Data.m_vTriSize.y = fabs((Tex_3D_Data[0].Obj_Size.x) * sinf(Data.m_vRad[0].z));

	Tex_3D_Data[0].Obj_Pos.x = -Data.m_vTriSize.x / 2;
	Tex_3D_Data[1].Obj_Pos.x = Data.m_vTriSize.x / 2;

	Data.m_nLaneNum = LANE_NUM;
	Data.m_fLaneSize = Tex_3D_Data[0].Obj_Size.y / Data.m_nLaneNum;

	Data.Pos[LANE_LEFT] = Tex_3D_Data[LANE_LEFT].Obj_Pos;
	Data.Pos[LANE_RIGHT] = Tex_3D_Data[LANE_RIGHT].Obj_Pos;

	Data.m_vTexSize = Tex_3D_Data[0].Obj_Size;

	//Tex_3D_Data[0].Obj_Pos.x -= (1500.0f + Data.m_fLaneSize / 2);
	//Tex_3D_Data[1].Obj_Pos.x += (1500.0f + Data.m_fLaneSize / 2);

	SelectLaneEffect.Initialize(Data);
}

//*************************************************************************
// デストラクタ
//*************************************************************************
CLane::~CLane(void)
{
	//delete[] bLife;
	//delete[] nDir;
	//delete[] Move_Speed;
	//delete[] nSet_Texture;
	CLane::Finalize();
}

void CLane::Initialize()
{

}

void CLane::Finalize()
{
	SelectLaneEffect.Finalise();
	CTexture_3D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void CLane::Update(void)
{
	SelectLaneEffect.Update();

	//if (CInput::GetKeyboardData(DIK_A, TRIGGER))
	//{
	//	fRot += 0.01f;
	//	Tex_3D_Data[0].Obj_Rot.z = fRot;
	//	Tex_3D_Data[1].Obj_Rot.z = -fRot;
	//}
	//if (CInput::GetKeyboardData(DIK_S, TRIGGER))
	//{
	//	fRot -= 0.01f;
	//	Tex_3D_Data[0].Obj_Rot.z = fRot;
	//	Tex_3D_Data[1].Obj_Rot.z = -fRot;
	//}

	//if (CInput::GetKeyboardData(DIK_D, PRESS))
	//{
	//	BaseLanePos.x += 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.x = -BaseLanePos.x;
	//	Tex_3D_Data[1].Obj_Pos.x = BaseLanePos.x;
	//}
	//if (CInput::GetKeyboardData(DIK_F, PRESS))
	//{
	//	BaseLanePos.x -= 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.x = -BaseLanePos.x;
	//	Tex_3D_Data[1].Obj_Pos.x = BaseLanePos.x;
	//}
	//if (CInput::GetKeyboardData(DIK_Q, PRESS))
	//{
	//	BaseLanePos.y -= 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.y = BaseLanePos.y;
	//	Tex_3D_Data[1].Obj_Pos.y = BaseLanePos.y;
	//}
	//if (CInput::GetKeyboardData(DIK_W, PRESS))
	//{
	//	BaseLanePos.y += 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.y = BaseLanePos.y;
	//	Tex_3D_Data[1].Obj_Pos.y = BaseLanePos.y;
	//}

	//if (CInput::GetKeyboardData(DIK_LSHIFT, TRIGGER))
	//{
	//	Debug_Save_ObjectPos("レーン座標", Tex_3D_Data[0].Obj_Pos);
	//	Debug_Save_ObjectPos("レーン角度", Tex_3D_Data[0].Obj_Rot);
	//}

	CTexture_3D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void CLane::Draw(void)
{
	SelectLaneEffect.Draw();
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_3D_Base::Draw(i, 0);
	}
}

void CLane::NotesEffect(int LaneNum, int LaneType)
{
	SelectLaneEffect.NotesEffect(LaneNum, LaneType);
}

void CLane::TimerReset(int LaneNum, int LaneType)
{
	SelectLaneEffect.TimerReset(LaneNum, LaneType);
}

//*************************************************************************
// EOF
//*************************************************************************
