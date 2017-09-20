//***********************************************************************************************************
//
// �g�p�����������̃e�N�X�`��������W��Ԃ�
//
//***********************************************************************************************************
#include "Number.h"
#include <string.h>

float		ONE_NUMBER_TEX_WIDTH	= (float)( 1.0f / 10 );	// ����1���̃e�N�X�`����
float		ONE_NUMBER_TEX_HEIGHT	= (float)( 1.0f /  1 );	// ����1���̃e�N�X�`������

//***********************************************************************************************************
// �v���g�^�C�v�錾
//***********************************************************************************************************
D3DXVECTOR2 Get_Number_Tex(int Number)
{
	D3DXVECTOR2 TEXTURE_POSITION = D3DXVECTOR2();// �e�N�X�`�����W

	// 1�������̃s�N�Z����
	int nOne_Texture_X	= 400;
	int nOne_Texture_Y	= 400;

	int nTexture_Width  = 4000;
	int nTexture_Height =  400;

	switch ( Number )
	{
	case 0:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 0) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 1:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 2:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 3:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 4:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 5:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 6:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 6) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 7:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 7) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 8:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 8) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	case 9:
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 9) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
		break;

	default:
		break;
	}

	return TEXTURE_POSITION;
}

float Get_Number_Texture_Width()
{
	return ONE_NUMBER_TEX_WIDTH;
}

float Get_Number_Texture_Height()
{
	return ONE_NUMBER_TEX_HEIGHT;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************