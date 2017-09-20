//***********************************************************************************************************
//
// ���̓f�o�C�X�Ǘ��N���X( �L�[�{�[�h�A�}�E�X )
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CWindowAPI.h"
#include "CDirectX.h"
#include "Camera.h"

//***********************************************************************************************************
// �}�N����`
//***********************************************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[

//***********************************************************************************************************
// �񋓌^��`
//***********************************************************************************************************

// �L�[�{�[�h�E�}�E�X�Ŏg�p
//*********************
enum Key_Data
{
	PRESS = 0,		// ��������
	REPEAT,			// ���������Ă����
	TRIGGER,		// �������u��
	RELEASE			// �������u��
};

// �}�E�X�Ŏg�p
//*********************
enum Mouse_Data
{
	L_BUTTON = 0,	// ���N���b�N
	R_BUTTON,		// �E�N���b�N
	C_BUTTON		// �z�C�[���{�^��
};

//***********************************************************************************************************
// �N���X��`
//***********************************************************************************************************
class CInput
{
private:
	static	LPDIRECTINPUTDEVICE8	pDIDevKeyboard;		// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static	LPDIRECTINPUTDEVICE8	pDIDevMouse;		// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
	static	LPDIRECTINPUT8			pDInput;			// DirectInput�C���^�[�t�F�[�X�ւ̃|�C���^


	static	BYTE	aKeyStatePress[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static	BYTE	aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static	BYTE	aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static	BYTE	aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	static	int		aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

	static	DIMOUSESTATE2		mouseState;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	static	DIMOUSESTATE2		mouseStateTrigger;		// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	static	DIMOUSESTATE2		mouseStatePress;		// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	static	DIMOUSESTATE2		mouseStateRelease;		// �}�E�X�̏�Ԃ��󂯎�郏�[�N

	static POINT				po;						// �}�E�X���\���̃|�C���^
	static D3DXVECTOR3			MousePos;				// �}�E�X���W�󂯓n���p

	static D3DXVECTOR3*			pWorldPos;				// ���[���h���W�p	
	static D3DXVECTOR3			WorldPos;
	
	static D3DXMATRIX InvView;
	static D3DXMATRIX InvPrj;
	static D3DXMATRIX VP;
	static D3DXMATRIX InvViewport;

	// XZ���ʕϊ��p
	static D3DXVECTOR3 nearpos;
	static D3DXVECTOR3 farpos;
	static D3DXVECTOR3 ray;
	static float Lray;
	static float LP0;

	CCamera	Camera;

	void		Keyboard_Update(void);													// �L�[�{�[�h���X�V
	void		Mouse_Update(void);														// �}�E�X���X�V
	
	void		WorldUpdate(D3DXVECTOR3* pWorld, float fZ);								// ���[���h���W�X�V
	void		WorldXZUpdate(void);													// ���[���hXZ���W�X�V

public:
	HRESULT	Init(HINSTANCE hInstance, HWND hWnd );										// ������
	void		Finalise(void);															// �I��
	void		Update(void);															// �X�V

	static bool		GetKeyboardData( int nKey, Key_Data nData );						// �L�[�{�[�h���g�������Ƃ��Ɏg�p( �g�p����L�[���A��� )
	static bool		GetMouseData( Mouse_Data nButton, int nData );						// �}�E�X���g�������Ƃ��Ɏg�p( �g�p����{�^�����A��� )

	// �ϐ������n���֐���
	static D3DXVECTOR3	GetMousePos(void) { return MousePos; };							// �}�E�X���W��Ԃ�(X,Y)
	static float		GetMouseWheel(void) { return (float)(mouseStateTrigger.lZ); };	// �z�C�[���ړ��ʂ�Ԃ�(X,Y)
	static D3DXVECTOR3	GetToWorldPos(void) { return WorldPos; };						// �}�E�X���W��胏�[���h���W���擾
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************