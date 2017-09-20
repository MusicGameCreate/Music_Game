//***********************************************************************************************************
//
// 入力デバイス管理クラス( キーボード、マウス )
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CWindowAPI.h"
#include "CDirectX.h"
#include "Camera.h"

//***********************************************************************************************************
// マクロ定義
//***********************************************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

//***********************************************************************************************************
// 列挙型定義
//***********************************************************************************************************

// キーボード・マウスで使用
//*********************
enum Key_Data
{
	PRESS = 0,		// 押したら
	REPEAT,			// 押し続けている間
	TRIGGER,		// 押した瞬間
	RELEASE			// 離した瞬間
};

// マウスで使用
//*********************
enum Mouse_Data
{
	L_BUTTON = 0,	// 左クリック
	R_BUTTON,		// 右クリック
	C_BUTTON		// ホイールボタン
};

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class CInput
{
private:
	static	LPDIRECTINPUTDEVICE8	pDIDevKeyboard;		// 入力デバイス(キーボード)へのポインタ
	static	LPDIRECTINPUTDEVICE8	pDIDevMouse;		// 入力デバイス(マウス)へのポインタ
	static	LPDIRECTINPUT8			pDInput;			// DirectInputインターフェースへのポインタ


	static	BYTE	aKeyStatePress[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	static	BYTE	aKeyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	static	BYTE	aKeyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	static	BYTE	aKeyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
	static	int		aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

	static	DIMOUSESTATE2		mouseState;				// マウスの状態を受け取るワーク
	static	DIMOUSESTATE2		mouseStateTrigger;		// マウスの状態を受け取るワーク
	static	DIMOUSESTATE2		mouseStatePress;		// マウスの状態を受け取るワーク
	static	DIMOUSESTATE2		mouseStateRelease;		// マウスの状態を受け取るワーク

	static POINT				po;						// マウス情報構造体ポインタ
	static D3DXVECTOR3			MousePos;				// マウス座標受け渡し用

	static D3DXVECTOR3*			pWorldPos;				// ワールド座標用	
	static D3DXVECTOR3			WorldPos;
	
	static D3DXMATRIX InvView;
	static D3DXMATRIX InvPrj;
	static D3DXMATRIX VP;
	static D3DXMATRIX InvViewport;

	// XZ平面変換用
	static D3DXVECTOR3 nearpos;
	static D3DXVECTOR3 farpos;
	static D3DXVECTOR3 ray;
	static float Lray;
	static float LP0;

	CCamera	Camera;

	void		Keyboard_Update(void);													// キーボード情報更新
	void		Mouse_Update(void);														// マウス情報更新
	
	void		WorldUpdate(D3DXVECTOR3* pWorld, float fZ);								// ワールド座標更新
	void		WorldXZUpdate(void);													// ワールドXZ座標更新

public:
	HRESULT	Init(HINSTANCE hInstance, HWND hWnd );										// 初期化
	void		Finalise(void);															// 終了
	void		Update(void);															// 更新

	static bool		GetKeyboardData( int nKey, Key_Data nData );						// キーボードを使いたいときに使用( 使用するキー名、状態 )
	static bool		GetMouseData( Mouse_Data nButton, int nData );						// マウスを使いたいときに使用( 使用するボタン名、状態 )

	// 変数引き渡し関数↓
	static D3DXVECTOR3	GetMousePos(void) { return MousePos; };							// マウス座標を返す(X,Y)
	static float		GetMouseWheel(void) { return (float)(mouseStateTrigger.lZ); };	// ホイール移動量を返す(X,Y)
	static D3DXVECTOR3	GetToWorldPos(void) { return WorldPos; };						// マウス座標よりワールド座標を取得
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************