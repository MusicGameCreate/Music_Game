//***********************************************************************************************************
//
// 2D�摜�`���{�N���X
//
//***********************************************************************************************************


//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CTexture_2D_Base.h"


//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
CTexture_2D_Base::CTexture_2D_Base()
{
	// �Ƃ肠����NULL��
	//*******************************************************************************************************
	pTexture			= NULL;	// �e�N�X�`���摜���
	Tex_2D_Data			= NULL;	// �e�N�X�`�����z��
	aVertex				= NULL; // ���_���z��

	// �I�u�W�F�N�g���͍ŏ���1�ɐݒ�
	//*******************************************************************************************************
	nObject_Num			= 1;

	// �e�N�X�`�����͍ŏ���1�ɐݒ�
	//*******************************************************************************************************
	nUse_Texture_Num	= 1;
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
CTexture_2D_Base::~CTexture_2D_Base()
{

}

//***********************************************************************************************************
// ������
//***********************************************************************************************************
void CTexture_2D_Base::Init()
{
	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	// ���_�� * ���� = �K�v�ȃI�u�W�F�N�g���̒��_��(�O����4���g�p)
	//*******************************************************************************************************
	aVertex		= new VERTEX_2D[NUM_VERTEX * nObject_Num];

	// �g�p�e�N�X�`�����T�C�Y���m��
	//*******************************************************************************************************
	pTexture	= new LPDIRECT3DTEXTURE9[nUse_Texture_Num];

	// ���_��񏉊���
	//*******************************************************************************************************
	MakeVertex();

}

//***********************************************************************************************************
// �e�N�X�`���ǂݍ���
//***********************************************************************************************************
void CTexture_2D_Base::Load_Texture( char* TEXTURE_FILE, int NUMBER )
{	
	//*******************************************************************************************************
	// �摜�̃T�C�Y���擾
	//*******************************************************************************************************
	D3DXIMAGE_INFO	INFO;
	D3DXGetImageInfoFromFile( TEXTURE_FILE, &INFO );

	//*******************************************************************************************************
	// �e�N�X�`���̓ǂݍ���
	//*******************************************************************************************************
	D3DXCreateTextureFromFileEx(	CDirectX::Get_pD3DDevice(),
									TEXTURE_FILE,
									INFO.Width,
									INFO.Height,
									0,
									0,
									D3DFMT_UNKNOWN,
									D3DPOOL_DEFAULT,
									D3DX_FILTER_LINEAR,
									D3DX_DEFAULT,
									0,
									NULL,
									NULL,
									&pTexture[NUMBER] );
}

//***********************************************************************************************************
// �e�N�X�`���u�����h
//***********************************************************************************************************
void CTexture_2D_Base::Texture_Blend(int STAGE, int NUMBER, int TYPE)
{
	if( NUMBER != NULL )
		CDirectX::Get_pD3DDevice()->SetTexture( STAGE, pTexture[NUMBER] );
	else
		CDirectX::Get_pD3DDevice()->SetTexture( STAGE, NULL );

	// ���Z�����^�C�v
	//if (TYPE == ADD)
	//{
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLORARG1, D3DTA_CURRENT);
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	//	CDirectX::Get_pD3DDevice()->SetTextureStageState(NUMBER, D3DTSS_COLOROP, D3DTOP_ADD);
	//}
}

