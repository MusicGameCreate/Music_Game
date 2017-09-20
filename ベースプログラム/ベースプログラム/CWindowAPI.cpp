//***********************************************************************************************************
//
// WindowAPI�̊��ݒ�
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "Define.h"
#include "CWindowAPI.h"

//***********************************************************************************************************
// �ÓI�ϐ���`
//***********************************************************************************************************
WNDCLASSEX	CWindowAPI::wcex;
HWND		CWindowAPI::hWnd;
MSG			CWindowAPI::msg;

//***********************************************************************************************************
// �E�C���h�E��񏉊���
//***********************************************************************************************************
void CWindowAPI::Init( HINSTANCE hInstance )
{
DWORD dwStyle = WS_OVERLAPPED;
	DWORD dwExStyle = 0;
	// �E�B���h�E�̃T�C�Y�w��
	RECT clientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �w�肳�ꂽ�N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W�v�Z
	::AdjustWindowRect(&clientRect, 	// �N���C�A���g�̈�̍��W���������\���̂ւ̃|�C���^
		dwStyle,			// �E�B���h�E�X�^�C��
		dwExStyle);						// ���j���[�������ǂ����̎w��

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

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�C���h�E�̍쐬
	hWnd = CreateWindowEx(	0,
							CLASS_NAME,
							WINDOW_NAME,
							// �t���X�N���[�����[�h�ɂ���Ȃ灨	WS_VISIBLE | WS_POPUP
							// �E�C���h�E���[�h�ɂ���Ȃ灨		WS_OVERLAPPEDWINDOW
							WS_OVERLAPPEDWINDOW,
							0,				// �E�C���h�E�̉������̈ʒu
							0,				// �E�C���h�E�̏c�����̈ʒu
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
// �E�C���h�E�X�V����
//***********************************************************************************************************
void CWindowAPI::Update()
{

}

//***********************************************************************************************************
// �E�C���h�E�\������
//***********************************************************************************************************
void CWindowAPI::Display( int nCmdShow )
{
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
}

//***********************************************************************************************************
// �E�C���h�E�j������
//***********************************************************************************************************
void CWindowAPI::Finalise( HINSTANCE hInstance )
{
	UnregisterClass(CLASS_NAME, wcex.hInstance);
}

//***********************************************************************************************************
// �E�C���h�E�v���V�[�W��
//***********************************************************************************************************
LRESULT CALLBACK CWindowAPI::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�������ꂽ�Ƃ�
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
// �E�C���h�E���b�Z�[�W
//***********************************************************************************************************
int CWindowAPI::WindowMessage()
{
	if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0 )	//���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
	{
		//Windows�̏���
		if(msg.message == WM_QUIT)
		{
			//�v���O�����I��
			return 1;
		}
		else
		{
			//���b�Z�[�W�̖|��Ƒ��o
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