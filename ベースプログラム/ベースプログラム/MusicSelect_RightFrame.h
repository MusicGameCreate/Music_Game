//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************
#pragma once 

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CTexture_2D_Base.h" 

//*************************************************************************
// 列挙体定義
//*************************************************************************

// 曲セレクト画面にて使用
//*************************************************
typedef enum
{
	LEFT_DOWN,			// 左下移動
	RIGHT_DOWN,			// 右下移動
	LEFT_UP,			// 左上移動
	RIGHT_UP,			// 右上移動
}MOVE_POSITION;

//*************************************************************************
// 構造体定義
//*************************************************************************



// 枠の移動方向、描画順まとめ
//*************************************************
typedef struct
{
	int nMove_Vec_Up;	// 上の移動方向
	int nMove_Vec_Down;	// 下の移動方向
	int nDraw_Order;	// 描画順
}OBJECT_MOVE_VEC;

//*************************************************************************
// クラス定義
//*************************************************************************
class MusicSelect_RightFrame : public CTexture_2D_Base
{
private:
	OBJECT_MOVE_VEC		Move_Vec[7];			// 移動する時の移動方向


	const D3DXVECTOR3 MOVE_POSITION					= D3DXVECTOR3(  190.0f, 115.0f, 0.0f);	// オブジェクトが移動する際の移動距離
	const D3DXVECTOR3 RIMIT_POSITION_UP				= D3DXVECTOR3( 1530.0f, -90.0f, 0.0f);	// オブジェクト座標の上限
	const D3DXVECTOR3 POSITION_CENTER_UP_SPEAR		= D3DXVECTOR3( 1340.0f,  20.0f, 0.0f);	// オブジェクト上スペア座標
	const D3DXVECTOR3 POSITION_CENTER_UP_UP			= D3DXVECTOR3( 1150.0f, 135.0f, 0.0f);	// オブジェクトセンター2つ上座標
	const D3DXVECTOR3 POSITION_CENTER_UP			= D3DXVECTOR3(  960.0f, 250.0f, 0.0f);	// オブジェクトセンター1つ上座標
	const D3DXVECTOR3 POSITION_CENTER				= D3DXVECTOR3(  770.0f, 365.0f, 0.0f);	// オブジェクトセンター座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN			= D3DXVECTOR3(  960.0f, 480.0f, 0.0f);	// オブジェクトセンター1つ下座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN		= D3DXVECTOR3( 1150.0f, 595.0f, 0.0f);	// オブジェクトセンター2つ下座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1340.0f, 710.0f, 0.0f);	// オブジェクト下スペア座標
	const D3DXVECTOR3 RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1530.0f, 825.0f, 0.0f);	// オブジェクト座標の下限	

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum);

public:
	void Update( int DIFFICULT, bool UP, bool DOWN );
	int  Draw(int NUMBER);

	MusicSelect_RightFrame(void);
	virtual ~MusicSelect_RightFrame(void);
};

//*************************************************************************
// EOF
//*************************************************************************