//***********************************************************************************************************
// �I��
//***********************************************************************************************************
void CTexture_2D_Base::Finalise()
{

	if ( pTexture != NULL )
	{	// �e�N�X�`���̉��
		for ( int i = 0 ; i < nUse_Texture_Num ; i++ )
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if ( Tex_2D_Data != NULL )
	{	// �e�N�X�`�����z��̉��
		delete[] Tex_2D_Data;
		Tex_2D_Data = NULL;
	}

	if ( aVertex != NULL )
	{	// ���_���z��̉��
		delete[] aVertex;
		aVertex = NULL;
	}
}

//***********************************************************************************************************
// �X�V
//***********************************************************************************************************
void CTexture_2D_Base::Update()
{
	// ���_���X�V
	//*******************************************************************************************************
	SetVertex();

	// �e�N�X�`�����W���X�V
	//*******************************************************************************************************
	SetTexture();

	// �e�N�X�`���J���[���X�V
	//*******************************************************************************************************
	SetColor();
}

//***********************************************************************************************************
// �`��
//***********************************************************************************************************
void CTexture_2D_Base::Draw( int NUMBER, int SET_TEXTURE)
{
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̃Z�b�g
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTexture( 0, pTexture[SET_TEXTURE] );

	// �A���t�@�e�X�g�̗L����
	//***************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);


	// �|���S���̕`��
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(	D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
													NUM_POLYGON,					// �|���S����
													&aVertex[NUMBER * NUM_VERTEX],	// �z��̐擪�A�h���X
													sizeof(VERTEX_2D) );			// ���_�̃f�[�^�̑傫��

	// ���Z�����ݒ�����ɖ߂�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// �A���t�@�e�X�g�̗L�����ݒ�����ɖ߂�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

}


//***********************************************************************************************************
// ���_��񏉊���
//***********************************************************************************************************
void CTexture_2D_Base::MakeVertex()
{
	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���_���W�̐ݒ�
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx =
		aVertex[i * NUM_VERTEX + 1].vtx =
		aVertex[i * NUM_VERTEX + 2].vtx =
		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3();


		// rhw�̐ݒ�(1.0�Œ�)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].rhw =
		aVertex[i * NUM_VERTEX + 1].rhw =
		aVertex[i * NUM_VERTEX + 2].rhw =
		aVertex[i * NUM_VERTEX + 3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�(0�`255)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

		// �e�N�X�`�����W
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2( 0.0f, 0.0f );

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2( 1.0f, 0.0f );

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2( 0.0f, 1.0f );

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}
}

//�������� �e�N�X�`�����X�V�֐�( Private ) ��������

//***********************************************************************************************************
//�@���_���X�V
//***********************************************************************************************************
void CTexture_2D_Base::SetVertex()
{
	//float Rotate;

	// ���_���W�̐ݒ�
	//*******************************************************************************************************
	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y - Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x - Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );

		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)cos( Tex_2D_Data[i].fRot ) ) - ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)sin( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.x ) * Tex_2D_Data[i].fScale,
														( ( ( Tex_2D_Data[i].Obj_Pos.x + Tex_2D_Data[i].Obj_Size.x / 2 - Tex_2D_Data[i].Obj_Pos.x ) * (float)sin( Tex_2D_Data[i].fRot ) ) + ( ( Tex_2D_Data[i].Obj_Pos.y + Tex_2D_Data[i].Obj_Size.y / 2 - Tex_2D_Data[i].Obj_Pos.y ) * (float)cos( Tex_2D_Data[i].fRot ) ) + Tex_2D_Data[i].Obj_Pos.y ) * Tex_2D_Data[i].fScale,
														0.0f );
	}
}

//***********************************************************************************************************
//�@�e�N�X�`�����W���X�V
//***********************************************************************************************************
void CTexture_2D_Base::SetTexture()
{
	for (int i = 0; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x,
														Tex_2D_Data[i].Tex_Pos.y );

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x + Tex_2D_Data[i].Tex_Anim.x,
														Tex_2D_Data[i].Tex_Pos.y );

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x,
														Tex_2D_Data[i].Tex_Pos.y + Tex_2D_Data[i].Tex_Anim.y );

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(	Tex_2D_Data[i].Tex_Pos.x + Tex_2D_Data[i].Tex_Anim.x,
														Tex_2D_Data[i].Tex_Pos.y + Tex_2D_Data[i].Tex_Anim.y );
	}
}

//***********************************************************************************************************
//�@�e�N�X�`���J���[���X�V
//***********************************************************************************************************
void CTexture_2D_Base::SetColor()
{
	for ( int i = 0; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA( Tex_2D_Data[i].Red, 
														 Tex_2D_Data[i].Green, 
														 Tex_2D_Data[i].Brue, 
														 Tex_2D_Data[i].Alpha );
	}
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************