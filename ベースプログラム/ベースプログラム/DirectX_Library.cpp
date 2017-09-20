//*************************************************************************
//
// 各種便利関数諸々
//
//*************************************************************************
#include "DirectX_Library.h"

void LOAD_TEXTURE(LPDIRECT3DTEXTURE9& TEXTURE, char* TEXTURE_FILE)
{



}

void CREATE_TEXTURE(LPDIRECT3DTEXTURE9& TEXTURE, DWORD COLOR)
{
	int Texture_W;
	int Texture_H;

	Texture_W = Texture_H = 100;

	//***********************************************************************************
	// テクスチャ作成↓
	//***********************************************************************************
	LPDIRECT3DDEVICE9 pDevice = CDirectX::Get_pD3DDevice();
	pDevice->CreateTexture(	Texture_W,			// テクスチャ幅
												Texture_H,			// テクスチャ高さ
												1,					//
												D3DUSAGE_DYNAMIC,	//
												D3DFMT_A8R8G8B8,	//
												D3DPOOL_DEFAULT,	//
												&TEXTURE,			// 作成するテクスチャ番地
												NULL);				//


	//***********************************************************************************
	// テクスチャにテクスチャ情報を書き込み↓
	//***********************************************************************************
	D3DLOCKED_RECT lockedRect;

	//// ロック
	////*********************************************************************
	TEXTURE->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD);

	// テクスチャ初期化(透明にする)
	memset(lockedRect.pBits, 0, lockedRect.Pitch * Texture_H);

	// テクスチャメモリへのポインタ
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;

	for (int y = 0; y < Texture_H; y++)
	{
		for (int x = 0; x < Texture_W; x++)
		{
			memcpy((BYTE*)lockedRect.pBits + lockedRect.Pitch*y + 4 * x, &COLOR, sizeof(DWORD));
		}
	}

	//// アンロック
	////*********************************************************************
	TEXTURE->UnlockRect(0);
}

//*************************************************************************
// EOF
//*************************************************************************