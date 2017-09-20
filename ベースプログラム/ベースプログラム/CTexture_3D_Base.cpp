//***********************************************************************************************************
//
// 3D���ł̉摜�`���{�N���X
//
//***********************************************************************************************************


//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CTexture_3D_Base.h"


//***********************************************************************************************************
// �R���X�g���N�^
//***********************************************************************************************************
CTexture_3D_Base::CTexture_3D_Base()
{
	// �Ƃ肠����NULL��
	//*******************************************************************************************************
	pTexture	= NULL;		// �e�N�X�`�����̏�����
	Tex_3D_Data = NULL;		// �e�N�X�`�����z��
	aVertex		= NULL;		// ���_���z��

	// �I�u�W�F�N�g���͍ŏ���1�ɐݒ�
	//*******************************************************************************************************
	nObject_Num	= 1;

	// �e�N�X�`�����͍ŏ���1�ɐݒ�
	//*******************************************************************************************************
	nUse_Texture_Num = 1;

	// �e��ݒ�͍ŏ��͖��K�p
	//*******************************************************************************************************
	bBillboard	= false;	// �r���{�[�h�w��
	bAlphaTest	= false;	// ���e�X�g�K�p�w��
}

//***********************************************************************************************************
// �f�X�g���N�^
//***********************************************************************************************************
CTexture_3D_Base::~CTexture_3D_Base()
{

}

//***********************************************************************************************************
// ������
//***********************************************************************************************************
void CTexture_3D_Base::Init()
{
	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	// ���_�� * ���� = �K�v�ȃI�u�W�F�N�g���̒��_��(�O����4���g�p)
	//*******************************************************************************************************
	aVertex = new VERTEX_3D[NUM_VERTEX * nObject_Num];

	// �g�p�e�N�X�`�����T�C�Y���m��
	//*******************************************************************************************************
	pTexture = new LPDIRECT3DTEXTURE9[nUse_Texture_Num];

	// ���_��񏉊���
	//*******************************************************************************************************
	MakeVertex();
}

//***********************************************************************************************************
// �e�N�X�`���ǂݍ���
//***********************************************************************************************************
void CTexture_3D_Base::Load_Texture(char* TEXTURE_FILE, int NUMBER)
{
	// �e�N�X�`���̓ǂݍ���
	//*******************************************************************************************************
	D3DXCreateTextureFromFile(	CDirectX::Get_pD3DDevice(),	// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILE,				// �t�@�C���̖��O
								&pTexture[NUMBER]);			// �ǂݍ��ރ������[

}

