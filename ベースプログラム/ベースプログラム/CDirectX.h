//***********************************************************************************************************
//
// DirectX情報一括管理クラス( 2D,3D環境構築 )
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Define.h"

#include "d3dx9.h"						// 描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"

#pragma comment (lib,"d3d9.lib")	//描画処理に必要
#pragma comment (lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment (lib,"dxguid.lib")	//DirectXコンポーネント使用に必要
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"winmm.lib")

//***********************************************************************************************************
// マクロ定義
//***********************************************************************************************************

// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//***********************************************************************************************************
// 構造体定義
//***********************************************************************************************************

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;		// 頂点座標
	float		rhw;		// テクスチャのパースペクティブコレクト用
	D3DCOLOR	col;		// 頂点カラー
	D3DXVECTOR2	tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;		// 頂点座標
	D3DXVECTOR3	normal;		// 法線
	D3DCOLOR	diffuse;	// 頂点カラー
	D3DXVECTOR2	tex;		// テクスチャ座標
} VERTEX_3D;

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class CDirectX
{
private:
	static LPDIRECT3D9			pD3D;		// Direct3Dオブジェクト
	static LPDIRECT3DDEVICE9	pD3DDevice;	// Deviceオブジェクト(描画に必要)

public:
	HRESULT Init( HWND hWnd , bool bWindow );
	void Finalise();

	bool Render_Begin();	// 描画開始
	void Render_End();		// 描画終了

	// 変数引き渡し関数↓
	static LPDIRECT3DDEVICE9	Get_pD3DDevice(){ return pD3DDevice; }
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************