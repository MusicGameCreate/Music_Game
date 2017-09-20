//**********************************************************************************************************
//
// ���̓f�o�C�X�Ǘ��N���X(�L�[�{�[�h�A�}�E�X)
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CInput.h"

//***********************************************************************************************************
// �ÓI�ϐ���`
//***********************************************************************************************************

// ����
//***********************************************************************************************************
LPDIRECTINPUT8			CInput::pDInput			= NULL;				// DirectInput�C���^�[�t�F�[�X�ւ̃|�C���^	

// �L�[�{�[�h�p
//***********************************************************************************************************
LPDIRECTINPUTDEVICE8	CInput::pDIDevKeyboard	= NULL;				// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^

BYTE					CInput::aKeyStatePress[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N(�����Ă����)
BYTE					CInput::aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N(1�񔻒�)
BYTE					CInput::aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N(1�񂠂Ə������O����PRESS)
BYTE					CInput::aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N(�L�[���痣�����u��)
int						CInput::aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

// �}�E�X�p
//***********************************************************************************************************
LPDIRECTINPUTDEVICE8	CInput::pDIDevMouse		= NULL;			// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^

DIMOUSESTATE2			CInput::mouseState;						// �}�E�X�̏�Ԃ��󂯎�郏�[�N
DIMOUSESTATE2			CInput::mouseStateTrigger;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N(�g���K�[���)
DIMOUSESTATE2			CInput::mouseStatePress;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N(�v���X���)
DIMOUSESTATE2			CInput::mouseStateRelease;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N(�����[�X���)

POINT					CInput::po;								// �}�E�X���\���̃|�C���^
D3DXVECTOR3				CInput::MousePos;						// �}�E�X���W���i�[(X,Y)
D3DXVECTOR3				CInput::WorldPos;						// ���[���h���W�i�[�p(X,Y,Z)
D3DXVECTOR3*			CInput::pWorldPos;						// ���[���h���W�|�C���^

//--- ���[���h���W�ϊ��p ---
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
// ������
//***********************************************************************************************************
HRESULT	CInput::Init(HINSTANCE hInstance, HWND hWnd )
{
	HRESULT	hr;

	// �X�N���[�����W���擾
	//*******************************************************************************************************
	GetCursorPos(&po);

	MousePos.x = 0.0f;
	MousePos.y = 0.0f;
	MousePos.z = 0.0f;

	// NULL����
	//*******************************************************************************************************
	pWorldPos = NULL;
	
	// ���[���h�ϊ��p�ϐ�������
	//*******************************************************************************************************
	WorldPos	= D3DXVECTOR3();

	nearpos		= D3DXVECTOR3();
	farpos		= D3DXVECTOR3();
	ray			= D3DXVECTOR3();

	Lray		= 0.0f;
	LP0			= 0.0f;

	pWorldPos	= &WorldPos;

	// �E�B���h�E�̃N���C�A���g�̈���擾����
	RECT rc;
	GetClientRect(CWindowAPI::GethWnd(), &rc);

	// �N���C�A���g�̈����ʍ��W�ɕϊ�����
	POINT pt = { rc.left, rc.top };
	POINT pt2 = { rc.right, rc.bottom };
	ClientToScreen(CWindowAPI::GethWnd(), &pt);
	ClientToScreen(CWindowAPI::GethWnd(), &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

	// �J�[�\���̓���͈͂𐧌�����
	//ClipCursor(&rc);

	// ���W����
	//*******************************************************************************************************
	MousePos.x = (float)po.x;
	MousePos.y = (float)po.y;

	if( pDInput == NULL )
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(	hInstance, 
									DIRECTINPUT_VERSION,
									IID_IDirectInput8, 
									(void**)&pDInput, 
									NULL	);
	}

	if( FAILED(hr) )
	{
		MessageBox( hWnd, "DirectInput�I�u�W�F�N�g���쐬�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
		return hr;
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	//*******************************************************************************************************
	if( FAILED( hr = pDInput->CreateDevice(GUID_SysKeyboard, &pDIDevKeyboard, NULL) ) )
	{
		MessageBox( hWnd, "�L�[�{�[�h�����o����܂���ł����B", "�x���I", MB_ICONWARNING );
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	//*******************************************************************************************************
	if( FAILED( hr = pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard)) )
	{
		MessageBox( hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	//*******************************************************************************************************
	if( FAILED( hr = pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) ) )
	{
		MessageBox( hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	//*******************************************************************************************************
	pDIDevKeyboard->Acquire();

	// �f�o�C�X�I�u�W�F�N�g���쐬
	//*******************************************************************************************************
	if( FAILED( hr = pDInput->CreateDevice( GUID_SysMouse, &pDIDevMouse, NULL ) ) || pDIDevMouse == NULL )
	{
		MessageBox(hWnd, "�}�E�X�����o����܂���ł���", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	//*******************************************************************************************************
	if(FAILED( hr = pDIDevMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	//*******************************************************************************************************
	if(FAILED( hr = pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̐ݒ�
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
			MessageBox( hWnd, "�}�E�X�f�o�C�X��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return hr;
		}
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	//**********************************************
	pDIDevMouse->Acquire();

	return S_OK;
}

//***********************************************************************************************************
// ���̓f�o�C�X�̏I������
//***********************************************************************************************************
void CInput::Finalise(void)
{
	if( pDInput != NULL)
	{	// DirectInput�I�u�W�F�N�g�̊J��
		pDInput->Release();
		pDInput = NULL;
	}

	if( pDIDevKeyboard != NULL )
	{	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		pDIDevKeyboard->Unacquire();
		pDIDevKeyboard->Release();
		pDIDevKeyboard = NULL;
	}

	if ( pDIDevMouse	!= NULL )
	{	// ���̓f�o�C�X(�}�E�X)�̊J��
		// �}�E�X�ւ̃A�N�Z�X�����J��(���͐���I��)
		pDIDevMouse->Unacquire();
		pDIDevMouse->Release();
		pDIDevMouse = NULL;
	}
}

//***********************************************************************************************************
// �X�V
//***********************************************************************************************************
void CInput::Update(void)
{
	// �L�[�{�[�h���X�V
	//*******************************************************************************************************
	Keyboard_Update();



	// �}�E�X���X�V
	//*******************************************************************************************************
	Mouse_Update();
}

//***********************************************************************************************************
// �L�[�{�[�h���X�V
//***********************************************************************************************************
void CInput::Keyboard_Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	//*******************************************************************************************************
	if( SUCCEEDED( pDIDevKeyboard->GetDeviceState( sizeof( aKeyState ), aKeyState ) ) )
	{
		for( int nCnKey = 0 ; nCnKey < NUM_KEY_MAX ; nCnKey ++ )
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			// aKeyState�́A���݂̃t���[���̏��
			// aKeyState�́A1�t���[���O�̏��
			aKeyStateTrigger[nCnKey] = aKeyState[nCnKey] & (~aKeyStatePress[nCnKey] );	//�g���K�[���
			aKeyStateRelease[nCnKey] = aKeyStatePress[nCnKey] & (~aKeyState[nCnKey] );	//�����[�X���

			// �L�[���s�[�g���𐶐�
			if( aKeyState[nCnKey] )
			{
				if( aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT )
				{
					aKeyStateRepeatCnt[nCnKey]++;
					if( aKeyStateRepeatCnt[nCnKey] == 1 ||  aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT )
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�
			aKeyStatePress[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		pDIDevKeyboard->Acquire();
	}
}

//***********************************************************************************************************
// �}�E�X���X�V
//***********************************************************************************************************
void CInput::Mouse_Update(void)
{
	HRESULT	hr;
	DIMOUSESTATE2 mouseStateOld;

	// �O��̃f�[�^��ۑ�
	mouseStateOld = mouseState;

	//// �E�B���h�E�̃N���C�A���g�̈���擾����
	//RECT rc;
	//GetClientRect(CWindowAPI::GethWnd(), &rc);

	//// �N���C�A���g�̈����ʍ��W�ɕϊ�����
	//POINT pt = { rc.left, rc.top };
	//POINT pt2 = { rc.right, rc.bottom };
	//ClientToScreen(CWindowAPI::GethWnd(), &pt);
	//ClientToScreen(CWindowAPI::GethWnd(), &pt2);
	//SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);

	//// �J�[�\���̓���͈͂𐧌�����
	//ClipCursor(&rc);

	// �X�N���[�����W���擾
	GetCursorPos(&po);

	ScreenToClient(CWindowAPI::GethWnd(), &po);

	// ���[���h���W�ϊ�
	WorldXZUpdate();

	MousePos.x = (float)po.x;
	MousePos.y = (float)po.y;

	// �f�o�C�X����f�[�^���擾
	//*******************************************************************************************************
	if( SUCCEEDED( hr = pDIDevMouse->GetDeviceState( sizeof( mouseState ), &mouseState ) ) )
	{
		// ^ = �r���I�_���a (�������1�A������������0)

		mouseStateTrigger.lX = ( ( mouseStateOld.lX ^ mouseState.lX ) & mouseState.lX );
		mouseStateTrigger.lY = ( ( mouseStateOld.lY ^ mouseState.lY ) & mouseState.lY );
		mouseStateTrigger.lZ = ( ( mouseStateOld.lZ ^ mouseState.lZ ) & mouseState.lZ );

		for( int cnt = 0 ; cnt < 8 ; cnt ++ )
		{
			// �g���K�[��񔻒�
			mouseStateTrigger.rgbButtons[cnt] = ( ( mouseStateOld.rgbButtons[cnt] ^ mouseState.rgbButtons[cnt] ) & mouseState.rgbButtons[cnt] );

			// �����[�X��񔻒�
			mouseStateRelease.rgbButtons[cnt] = ( ( mouseStateOld.rgbButtons[cnt] ^ mouseState.rgbButtons[cnt] ) & mouseStateOld.rgbButtons[cnt] );

			// �v���X��񔻒�
			mouseStatePress.rgbButtons[cnt] = mouseState.rgbButtons[cnt];
		}
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����擾
		pDIDevMouse->Acquire();
	}
}

//***********************************************************************************************************
// ���[���h���W�ϊ�
//***********************************************************************************************************
void CInput::WorldUpdate( D3DXVECTOR3* pWorld, float fZ )
{
	// �e�s��̋t�s����Z�o
	//*******************************************************************************************************
	D3DXMatrixInverse( &InvView, NULL, Camera.GetPView() );
	D3DXMatrixInverse( &InvPrj, NULL, Camera.GetPPrj() );
	D3DXMatrixIdentity( &VP );
	
	VP._11 = SCREEN_WIDTH / 2.0f; VP._22 = -SCREEN_HEIGHT / 2.0f;
	VP._41 = SCREEN_WIDTH / 2.0f; VP._42 = SCREEN_HEIGHT / 2.0f;
	D3DXMatrixInverse( &InvViewport, NULL, &VP );

	// �t�ϊ�
	//*******************************************************************************************************
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord( pWorld, &D3DXVECTOR3( MousePos.x,MousePos.y, fZ ), &tmp );
	
}

//***********************************************************************************************************
// ���[���h���W��XZ���ʂ̌����_���Z�o
//***********************************************************************************************************
void CInput::WorldXZUpdate(void)
{
	WorldUpdate( &nearpos, 0.0f );
	WorldUpdate( &farpos, 1.0f );
	ray = farpos - nearpos;
	D3DXVec3Normalize( &ray, &ray );

	// ���Ƃ̌������N���Ă���ꍇ�͌�_��
	// �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if( ray.y <= 0 ) 
	{
		// ����_
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
// �L�[�{�[�h�g�p���Ɏg�p
// �����F�g�������L�[���A�g���������(TRIGGER���c)
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
// �}�E�X�g�p���Ɏg�p
// �����F�g�������L�[���A�g���������(TRIGGER���c)
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