//***********************************************************************************************************
// 
// FPS関連構築クラス
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CFPS.h"


//***********************************************************************************************************
// 静的変数定義
//***********************************************************************************************************
int	CFPS::nCountFPS = 0;


//***********************************************************************************************************
// FPS関連初期化
//***********************************************************************************************************
void CFPS::Init( LPDIRECT3DDEVICE9	pDevice )
{
	pD3DXFont		= NULL;

//#ifdef _DEBUG
	MousePos		= D3DXVECTOR3();
	WorldPos		= D3DXVECTOR3();
	fMouseWheel		= 0.0f;
//#endif

	// フレームカウント初期化
	timeBeginPeriod(1);		//分解能の設定

	dwExecLastTime	= //ミリ秒間隔で取得
	dwFPSLastTime	= timeGetTime();

	dwCurrentTime	= 
	dwFrameCount	= 0;

	//情報表示用フォントを設定
	D3DXCreateFont (	pDevice,
						18, 
						0, 
						0, 
						0, 
						FALSE,
						SHIFTJIS_CHARSET, 
						OUT_DEFAULT_PRECIS,
						DEFAULT_QUALITY, 
						DEFAULT_PITCH,
						"Terminal", 
						&pD3DXFont );
}

//***********************************************************************************************************
// FPS終了処理
//***********************************************************************************************************
void CFPS::Finalise()
{
	if ( pD3DXFont != NULL )
	{	//情報表示用フォントの開放
		pD3DXFont->Release();
		pD3DXFont = NULL;
	}
}

//***********************************************************************************************************
// FPS更新
//***********************************************************************************************************
bool CFPS::Update()
{
	dwCurrentTime = timeGetTime();

//#ifdef _DEBUG
	MousePos	= CInput::GetMousePos();	// マウス座標取得
	WorldPos	= CInput::GetToWorldPos();	// ワールド座標取得
	fMouseWheel = CInput::GetMouseWheel();	// マウスホイール移動量取得
//#endif

	if (( dwCurrentTime - dwFPSLastTime ) >= 500 )
	{	//0.5秒ごとに実行
		//FPSを測定
		nCountFPS		= ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );

		//FPSを測定した時刻を保存
		dwFPSLastTime	= dwCurrentTime;
		dwFrameCount	= 0; //カウントクリア
	}

	if ( ( float )( dwCurrentTime - dwExecLastTime ) >= ( 1000.0f/60.0f ) )
	{
		dwExecLastTime = dwCurrentTime;
		dwFrameCount ++;	//カウント加算

		return true;
	}
	else
	{
		return false;
	}
}

//***********************************************************************************************************
//
// FPS描画
//
//***********************************************************************************************************
void CFPS::Draw()
{
//#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];	//文字格納用


	wsprintf(	aStr, 
				"FPS:%2d\nMousePos.X:%5dY:%5dZ:%5d\nWorldPos.X:%5dY:%5dZ:%5d\n", 
				nCountFPS, 
				(int)MousePos.x, (int)MousePos.y, (int)fMouseWheel, 
				(int)WorldPos.x, (int)WorldPos.y, (int)WorldPos.z );


	//テキスト描画
	pD3DXFont->DrawText(	NULL, 
							aStr, 
							-1, 
							&rect,
							DT_LEFT, 
							D3DCOLOR_RGBA(255,255,255,255) );
//#endif
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************