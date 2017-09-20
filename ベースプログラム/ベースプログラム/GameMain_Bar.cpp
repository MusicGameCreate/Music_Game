//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "GameMain_Bar.h"
#include "CInput.h"

//*************************************************************************
// コンストラクタ
//*************************************************************************
GameMain_Bar::GameMain_Bar(void)
{
	// オブジェクトを何個作成するか？(最低 1～)
	//**********************************************************************
	nObject_Num	= 1;

	// テクスチャを何種類使用するか？(最低 1～)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	560.0f, 360.0f, 0.0f );

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 120.0f, 340.0f );

		// テクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1アニメーション毎のテクスチャ座標(0.0f～1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// 画像のRGBA値
		//******************************************************************
		Tex_2D_Data[i].Red  =
		Tex_2D_Data[i].Green=
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha= 255;

		// 画像の拡大率( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// 画像の回転角度( 0.0f～ )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 ～ 指定してください)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/bar.png", 0);
	
}

//*************************************************************************
// デストラクタ
//*************************************************************************
GameMain_Bar::~GameMain_Bar(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void GameMain_Bar::Update(void)
{
	int BarSize = Tex_2D_Data[0].Obj_Size.y / LANE_NUM;
	int SelectLaneUp = -1;
	int SelectLaneDown = LANE_NUM;
	SelectLane.clear();
	MouseY = CInput::GetMousePos().y;
	// 上レーン算出
	for (int i = 0; i < LANE_NUM; i++)
	{
		if (MouseY - (CursolSize / 2) < Tex_2D_Data[0].Obj_Pos.y - (Tex_2D_Data[0].Obj_Size.y / 2 - BarSize) + (BarSize * i))
		{
			SelectLane.push_back(i);
			//SelectLane.push_back(i + LANE_NUM);
			break;
		}
	}
	// 下レーン算出
	for (int i = LANE_NUM - 1; i >= 0; i--)
	{
		if (MouseY + (CursolSize / 2) > Tex_2D_Data[0].Obj_Pos.y - (Tex_2D_Data[0].Obj_Size.y / 2) + (BarSize * i + 2))
		{
			SelectLane.push_back(i);
			//SelectLane.push_back(i + LANE_NUM);
			break;
		}
	}
	//AddRotate();
	CTexture_2D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void GameMain_Bar::Draw(void)
{
	//CDirectX::Get_pD3DDevice()->BeginScene();
	CTexture_2D_Base::Draw(0,0);
	//CDirectX::Get_pD3DDevice()->EndScene();
}

void GameMain_Bar::Initialize(int laneSize, int cursolSize)
{
	LaneSize = laneSize;
	CursolSize = cursolSize;
}

void GameMain_Bar::AddRotate()
{
	Tex_2D_Data[0].fRot += 0.01f;
}

// 
deque<int> GameMain_Bar::GetSelectLane()
{
	return SelectLane;
}

//*************************************************************************
// EOF
//*************************************************************************
