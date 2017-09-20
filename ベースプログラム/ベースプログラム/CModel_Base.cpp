//***********************************************************************************************************
//
// ���f���`���{�N���X
//
//***********************************************************************************************************

//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CModel_Base.h"

//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
CModel_Base::CModel_Base()
{
	// �Ƃ肠����NULL��
	//*******************************************************************************************************
	pD3DXMesh		= NULL;
	pD3DXBuffMat	= NULL;
	pD3DXMat		= NULL;
	pTexture		= NULL;
	pMaterial		= NULL;
	Model_Data		= NULL;

	// �}�e���A�����͍ŏ���0��
	//*******************************************************************************************************
	nNumMat = 0;
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
CModel_Base::~CModel_Base()
{

}

//***********************************************************************************************************
// ����������
//***********************************************************************************************************
void CModel_Base::Init( char* X_FILE )
{

	// X�t�@�C���ǂݍ��݁A�K�v�ȏ����擾
	//*******************************************************************************************************
	D3DXLoadMeshFromX(	X_FILE,						// �g�p����X�t�@�C����
						D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
						CDirectX::Get_pD3DDevice(),	// �f�o�C�X�̃|�C���^
						NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
						&pD3DXBuffMat,				// �}�e���A���f�[�^���܂ރo�b�t�@
						NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
						&nNumMat,					// D3DXMATERIAL�\���̂̐�
						&pD3DXMesh );				// ���b�V���̃|�C���^
					
	// �e�N�X�`���ǂݍ���
	//*******************************************************************************************************
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXBuffMat->GetBufferPointer();

	pMaterial	= new D3DMATERIAL9[nNumMat];
	pTexture	= new LPDIRECT3DTEXTURE9[nNumMat];

	for ( DWORD i = 0; i < nNumMat; i ++ )
	{
		pMaterial[i]		= pD3DMaterials[i].MatD3D;
		pMaterial[i].Ambient= pMaterial[i].Diffuse;
		pTexture[i]			= NULL;

		if ( pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0] )
		{
			// �e�N�X�`���t�@�C����ǂݍ���
			//***********************************************************************************************
			D3DXCreateTextureFromFileA(	CDirectX::Get_pD3DDevice(),
										pD3DMaterials[i].pTextureFilename,
										&pTexture[i]);
		}
	}
}

//***********************************************************************************************************
// �I������
//***********************************************************************************************************
void CModel_Base::Finalise()
{
	if ( pD3DXMesh != NULL )
	{	// ���b�V�����
		pD3DXMesh->Release();
		pD3DXMesh = NULL;
	}
	if ( pD3DXBuffMat != NULL )
	{	// �}�e���A���J��
		pD3DXBuffMat->Release();
		pD3DXBuffMat = NULL;
	}
	
	//if ( pTexture != NULL )
	//{	// �e�N�X�`�����
	//	for ( DWORD i = 0; i < nNumMat; i++ )
	//	{
	//		pTexture[i]->Release();
	//	}

	//	delete[] pTexture;
	//	pTexture = NULL;
	//}	

	if ( pMaterial != NULL )
	{
		delete[] pMaterial;
		pMaterial = NULL;
	}

	if ( Model_Data != NULL )
	{	// ���f�����\���̉��
		delete[] Model_Data;
		Model_Data = NULL;
	}
}

//***********************************************************************************************************
// �X�V����
//***********************************************************************************************************
void CModel_Base::Update()
{
	for (int i = 0; i < nObject_Num; i++)
	{
		// ���[���h�}�g���N�X�̏�����
		//***************************************************************************************************
		D3DXMatrixIdentity(&Model_Data[i].World_Matrix);

		// �g�嗦�����f���ɔ��f
		//***************************************************************************************************
		D3DXMatrixScaling( &Model_Data[i].Scale_Matrix, Model_Data[i].Model_Scale.x, Model_Data[i].Model_Scale.y, Model_Data[i].Model_Scale.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Scale_Matrix);


		// ��]�p�x�����f���ɔ��f
		//***************************************************************************************************
		D3DXMatrixRotationYawPitchRoll(	&Model_Data[i].Rotate_Matrix, Model_Data[i].Model_Rot.y, Model_Data[i].Model_Rot.x, Model_Data[i].Model_Rot.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Rotate_Matrix);			


		// ���W�����f���ɔ��f
		//***************************************************************************************************
		D3DXMatrixTranslation( &Model_Data[i].Trans_Matrix, Model_Data[i].Model_Pos.x, Model_Data[i].Model_Pos.y, Model_Data[i].Model_Pos.z);
		D3DXMatrixMultiply(	&Model_Data[i].World_Matrix, &Model_Data[i].World_Matrix, &Model_Data[i].Trans_Matrix );

	}
}

//***********************************************************************************************************
// �`�揈��
//***********************************************************************************************************
void CModel_Base::Draw()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���[���h�}�g���N�X�̐ݒ�
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_WORLD, &Model_Data[i].World_Matrix );

		for ( int i = 0; i < (int)nNumMat; i ++ )
		{
			// �}�e���A���̐ݒ�
			//***********************************************************************************************
			CDirectX::Get_pD3DDevice()->SetMaterial( &pMaterial[i] );

			// �e�N�X�`���̐ݒ�
			//***********************************************************************************************
			if ( bUse_Texture == true )
				CDirectX::Get_pD3DDevice()->SetTexture( 0, pTexture[i] );
			if ( bUse_Texture == false )
				CDirectX::Get_pD3DDevice()->SetTexture( 0, NULL );

			// �`��
			//***********************************************************************************************
			pD3DXMesh->DrawSubset(i);
		}
	}

	// ���Z�����ݒ�����ɖ߂�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************