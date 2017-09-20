//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "Define.h"	
#include "CWindowAPI.h"		// WindowAPI���
#include "CDirectX.h"		// DirectX���
#include "CFPS.h"			// FPS���
#include "CInput.h"			// �L�[�{�[�h�A�}�E�X���
#include "Camera.h"			// �J�������
#include "CLight.h"			// ���C�g���
#include "SceneMgr.h"		// �V�[�����
#include "CMusic_Manager.h"	// �ȏ��

//#define _ITERATOR_DEBUG_LEVEL (0)

//***********************************************************************************************************
//
// ���C���֐�
//
//***********************************************************************************************************
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//*******************************************************************************************************
	// �N���X��`
	//*******************************************************************************************************
	CWindowAPI		WindowAPI;		// WindowAPI�N���X
	CDirectX		DirectX;		// DirectX�N���X
	CInput			Input;			// �L�[�{�[�h�A�}�E�X�N���X
	CFPS			FPS;			// FPS�N���X
	CCamera			Camera;			// �J�����N���X
	CLight			Light;			// �����N���X
	CMusic_Manager	Music_Manager;	// �ȃf�[�^�ꊇ�Ǘ��N���X

	//*******************************************************************************************************
	// �e��ݒ�I�[��������
	//*******************************************************************************************************
	WindowAPI.Init( hInstance );					// WindowAPI���
	DirectX.Init( WindowAPI.GethWnd() ,true );		// DirectX���
	Input.Init( hInstance, WindowAPI.GethWnd() );	// �L�[�{�[�h�A�}�E�X���
	FPS.Init( DirectX.Get_pD3DDevice() );			// FPS���
	Music_Manager.Init();							// �ȏ��
	Music_Manager.Load();							// �ȏ��ǂݍ���
	Camera.Init();									// �J�������
	Light.Init();									// ���C�g���
	CSceneMgr		SceneMgr;		// �V�[���ꊇ�Ǘ��N���X
	SceneMgr.Initialize();							// �V�[�����

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	//*******************************************************************************************************
	WindowAPI.Display( nCmdShow );

	// ���b�Z�[�W���[�v
	//*******************************************************************************************************
	while( WindowAPI.WindowMessage() != 1 )
	{
		// �E�C���h�E���X�V
		WindowAPI.Update();

		if ( FPS.Update() == true )
		{
			// �`��J�n
			//***********************************************************************************************
			DirectX.Render_Begin();

			// �L�[�{�[�h�A�}�E�X���X�V
			Input.Update();
			// �J�������X�V
			Camera.Update();
			// ���C�g���X�V
			Light.Update();
			// �J�����Z�b�g
			Camera.Set();

			// �V�[���X�V
			SceneMgr.Update();

			// �V�[���`��
			SceneMgr.Draw();

//#ifdef _DEBUG
			// FPS�`��
			FPS.Draw();
//#endif
			// �`��I��
			//***********************************************************************************************
			DirectX.Render_End();
		}
	}

	//*******************************************************************************************************
	// �e��ݒ�I�[���J��
	//*******************************************************************************************************
	SceneMgr.Finalize();
	WindowAPI.Finalise( hInstance );	// �E�C���h�E�N���X�̓o�^������
	DirectX.Finalise();					// DirectX�����
	Input.Finalise();					// �L�[�{�[�h�A�}�E�X�����
	FPS.Finalise();						// FPS���̏I������
	Camera.Finalise();					// �J���������
	Music_Manager.Finalise();			// �ȏ����

	return (int)WindowAPI.Getmsg().wParam;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************