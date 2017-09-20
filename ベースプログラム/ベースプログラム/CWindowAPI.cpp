//***********************************************************************************************************
//
// WindowAPIの環境設定
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Define.h"
#include "CWindowAPI.h"

//***********************************************************************************************************
// 静的変数定義
//***********************************************************************************************************
WNDCLASSEX	CWindowAPI::wcex;
HWND		CWindowAPI::hWnd;
MSG			CWindowAPI::msg;

//***********************************************************************************************************
// ウインドウ情報初期化
//***********************************************************************************************************
void CWindowAPI::Init( HINSTANCE hInstance )
{
DWORD dwStyle = WS_OVERLAPPED;
	DWORD dwExStyle = 0;
	// ウィンドウのサイズ指定
	RECT clientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// 指定されたクライアント領域を確保するために必要なウィンドウ座標計算
	::AdjustWindowRect(&clientRect, 	// クライアント領域の座標が入った構造体へのポインタ
		dwStyle,			// ウィンドウスタイル
		dwExStyle);						// メニューを持つかどうかの指定

	WNDCLASSEX work =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	wcex = work;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//ウインドウの作成
	hWnd = CreateWindowEx(	0,
							CLASS_NAME,
							WINDOW_NAME,
							// フルスクリーンモードにするなら→	WS_VISIBLE | WS_POPUP
							// ウインドウモードにするなら→		WS_OVERLAPPEDWINDOW
							WS_OVERLAPPEDWINDOW,
							0,				// ウインドウの横方向の位置
							0,				// ウインドウの縦方向の位置
							( SCREEN_WIDTH	+ GetSystemMetrics(SM_CXDLGFRAME) * 2 ),
							( SCREEN_HEIGHT	+ GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION) ),
							NULL,
							NULL,
							hInstance,
							NULL);

	AdjustWindowRectEx(&clientRect, WS_OVERLAPPEDWINDOW, FALSE, 0);
	SetWindowPos(hWnd, NULL, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, SWP_NOMOVE | SWP_NOZORDER);
}

//***********************************************************************************************************
// ウインドウ更新処理
//***********************************************************************************************************
void CWindowAPI::Update()
{

}

//***********************************************************************************************************
// ウインドウ表示処理
//***********************************************************************************************************
void CWindowAPI::Display( int nCmdShow )
{
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
}

//***********************************************************************************************************
// ウインドウ破棄処理
//***********************************************************************************************************
void CWindowAPI::Finalise( HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, wcex.hInstance);
}

//***********************************************************************************************************
// ウインドウプロシージャ
//***********************************************************************************************************
LRESULT CALLBACK CWindowAPI::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// キーが押されたとき
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);

			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);

		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//***********************************************************************************************************
// ウインドウメッセージ
//***********************************************************************************************************
int CWindowAPI::WindowMessage()
{
	if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0 )	//メッセージを取得しなかった場合"0"を返す
	{
		//Windowsの処理
		if(msg.message == WM_QUIT)
		{
			//プログラム終了
			return 1;
		}
		else
		{
			//メッセージの翻訳と送出
			TranslateMessage( &msg );
			DispatchMessage ( &msg );

			return 0;
		}
	}
	else
	{
		return 0;
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************