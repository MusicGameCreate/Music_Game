//**********************************************************************************************************
//
// 入力デバイス管理クラス(キーボード、マウス)
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CInput.h"

//***********************************************************************************************************
// 静的変数定義
//***********************************************************************************************************

// 共通
//***********************************************************************************************************
LPDIRECTINPUT8			CInput::pDInput			= NULL;				// DirectInputインターフェースへのポインタ	

// キーボード用
//***********************************************************************************************************
LPDIRECTINPUTDEVICE8	CInput::pDIDevKeyboard	= NULL;				// 入力デバイス(キーボード)へのポインタ

BYTE					CInput::aKeyStatePress[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク(押している間)
BYTE					CInput::aKeyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク(1回判定)
BYTE					CInput::aKeyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク(1回あと少しラグありPRESS)
BYTE					CInput::aKeyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク(キーから離した瞬間)
int						CInput::aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

// マウス用
//***********************************************************************************************************
LPDIRECTINPUTDEVICE8	CInput::pDIDevMouse		= NULL;			// 入力デバイス(マウス)へのポインタ

DIMOUSESTATE2			CInput::mouseState;						// マウスの状態を受け取るワーク
DIMOUSESTATE2			CInput::mouseStateTrigger;				// マウスの状態を受け取るワーク(トリガー情報)
DIMOUSESTATE2			CInput::mouseStatePress;				// マウスの状態を受け取るワーク(プレス情報)
DIMOUSESTATE2			CInput::mouseStateRelease;				// マウスの状態を受け取るワーク(リリース情報)

POINT					CInput::po;								// マウス情報構造体ポインタ
D3DXVECTOR3				CInput::MousePos;						// マウス座標を格納(X,Y)
D3DXVECTOR3				CInput::WorldPos;						// ワールド座標格納用(X,Y,Z)
D3DXVECTOR3*			CInput::pWorldPos;						// ワールド座標ポインタ

//--- ワールド座標変換用 ---
D3DXMATRIX				CInput::InvView;						
D3DXMATRIX				CInput::InvPrj;
D3DXMATRIX				CInput::VP;
D3DXMATRIX				CInput::InvViewport;

D3DXVECTOR3				CInput::nearpos;
D3DXVECTOR3				CInput::farpos;
D3DXVECTOR3				CInput::ray;

float					CInput::Lray;
float					CInput::LP0;

//***********************************************************************************************************
// 初期化
//***********************************************************************************************************
HRESULT	CInput::Init(HINSTANCE hInstance, HWND hWnd )
{
	HRESULT	hr;

	// スクリーン座標を取得
	//*******************************************************************************************************
	GetCursorPos(&po);

	MousePos.x = 0.0f;
	MousePos.y = 0.0f;
	MousePos.z = 0.0f;

	// NULLを代入
	//*******************************************************************************************************
	pWorldPos = NULL;
	
	// ワールド変換用変数初期化
	//*******************************************************************************************************
	WorldPos	= D3DXVECTOR3();

	nearpos		= D3DXVECTOR3();
	farpos		= D3DXVECTOR3();
	ray			= D3DXVECTOR3();

	Lray		= 0.0f;
	LP0			= 0.0f;

	pWorldPos	= &WorldPos;

	// ウィンドウのクライアント領域を取得する
	RECT rc;
	GetClientRect(CWindowAPI::GethWnd(), &rc);

	// クライアント領域を画面座標に変換する
	POINT pt = { rc.left, rc.top };
	POINT pt2 = { rc.right, rc.bottom };
	ClientToScreen(CWindowAPI::GethWnd(), &pt);
	ClientToScreen(CWindowAPI::GethWnd(), &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

	// カーソルの動作範囲を制限する
	//ClipCursor(&rc);

	// 座標を代入
	//*******************************************************************************************************
	MousePos.x = (float)po.x;
	MousePos.y = (float)po.y;

	if( pDInput == NULL )
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(	hInstance, 
									DIRECTINPUT_VERSION,
									IID_IDirectInput8, 
									(void**)&pDInput, 
									NULL	);
	}

	if( FAILED(hr) )
	{
		MessageBox( hWnd, "DirectInputオブジェクトが作成できませんでした。", "警告！", MB_ICONWARNING );
		return hr;
	}

	// デバイスオブジェクトを作成
	//*******************************************************************************************************
	if( FAILED( hr = pDInput->CreateDevice(GUID_SysKeyboard, &pDIDevKeyboard, NULL) ) )
	{
		MessageBox( hWnd, "キーボードが検出されませんでした。", "警告！", MB_ICONWARNING );
		return hr;
	}

	// データフォーマットを設定
	//*******************************************************************************************************
	if( FAILED( hr = pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard)) )
	{
		MessageBox( hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING );
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	//*******************************************************************************************************
	if( FAILED( hr = pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) ) )
	{
		MessageBox( hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING );
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	//*******************************************************************************************************
	pDIDevKeyboard->Acquire();

	// デバイスオブジェクトを作成
	//*******************************************************************************************************
	if( FAILED( hr = pDInput->CreateDevice( GUID_SysMouse, &pDIDevMouse, NULL ) ) || pDIDevMouse == NULL )
	{
		MessageBox(hWnd, "マウスが検出されませんでした", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	//*******************************************************************************************************
	if(FAILED( hr = pDIDevMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	//*******************************************************************************************************
	if(FAILED( hr = pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// デバイスの設定
	//*******************************************************************************************************
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize			= sizeof(dipdw);
		dipdw.diph.dwHeaderSize		= sizeof(dipdw.diph);
		dipdw.diph.dwObj			= 0;
		dipdw.diph.dwHow			= DIPH_DEVICE;
		dipdw.dwData				= DIPROPAXISMODE_REL;

		if ( FAILED( hr = pDIDevMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph ) ) )
		{
			MessageBox( hWnd, "マウスデバイスを設定できませんでした。", "警告！", MB_ICONWARNING );
			return hr;
		}
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	//**********************************************
	pDIDevMouse->Acquire();

	return S_OK;
}

//***********************************************************************************************************
// 入力デバイスの終了処理
//***********************************************************************************************************
void CInput::Finalise(void)
{
	if( pDInput != NULL)
	{	// DirectInputオブジェクトの開放
		pDInput->Release();
		pDInput = NULL;
	}

	if( pDIDevKeyboard != NULL )
	{	// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		pDIDevKeyboard->Unacquire();
		pDIDevKeyboard->Release();
		pDIDevKeyboard = NULL;
	}

	if ( pDIDevMouse	!= NULL )
	{	// 入力デバイス(マウス)の開放
		// マウスへのアクセス権を開放(入力制御終了)
		pDIDevMouse->Unacquire();
		pDIDevMouse->Release();
		pDIDevMouse = NULL;
	}
}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void CInput::Update(void)
{
	// キーボード情報更新
	//*******************************************************************************************************
	Keyboard_Update();



	// マウス情報更新
	//*******************************************************************************************************
	Mouse_Update();
}

//***********************************************************************************************************
// キーボード情報更新
//***********************************************************************************************************
void CInput::Keyboard_Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	//*******************************************************************************************************
	if( SUCCEEDED( pDIDevKeyboard->GetDeviceState( sizeof( aKeyState ), aKeyState ) ) )
	{
		for( int nCnKey = 0 ; nCnKey < NUM_KEY_MAX ; nCnKey ++ )
		{
			// キートリガー・リリース情報を生成
			// aKeyStateは、現在のフレームの情報
			// aKeyStateは、1フレーム前の情報
			aKeyStateTrigger[nCnKey] = aKeyState[nCnKey] & (~aKeyStatePress[nCnKey] );	//トリガー情報
			aKeyStateRelease[nCnKey] = aKeyStatePress[nCnKey] & (~aKeyState[nCnKey] );	//リリース情報

			// キーリピート情報を生成
			if( aKeyState[nCnKey] )
			{
				if( aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT )
				{
					aKeyStateRepeatCnt[nCnKey]++;
					if( aKeyStateRepeatCnt[nCnKey] == 1 ||  aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT )
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				aKeyStateRepeatCnt[nCnKey] = 0;
				aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存
			aKeyStatePress[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		pDIDevKeyboard->Acquire();
	}
}

//***********************************************************************************************************
// マウス情報更新
//***********************************************************************************************************
void CInput::Mouse_Update(void)
{
	HRESULT	hr;
	DIMOUSESTATE2 mouseStateOld;

	// 前回のデータを保存
	mouseStateOld = mouseState;

	//// ウィンドウのクライアント領域を取得する
	//RECT rc;
	//GetClientRect(CWindowAPI::GethWnd(), &rc);

	//// クライアント領域を画面座標に変換する
	//POINT pt = { rc.left, rc.top };
	//POINT pt2 = { rc.right, rc.bottom };
	//ClientToScreen(CWindowAPI::GethWnd(), &pt);
	//ClientToScreen(CWindowAPI::GethWnd(), &pt2);
	//SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

	//// カーソルの動作範囲を制限する
	//ClipCursor(&rc);

	// スクリーン座標を取得
	GetCursorPos(&po);

	ScreenToClient(CWindowAPI::GethWnd(), &po);

	// ワールド座標変換
	WorldXZUpdate();

	MousePos.x = (float)po.x;
	MousePos.y = (float)po.y;

	// デバイスからデータを取得
	//*******************************************************************************************************
	if( SUCCEEDED( hr = pDIDevMouse->GetDeviceState( sizeof( mouseState ), &mouseState ) ) )
	{
		// ^ = 排他的論理和 (違ったら1、同じだったら0)

		mouseStateTrigger.lX = ( ( mouseStateOld.lX ^ mouseState.lX ) & mouseState.lX );
		mouseStateTrigger.lY = ( ( mouseStateOld.lY ^ mouseState.lY ) & mouseState.lY );
		mouseStateTrigger.lZ = ( ( mouseStateOld.lZ ^ mouseState.lZ ) & mouseState.lZ );

		for( int cnt = 0 ; cnt < 8 ; cnt ++ )
		{
			// トリガー情報判定
			mouseStateTrigger.rgbButtons[cnt] = ( ( mouseStateOld.rgbButtons[cnt] ^ mouseState.rgbButtons[cnt] ) & mouseState.rgbButtons[cnt] );

			// リリース情報判定
			mouseStateRelease.rgbButtons[cnt] = ( ( mouseStateOld.rgbButtons[cnt] ^ mouseState.rgbButtons[cnt] ) & mouseStateOld.rgbButtons[cnt] );

			// プレス情報判定
			mouseStatePress.rgbButtons[cnt] = mouseState.rgbButtons[cnt];
		}
	}
	else
	{
		// マウスへのアクセス権を取得
		pDIDevMouse->Acquire();
	}
}

//***********************************************************************************************************
// ワールド座標変換
//***********************************************************************************************************
void CInput::WorldUpdate( D3DXVECTOR3* pWorld, float fZ )
{
	// 各行列の逆行列を算出
	//*******************************************************************************************************
	D3DXMatrixInverse( &InvView, NULL, Camera.GetPView() );
	D3DXMatrixInverse( &InvPrj, NULL, Camera.GetPPrj() );
	D3DXMatrixIdentity( &VP );
	
	VP._11 = SCREEN_WIDTH / 2.0f; VP._22 = -SCREEN_HEIGHT / 2.0f;
	VP._41 = SCREEN_WIDTH / 2.0f; VP._42 = SCREEN_HEIGHT / 2.0f;
	D3DXMatrixInverse( &InvViewport, NULL, &VP );

	// 逆変換
	//*******************************************************************************************************
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord( pWorld, &D3DXVECTOR3( MousePos.x,MousePos.y, fZ ), &tmp );
	
}

//***********************************************************************************************************
// ワールド座標のXZ平面の交差点を算出
//***********************************************************************************************************
void CInput::WorldXZUpdate(void)
{
	WorldUpdate( &nearpos, 0.0f );
	WorldUpdate( &farpos, 1.0f );
	ray = farpos - nearpos;
	D3DXVec3Normalize( &ray, &ray );

	// 床との交差が起きている場合は交点を
	// 起きていない場合は遠くの壁との交点を出力
	if( ray.y <= 0 ) 
	{
		// 床交点
		Lray		= D3DXVec3Dot( &ray, &D3DXVECTOR3( 0,1,0 ) );
		LP0			= D3DXVec3Dot( &( -nearpos ), &D3DXVECTOR3( 0,1,0 ) );
		*pWorldPos	= nearpos + ( LP0 / Lray )*ray;
	}
	else 
	{
		*pWorldPos = farpos;
	}
}

//***********************************************************************************************************
// キーボード使用時に使用
// 引数：使いたいキー名、使いたい状態(TRIGGER等…)
//***********************************************************************************************************
bool CInput::GetKeyboardData( int nKey, Key_Data nData )
{
	switch ( nData )
	{
	case PRESS:   return ( aKeyStatePress[nKey]   & 0x80 ) ? true: false; break;
	case REPEAT:  return ( aKeyStateRepeat[nKey]  & 0x80 ) ? true: false; break;
	case TRIGGER: return ( aKeyStateTrigger[nKey] & 0x80 ) ? true: false; break;
	case RELEASE: return ( aKeyStateRelease[nKey] & 0x80 ) ? true: false; break;
	
	default : break;
	}

	return false;
}

//***********************************************************************************************************
// マウス使用時に使用
// 引数：使いたいキー名、使いたい状態(TRIGGER等…)
//***********************************************************************************************************
bool CInput::GetMouseData( Mouse_Data nButton, int nData )
{
	switch ( nData )
	{
	case PRESS:   return ( mouseStatePress.rgbButtons[nButton]   & 0x80 ) ? true : false; break;
	case TRIGGER: return ( mouseStateTrigger.rgbButtons[nButton] & 0x80 ) ? true : false; break;
	case RELEASE: return ( mouseStateRelease.rgbButtons[nButton] & 0x80 ) ? true : false; break;

	default : break;
	}

	return false;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************