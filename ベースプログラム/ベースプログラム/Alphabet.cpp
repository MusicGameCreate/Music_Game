//***********************************************************************************************************
//
// 使用したいアルファベットのテクスチャ左上座標を返す
//
//***********************************************************************************************************
#include "Alphabet.h"
#include <string.h>

float		ONE_FONT_TEX_WIDTH	= 1.0f / 6;		// アルファベット1個分のテクスチャ幅
float		ONE_FONT_TEX_HEIGHT = 1.0f / 5;		// アルファベット1個分のテクスチャ高さ

D3DXVECTOR2 Get_Alphabet_Tex(char* Alphabet)
{
	D3DXVECTOR2 TEXTURE_POSITION	= D3DXVECTOR2();// テクスチャ座標

	// 1文字毎のピクセル数
	int nOne_Texture_X	= 400;
	int nOne_Texture_Y	= 400;

	// テクスチャの横ピクセル数・縦ピクセル数
	int nTexture_Width  = 2400;
	int nTexture_Height = 2000;

	// strcmp → 一致で「0」を返す
	if (!strcmp(Alphabet, "A"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "B"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "C"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "D"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 3) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "E"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 5) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 4) + 0.5f) / nTexture_Height);
	}

	if (!strcmp(Alphabet, "F"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "G"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "H"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "I"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 3) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "J"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 4) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 4) + 0.5f) / nTexture_Height);
	}

	if (!strcmp(Alphabet, "K"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "L"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "M"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "N"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 3) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "O"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 3) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 4) + 0.5f) / nTexture_Height);
	}

	if (!strcmp(Alphabet, "P"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "Q"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "R"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "S"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 3) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "T"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 2) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 4) + 0.5f) / nTexture_Height);
	}

	if (!strcmp(Alphabet, "U"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "V"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "W"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "X"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 3) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "Y"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	((float)(nOne_Texture_X * 1) + 0.5f) / nTexture_Width,
										((float)(nOne_Texture_Y * 4) + 0.5f) / nTexture_Height);
	}

	if (!strcmp(Alphabet, "Z"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	( (float)(nOne_Texture_X * 0) + 0.5f) / nTexture_Width,
										( (float)(nOne_Texture_Y * 0) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "!"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	( (float)(nOne_Texture_X * 0) + 0.5f) / nTexture_Width,
										( (float)(nOne_Texture_Y * 1) + 0.5f) / nTexture_Height);
	}
	if (!strcmp(Alphabet, "?"))
	{
		TEXTURE_POSITION = D3DXVECTOR2(	( (float)(nOne_Texture_X * 0) + 0.5f) / nTexture_Width,
										( (float)(nOne_Texture_Y * 2) + 0.5f) / nTexture_Height);
	}


	return TEXTURE_POSITION;
}

float Get_Alphabet_Texture_Width()
{
	return ONE_FONT_TEX_WIDTH;
}

float Get_Alphabet_Texture_Height()
{
	return ONE_FONT_TEX_HEIGHT;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************