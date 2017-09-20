//***********************************************************************************************************
// 
// FPS�֘A�\�z�N���X
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CFPS.h"


//***********************************************************************************************************
// �ÓI�ϐ���`
//***********************************************************************************************************
int	CFPS::nCountFPS = 0;


//***********************************************************************************************************
// FPS�֘A������
//***********************************************************************************************************
void CFPS::Init( LPDIRECT3DDEVICE9	pDevice )
{
	pD3DXFont		= NULL;

//#ifdef _DEBUG
	MousePos		= D3DXVECTOR3();
	WorldPos		= D3DXVECTOR3();
	fMouseWheel		= 0.0f;
//#endif

	// �t���[���J�E���g������
	timeBeginPeriod(1);		//����\�̐ݒ�

	dwExecLastTime	= //�~���b�Ԋu�Ŏ擾
	dwFPSLastTime	= timeGetTime();

	dwCurrentTime	= 
	dwFrameCount	= 0;

	//���\���p�t�H���g��ݒ�
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
// FPS�I������
//***********************************************************************************************************
void CFPS::Finalise()
{
	if ( pD3DXFont != NULL )
	{	//���\���p�t�H���g�̊J��
		pD3DXFont->Release();
		pD3DXFont = NULL;
	}
}

//***********************************************************************************************************
// FPS�X�V
//***********************************************************************************************************
bool CFPS::Update()
{
	dwCurrentTime = timeGetTime();

//#ifdef _DEBUG
	MousePos	= CInput::GetMousePos();	// �}�E�X���W�擾
	WorldPos	= CInput::GetToWorldPos();	// ���[���h���W�擾
	fMouseWheel = CInput::GetMouseWheel();	// �}�E�X�z�C�[���ړ��ʎ擾
//#endif

	if (( dwCurrentTime - dwFPSLastTime ) >= 500 )
	{	//0.5�b���ƂɎ��s
		//FPS�𑪒�
		nCountFPS		= ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );

		//FPS�𑪒肵��������ۑ�
		dwFPSLastTime	= dwCurrentTime;
		dwFrameCount	= 0; //�J�E���g�N���A
	}

	if ( ( float )( dwCurrentTime - dwExecLastTime ) >= ( 1000.0f/60.0f ) )
	{
		dwExecLastTime = dwCurrentTime;
		dwFrameCount ++;	//�J�E���g���Z

		return true;
	}
	else
	{
		return false;
	}
}

//***********************************************************************************************************
//
// FPS�`��
//
//***********************************************************************************************************
void CFPS::Draw()
{
//#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];	//�����i�[�p


	wsprintf(	aStr, 
				"FPS:%2d\nMousePos.X:%5dY:%5dZ:%5d\nWorldPos.X:%5dY:%5dZ:%5d\n", 
				nCountFPS, 
				(int)MousePos.x, (int)MousePos.y, (int)fMouseWheel, 
				(int)WorldPos.x, (int)WorldPos.y, (int)WorldPos.z );


	//�e�L�X�g�`��
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