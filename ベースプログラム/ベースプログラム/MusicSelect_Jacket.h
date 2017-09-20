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
#include "MusicSelect_RightFrame.h"

//*************************************************************************
// 構造体定義
//*************************************************************************
typedef struct
{
	char*	Music_Jacket_Pass;	// 曲全ジャケットパス
	int		nTexture_Num;		// テクスチャ読み込み時に設定したテクスチャ番号

}JACKET_DATA;

//*************************************************************************
// クラス定義
//*************************************************************************
class MusicSelect_Jacket : public CTexture_2D_Base
{
private:
	int					nAll_Music_Num;		// 曲総数
	JACKET_DATA*		Jacket_Data;

	int					nCount;				// FPSカウンタ
	int					nTexture;			// 

	bool				bMove_Up;			// 上方向に移動するかどうか
	bool				bMove_Down;			// 下方向に移動するかどうか

	OBJECT_MOVE_VEC		Move_Vec[7];		// 移動する時の移動方向
	int					nNow_SetTexture[7];	// 現在のオブジェクトにセットされてあるテクスチャの番号

	const D3DXVECTOR3 MOVE_POSITION					= D3DXVECTOR3(  195.0f,  110.0f, 0.0f );	// オブジェクトが移動する際の移動距離
	const D3DXVECTOR3 RIMIT_POSITION_UP				= D3DXVECTOR3( 1375.0f,  -75.0f, 0.0f );	// オブジェクト座標の上限
	const D3DXVECTOR3 POSITION_CENTER_UP_SPEAR		= D3DXVECTOR3( 1180.0f,   35.0f, 0.0f );	// オブジェクト上スペア座標
	const D3DXVECTOR3 POSITION_CENTER_UP_UP			= D3DXVECTOR3(  985.0f,  145.0f, 0.0f );	// オブジェクトセンター2つ上座標
	const D3DXVECTOR3 POSITION_CENTER_UP			= D3DXVECTOR3(  790.0f,  255.0f, 0.0f );	// オブジェクトセンター1つ上座標
	const D3DXVECTOR3 POSITION_CENTER				= D3DXVECTOR3(  595.0f,  365.0f, 0.0f );	// オブジェクトセンター座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN			= D3DXVECTOR3(  790.0f,  475.0f, 0.0f );	// オブジェクトセンター1つ下座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN_DOWN		= D3DXVECTOR3(  985.0f,  585.0f, 0.0f );	// オブジェクトセンター2つ下座標
	const D3DXVECTOR3 POSITION_CENTER_DOWN_SPEAR	= D3DXVECTOR3( 1180.0f,  695.0f, 0.0f );	// オブジェクト下スペア座標
	const D3DXVECTOR3 RIMIT_POSITION_DOWN			= D3DXVECTOR3( 1375.0f,  805.0f, 0.0f );	// オブジェクト座標の下限

	void Set_Move_Vec(D3DXVECTOR3 POSITION, int nNum);

public:
	void Update(bool UP, bool DOWN);
	void Draw(int NUMBER);

	MusicSelect_Jacket(void);
	virtual ~MusicSelect_Jacket(void);
};

//*************************************************************************
// EOF
//*************************************************************************
