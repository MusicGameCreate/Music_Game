//*************************************************************************
//
// ゲームメイン画面・背景色
//
//*************************************************************************

//*************************************************************************
// インクルード部
//*************************************************************************
#include "NotesDecision.h" 
#include "DirectX_Library.h"
#include "TimeServer.h"

const D3DXVECTOR3 InitPos(0.0f, 0.0f, 270.0f);
const float LifeTime = 0.3f;

//*************************************************************************
// コンストラクタ
//*************************************************************************
CNotesDecision::CNotesDecision(void)
{
	// オブジェクトを何個作成するか？(最低 1〜)
	//**********************************************************************
	nObject_Num = 1;

	// テクスチャを何種類使用するか？(最低 1〜)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// 各種設定を指定
	//**********************************************************************
	bBillboard = true;// ビルボードにするかどうか
	bAlphaTest = false;// αテストを適用するかどうか

	// オブジェクトの個数分、必要なサイズを確保
	//**********************************************************************
	Tex_3D_Data = new TEXTURE_3D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// 座標(画像の中心を原点)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = InitPos;

		// オブジェクトのサイズ(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(150.0f, 20.0f);

		// テクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1アニメーション毎のテクスチャ座標(0.0f〜1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 0.5f);

		// 画像のRGBA値
		//******************************************************************
		Tex_3D_Data[i].Red =
			Tex_3D_Data[i].Green =
			Tex_3D_Data[i].Brue = 255;
			Tex_3D_Data[i].Alpha = 255;

		// 画像の拡大率( 0.0f〜 )
		//******************************************************************
		Tex_3D_Data[i].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// 画像の回転角度( 0.0f〜 )
		//******************************************************************
		Tex_3D_Data[i].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	CTexture_3D_Base::Init();

	// テクスチャ読み込み(複数の場合は複数回読みこんでください)
	// 引数：	TEXTURE_FILE = 読み込みたい画像ファイルのパス
	//			NUMBER		 = 読み込むテクスチャパスの配列番地(これの数字下のDraw()で渡す引数の数字になります)
	//						   ( 0 〜 指定してください)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/NotesEffect/judge.png", 0);

	bLife = false;
	NowTime = 0.0f;
}

//*************************************************************************
// デストラクタ
//*************************************************************************
CNotesDecision::~CNotesDecision(void)
{
	CTexture_3D_Base::Finalise();
}

//*************************************************************************
// 更新処理
//*************************************************************************
void CNotesDecision::Update(void)
{
	if (!bLife)return;

	NowTime += CTimeServer::GetDifference();
	if (NowTime >= LifeTime)
		bLife = false;

	CTexture_3D_Base::Update();
}

//*************************************************************************
// 描画処理
//*************************************************************************
void CNotesDecision::Draw()
{
	if (!bLife)return;

	
	CTexture_3D_Base::Draw(0,0);
}

void CNotesDecision::Active(int type)
{
	NowTime = 0.0f;
	bLife = true;
	DecisionType = type;
	switch (DecisionType)
	{
	case DECISION_FAST:
		Tex_3D_Data[0].Tex_Pos.y = 0.0f;
		break;
	case DECISION_SLOW:
		Tex_3D_Data[0].Tex_Pos.y = 0.5f;
		break;
	}
}

//*************************************************************************
// EOF
//*************************************************************************
