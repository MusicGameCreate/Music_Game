//***********************************************************************************************************
//
// 各カメラ処理
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Camera.h"

#include "CInput.h"
#include "Debug_DataSave.h"

//***********************************************************************************************************
// 静的変数定義
//***********************************************************************************************************
D3DXMATRIX  CCamera::mtxView;		
D3DXMATRIX  CCamera::mtxProjection;

D3DXVECTOR3	CCamera::posCameraP;	
D3DXVECTOR3	CCamera::posCameraT;	
D3DXVECTOR3	CCamera::vecCameraU;

D3DXVECTOR3	CCamera::rotCamera;

//***********************************************************************************************************
// void CCamera::Init
// 説明：カメラの初期化処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CCamera::Init(void)
{
	posCameraP		= D3DXVECTOR3(0.0f, 700.0f, -1.0f);	// カメラ位置設定
	posCameraT		= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );		// カメラ注視点設定
	vecCameraU		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );		// カメラ上設定

	rotCamera		= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );		// カメラ回転設定
}

//***********************************************************************************************************
// void CCamera::Finalise
// 説明：カメラの終了処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CCamera::Finalise(void)
{

}

//***********************************************************************************************************
// void CCamera::Update
// 説明：カメラの更新処理
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CCamera::Update(void)
{

}

//***********************************************************************************************************
// void CCamera::Set
// 説明：描画前にカメラをセットする
// 引数：なし　戻り値：なし
//***********************************************************************************************************
void CCamera::Set(void)
{ 
	//ビューマトリクスの初期化
	D3DXMatrixIdentity( &mtxView );
	//ビューマトリクスの作成
	D3DXMatrixLookAtLH( &mtxView,
						&posCameraP,
						&posCameraT,
						&vecCameraU );

	//ビューマトリクスの設定
	CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_VIEW, &mtxView );

	//プロジェクションマトリクス
	D3DXMatrixIdentity( &mtxProjection );

	//プロジェクションマトリクスの作成
	D3DXMatrixPerspectiveFovLH(	&mtxProjection,						// 格納先
								D3DXToRadian( 60.0f ),				// デグリーからラジアンへ変換
								(float)SCREEN_WIDTH/SCREEN_HEIGHT,	
								1.0f,								// ニアクリップ
								15000.0f  );							// ファークリップ

	//プロジェクションマトリクスの設定
	CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_PROJECTION, &mtxProjection );
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************