//***********************************************************************************************************
// �I��
//***********************************************************************************************************
void CTexture_3D_Base::Finalise()
{
	if (pTexture != NULL)
	{	// �e�N�X�`���̉��
		for (int i = 0; i < nUse_Texture_Num; i++)
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if( Tex_3D_Data != NULL )
	{	// �e�N�X�`�����z��̉��
		delete[] Tex_3D_Data;
		Tex_3D_Data = NULL;
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
void CTexture_3D_Base::Update()
{
	// ���_���X�V
	//*******************************************************************************************************
	SetVertex();

	// �e�N�X�`�����W�X�V
	//*******************************************************************************************************
	SetTexture();

	// �J���[���X�V
	//*******************************************************************************************************
	SetColor();
}

//***********************************************************************************************************
// �`��
//***********************************************************************************************************
void CTexture_3D_Base::Draw(int NUMBER, int SET_TEXTURE)
{
	D3DCAPS9 Caps;

	// ���C�e�B���O�𖳌��ɂ���
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���_�t�H�[�}�b�g�̐ݒ�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTexture(0, pTexture[SET_TEXTURE]);

	// �f�o�C�X�@�\���擾
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->GetDeviceCaps(&Caps);

	if ( bAlphaTest && Caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
	{
		// �A���t�@�e�X�g�̗L����
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

		// �s�����ɂ���l�̐ݒ�
		//***************************************************************************************************
		CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHAREF, 0x66);
	}


	// ���[���h�}�g���b�N�X�̐ݒ�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetTransform( D3DTS_WORLD, &Tex_3D_Data[NUMBER].mtxWorld );


	// �|���S���̕`��
	//*******************************************************************************************************
		CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(	D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
														NUM_POLYGON,					// �|���S����
														&aVertex[NUMBER * NUM_VERTEX],	// �z��̐擪�A�h���X
														sizeof(VERTEX_3D));				// ���_�̃f�[�^�̑傫��


	// ���Z�����ݒ�����ɖ߂�
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// ���C�e�B���O��L���ɂ���
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	// �A���t�@�e�X�g�̖�����
	//*******************************************************************************************************
	CDirectX::Get_pD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//***********************************************************************************************************
// ���_��񏉊���
//***********************************************************************************************************
void CTexture_3D_Base::MakeVertex()
{
	for ( int i = 0 ; i < nObject_Num ; i++ )
	{
		// ���_���W�̐ݒ�
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx		=
		aVertex[i * NUM_VERTEX + 1].vtx		=
		aVertex[i * NUM_VERTEX + 2].vtx		=
		aVertex[i * NUM_VERTEX + 3].vtx		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		if ( bBillboard == true )
		{
			// �@���̐ݒ�( 0.0f, 0.0f, -1.0f �Œ�)
			//***********************************************************************************************
			aVertex[i * NUM_VERTEX + 0].normal =
			aVertex[i * NUM_VERTEX + 1].normal =
			aVertex[i * NUM_VERTEX + 2].normal =
			aVertex[i * NUM_VERTEX + 3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		}
		else
		{
			// �@���̐ݒ�( 0.0f, 1.0f, 0.0f �Œ� )
			//***********************************************************************************************
			aVertex[i * NUM_VERTEX + 0].normal =
			aVertex[i * NUM_VERTEX + 1].normal =
			aVertex[i * NUM_VERTEX + 2].normal =
			aVertex[i * NUM_VERTEX + 3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		

		// ���_�J���[�̐ݒ�(0�`255)
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].diffuse =
		aVertex[i * NUM_VERTEX + 1].diffuse =
		aVertex[i * NUM_VERTEX + 2].diffuse =
		aVertex[i * NUM_VERTEX + 3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W
		//***************************************************************************************************
		aVertex[i * NUM_VERTEX + 0].tex		= D3DXVECTOR2(0.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 1].tex		= D3DXVECTOR2(1.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].tex		= D3DXVECTOR2(0.0f, 1.0f);
		aVertex[i * NUM_VERTEX + 3].tex		= D3DXVECTOR2(1.0f, 1.0f);
	}

}

//***********************************************************************************************************
// ���_���W�X�V
//***********************************************************************************************************
void CTexture_3D_Base::SetVertex()
{
	// �r���[�}�g���b�N�X���擾
	//*******************************************************************************************************
	mtxView = CCamera::GetMtxView();

	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		if ( bBillboard == true )
		{
			aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2,
															Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2,
															Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2,
															-Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);

			aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2,
															-Tex_3D_Data[i].Obj_Size.y / 2,
															0.0f);
		}
		else
		{
			//aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												Tex_3D_Data[i].Obj_Size.y / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												Tex_3D_Data[i].Obj_Size.y / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(	-Tex_3D_Data[i].Obj_Size.x / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												-Tex_3D_Data[i].Obj_Size.y / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			//aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(	Tex_3D_Data[i].Obj_Size.x / 2 * cosf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ),
			//												0.0f,
			//												-Tex_3D_Data[i].Obj_Size.y / 2 * sinf( Tex_3D_Data[i].Obj_Rot.y + ANGLE_45DEG ) );

			aVertex[i * NUM_VERTEX + 0].vtx = D3DXVECTOR3(-Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 2].vtx = D3DXVECTOR3(-Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				-Tex_3D_Data[i].Obj_Size.y / 2);

			aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(Tex_3D_Data[i].Obj_Size.x / 2,
				0.0f,
				-Tex_3D_Data[i].Obj_Size.y / 2);
		}

		// ���[���h�}�g���b�N�X�̏�����
		//***************************************************************************************************
		D3DXMatrixIdentity( &Tex_3D_Data[i].mtxWorld );

		if ( bBillboard == true )
		{
			// �|���S���𐳖ʂɌ�����
#if 1
			// �t�s������߂�
			//***********************************************************************************************
			D3DXMatrixInverse( &Tex_3D_Data[i].mtxWorld, NULL, &mtxView );

			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
			//���s�ړ��������Ȃ���

			// �]�u�s������߂�
			//***********************************************************************************************
			Tex_3D_Data[i].mtxWorld._11 = mtxView._11;
			Tex_3D_Data[i].mtxWorld._12 = mtxView._21;
			Tex_3D_Data[i].mtxWorld._13 = mtxView._31;
			Tex_3D_Data[i].mtxWorld._14 = 0.0f;
			Tex_3D_Data[i].mtxWorld._21 = mtxView._12;
			Tex_3D_Data[i].mtxWorld._22 = mtxView._22;
			Tex_3D_Data[i].mtxWorld._23 = mtxView._32;
			Tex_3D_Data[i].mtxWorld._24 = 0.0f;
			Tex_3D_Data[i].mtxWorld._31 = mtxView._13;
			Tex_3D_Data[i].mtxWorld._32 = mtxView._23;
			Tex_3D_Data[i].mtxWorld._33 = mtxView._33;
			Tex_3D_Data[i].mtxWorld._34 = 0.0f;
			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
			Tex_3D_Data[i].mtxWorld._44 = 1.0f;

#else
			// �t�s������߂�
			D3DXMatrixInverse(&Tex_3D_Data[i].mtxWorld,
				NULL,
				&mtxView);

			Tex_3D_Data[i].mtxWorld._41 = 0.0f;
			Tex_3D_Data[i].mtxWorld._42 = 0.0f;
			Tex_3D_Data[i].mtxWorld._43 = 0.0f;
#endif
		}

		// �X�P�[���𔽉f
		//***************************************************************************************************
		D3DXMatrixScaling( &Tex_3D_Data[i].mtxScale, Tex_3D_Data[i].Obj_Scale.x, Tex_3D_Data[i].Obj_Scale.y, Tex_3D_Data[i].Obj_Scale.z);
		D3DXMatrixMultiply(	&Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxScale);


		// ��]�p�x�𔽉f
		//***************************************************************************************************
		D3DXMatrixRotationYawPitchRoll(&Tex_3D_Data[i].mtxRot, Tex_3D_Data[i].Obj_Rot.y, Tex_3D_Data[i].Obj_Rot.x, Tex_3D_Data[i].Obj_Rot.z);
		D3DXMatrixMultiply(&Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxRot);

		// �ړ��𔽉f
		//***************************************************************************************************
		D3DXMatrixTranslation(	&Tex_3D_Data[i].mtxTranslate, Tex_3D_Data[i].Obj_Pos.x, Tex_3D_Data[i].Obj_Pos.y, Tex_3D_Data[i].Obj_Pos.z);
		D3DXMatrixMultiply( &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxWorld, &Tex_3D_Data[i].mtxTranslate );
	}
}

//***********************************************************************************************************
// �e�N�X�`�����W�X�V
//***********************************************************************************************************
void CTexture_3D_Base::SetTexture()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x,
														Tex_3D_Data[i].Tex_Pos.y);

		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x + Tex_3D_Data[i].Tex_Anim.x,
														Tex_3D_Data[i].Tex_Pos.y);

		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x,
														Tex_3D_Data[i].Tex_Pos.y + Tex_3D_Data[i].Tex_Anim.y);

		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(	Tex_3D_Data[i].Tex_Pos.x + Tex_3D_Data[i].Tex_Anim.x,
														Tex_3D_Data[i].Tex_Pos.y + Tex_3D_Data[i].Tex_Anim.y);
	}
}

//***********************************************************************************************************
// �e�N�X�`���J���[���X�V
//***********************************************************************************************************
void CTexture_3D_Base::SetColor()
{
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		aVertex[i * NUM_VERTEX + 0].diffuse =
		aVertex[i * NUM_VERTEX + 1].diffuse =
		aVertex[i * NUM_VERTEX + 2].diffuse =
		aVertex[i * NUM_VERTEX + 3].diffuse = D3DCOLOR_RGBA( Tex_3D_Data[i].Red, 
															 Tex_3D_Data[i].Green, 
															 Tex_3D_Data[i].Brue, 
															 Tex_3D_Data[i].Alpha );
	}
}

void CTexture_3D_Base::QuaternionRotate()
{
	q.x = q.y = q.z = NAxis.x = NAxis.y = 0.0f;
	q.w = NAxis.z = 1.0f;

	//�������Ȃ��s������
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&TurnMat);

	// �摜�̍��[�����_�ɂȂ�悤�ɕ��s�ړ�
	D3DXMatrixTranslation(&mat, Tex_3D_Data[0].Obj_Size.x / 2, 0.0f, 0.0f);

}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************