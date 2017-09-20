//*************************************************************************
//
// ���U���g��ʁE�{�^���E�N���b�N�E�z�C�[���m�[�c���������o�[
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "Result_BCWGauge.h"
#include "DirectX_Library.h"

// 1�� = 2.83f

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
Result_BCWGauge::Result_BCWGauge(void)
{	
	{// �v���C�����Ȃ̊e�m�[�c�̑������擾
		// �{�^���m�[�c�������i�[
		nMax_ButtonNort = 0;

		// �N���b�N�m�[�c�������i�[
		nMax_ClickNort = 0;

		// �z�C�[���m�[�c�������i�[
		nMax_WheelNort = 0;
	}


	// �{�^���E�N���b�N�E�z�C�[���m�[�c�̐�������(��)���i�[
	//*********************************************************************
	nButtonGauge	= 50;
	nClickGauge		= 25;
	nWheelGauge		= 25;



	// �Ƃ肠����NULL��
	//*********************************************************************
	pTexture		= NULL;	// �e�N�X�`���摜���
	aVertex			= NULL; // ���_���z��


	// �Q�[�W��3����
	//*********************************************************************
	nObject_Num = 3;

	// �g�p�e�N�X�`�����T�C�Y���m��
	//*********************************************************************
	pTexture = new LPDIRECT3DTEXTURE9[nObject_Num];

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	// ���_�� * ���� = �K�v�ȃI�u�W�F�N�g���̒��_��(�O����4���g�p)
	//*********************************************************************
	aVertex = new VERTEX_2D[NUM_VERTEX * nObject_Num];

	// �e���񏉊���
	//*********************************************************************
	for (int i = 0; i < nObject_Num; i++)
	{
		// ���_���W
		//*****************************************************************
		aVertex[i * NUM_VERTEX + 0].vtx = 
		aVertex[i * NUM_VERTEX + 1].vtx = D3DXVECTOR3(788.0f, 556.0f + i * 26.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].vtx = 
		aVertex[i * NUM_VERTEX + 3].vtx = D3DXVECTOR3(788.0f, 576.0f + i * 26.0f, 0.0f);

		// rhw�̐ݒ�(1.0�Œ�)
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].rhw =
		aVertex[i * NUM_VERTEX + 1].rhw =
		aVertex[i * NUM_VERTEX + 2].rhw =
		aVertex[i * NUM_VERTEX + 3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�(0�`255)
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].col =
		aVertex[i * NUM_VERTEX + 1].col =
		aVertex[i * NUM_VERTEX + 2].col =
		aVertex[i * NUM_VERTEX + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W
		//******************************************************************
		aVertex[i * NUM_VERTEX + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		aVertex[i * NUM_VERTEX + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		aVertex[i * NUM_VERTEX + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// �e�N�X�`���̍쐬
	//*********************************************************************
	CREATE_TEXTURE( pTexture[0], 0xffff00ff );
	CREATE_TEXTURE( pTexture[1], 0xffffff00 );
	CREATE_TEXTURE( pTexture[2], 0xff00ff70 );

	float fAdd_Length = 0.0f;

	{// �{�^���Q�[�W�̒����������ɉ����ĕύX
		fAdd_Length = (float)(nButtonGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[0 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[0 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}


	{// �N���b�N�Q�[�W�̒����������ɉ����ĕύX
		fAdd_Length = (float)(nClickGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[1 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[1 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}


	{// �z�C�[���Q�[�W�̒����������ɉ����ĕύX
		fAdd_Length = (float)(nWheelGauge * 2.83f);

		if (fAdd_Length > 283.0f)
			fAdd_Length = 283.0f;

		aVertex[2 * NUM_VERTEX + 1].vtx.x += fAdd_Length;
		aVertex[2 * NUM_VERTEX + 3].vtx.x += fAdd_Length;
	}

}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
Result_BCWGauge::~Result_BCWGauge(void)
{
	if (pTexture != NULL)
	{	// �e�N�X�`���̉��
		for (int i = 0; i < nObject_Num; i++)
		{
			pTexture[i]->Release();
		}

		delete[] pTexture;
		pTexture = NULL;
	}

	if (aVertex != NULL)
	{	// ���_���z��̉��
		delete[] aVertex;
		aVertex = NULL;
	}
}

//*************************************************************************
// �X�V����
//*************************************************************************
void Result_BCWGauge::Update(void)
{

}

//*************************************************************************
// �`�揈��
//*************************************************************************
void Result_BCWGauge::Draw(void)
{
	CDirectX::Get_pD3DDevice()->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < nObject_Num; i++)
	{
		// �e�N�X�`���̃Z�b�g
		//*****************************************************************
		CDirectX::Get_pD3DDevice()->SetTexture(0, pTexture[i]);

		// �|���S���̕`��
		//*****************************************************************
		CDirectX::Get_pD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
													NUM_POLYGON,				// �|���S����
													&aVertex[i * NUM_VERTEX],	// �z��̐擪�A�h���X
													sizeof(VERTEX_2D));			// ���_�̃f�[�^�̑傫��
	}
}

//*************************************************************************
// EOF
//*************************************************************************
