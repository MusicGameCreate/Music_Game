//***********************************************************************************************************
//
// DirectX���ݒ�( 2D,3D�� )
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CDirectX.h"


//***********************************************************************************************************
// �ÓI�ϐ���`
//***********************************************************************************************************
LPDIRECT3D9			CDirectX::pD3D			= NULL;
LPDIRECT3DDEVICE9	CDirectX::pD3DDevice	= NULL;

//***********************************************************************************************************
// ����������
// bWindow   :�E�C���h�E���[�h�ɂ��邩�ǂ���
//***********************************************************************************************************
HRESULT CDirectX::Init( HWND hWnd , bool bWindow )
{
	D3DPRESENT_PARAMETERS		d3dpp;
	D3DDISPLAYMODE				d3ddm;

	//Direct3D�I�u�W�F�N�g�̐���
	//*******************************************************************************************************
	if( ( pD3D = Direct3DCreate9(D3D_SDK_VERSION) ) == NULL )
		return E_FAIL;

	//���݂̃f�B�X�v���C���[�h���擾
	//*******************************************************************************************************
	if( FAILED( pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return E_FAIL;


	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	//*******************************************************************************************************
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//���[�����[���N���A
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= d3ddm.Format;				//�J���[���[�h�̎w��
	d3dpp.BackBufferCount			= 1;						//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//�f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					//�E�C���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						//�f�v�X�o�b�t�@(Z�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//�f�v�X�o�b�t�@�Ƃ���16bit���g��

	if( bWindow )
	{
		//�E�C���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz	= 0;								//���t���b�V�����[�g(�w��ł��Ȃ��̂�0�Œ�)
		d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;	//�C���^�[�o��(VSync��҂����ɕ`��)
	}
	else
	{
		//�t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
		d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��(VSync��҂��ĕ`��)
	}

	//�f�o�C�X�I�u�W�F�N�g�̐���
	//[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	if ( FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,						//�f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							//�f�o�C�X�^�C�v
									hWnd,									//�t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	//�f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,									//�f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&pD3DDevice)))							//�f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		//��L�̐ݒ肪���s������
		//[�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs��
		if ( FAILED( pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&pD3DDevice)))
		{

			//��L�̐ݒ肪���s������
			//[�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs��
			if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&pD3DDevice)))
			{
				//���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	//***********************************

	//���ʂ��J�����O
	pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	//�A���t�@�u�����h���s��
	pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	//�\�[�X�̐ݒ�
	pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//�f�X�g�̐ݒ�
	pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	//
	pD3DDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
	
	// �e�N�X�`���X�e�[�g�p�����[�^�̐ݒ�
	//**************************************

	// �A���t�@�u�����f�B���O������ݒ�
	//**************************************
	

	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1,   D3DTA_TEXTURE );	// �e�N�X�`��
																				// �~
	pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2,   D3DTA_DIFFUSE );	// �f�B�t���[�Y
	pD3DDevice->SetTextureStageState( 0,   D3DTSS_COLOROP, D3DTOP_MODULATE);	// �e�N�X�`���ƃf�B�t���[�Y����Z�������ďo��
	

	pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,   D3DTA_TEXTURE );	// �e�N�X�`��
																				// �~
	pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2,   D3DTA_DIFFUSE );	// �f�B�t���[�Y
	pD3DDevice->SetTextureStageState( 0,   D3DTSS_ALPHAOP, D3DTOP_MODULATE );	// �e�N�X�`���ƃf�B�t���[�Y����Z�������ďo��

	//�T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	//**************************************

	//�e�N�X�`��U�l�̌J��Ԃ��ݒ�
	pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );

	//�e�N�X�`��V�l�̌J��Ԃ��ݒ�
	pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

	//�e�N�X�`���g�厞�̕�Ԑݒ�
	pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	//�e�N�X�`���k�����̕�Ԑݒ�
	pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	pD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

	// ���C�g��L���ɂ���
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// �A���r�G���g���C�g�i�����j��ݒ肷��
	pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
	pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);


	return S_OK;
}

//***********************************************************************************************************
// �`��J�n
//***********************************************************************************************************
bool CDirectX::Render_Begin()
{
	//�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//Direct3D�ɂ��`��̊J�n
	return SUCCEEDED( pD3DDevice->BeginScene() );
}

//***********************************************************************************************************
// �`��I��
//***********************************************************************************************************
void CDirectX::Render_End()
{
	//Direct3D�ɂ��`��̏I��
	pD3DDevice->EndScene();

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	//pSourceRect			:�]������`
	//pDestRect				:�]������`
	//hDestWindowOverride	:�]�����E�C���h�E�ւ̃|�C���^
	//pDirtyRegion			:�ʏ��NULL��
	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//***********************************************************************************************************
// �I������
//***********************************************************************************************************
void CDirectX::Finalise()
{
	if ( pD3DDevice != NULL )
	{	//�f�o�C�X�̊J��
		pD3DDevice->Release();
		pD3DDevice = NULL;
	}

	if ( pD3D != NULL )
	{	//Direct3D�I�u�W�F�N�g�̊J��
		pD3D->Release();
		pD3D = NULL;
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************