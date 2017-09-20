//*************************************************************************
//
// �e��֗��֐����X
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
	// �e�N�X�`���쐬��
	//***********************************************************************************
	LPDIRECT3DDEVICE9 pDevice = CDirectX::Get_pD3DDevice();
	pDevice->CreateTexture(	Texture_W,			// �e�N�X�`����
												Texture_H,			// �e�N�X�`������
												1,					//
												D3DUSAGE_DYNAMIC,	//
												D3DFMT_A8R8G8B8,	//
												D3DPOOL_DEFAULT,	//
												&TEXTURE,			// �쐬����e�N�X�`���Ԓn
												NULL);				//


	//***********************************************************************************
	// �e�N�X�`���Ƀe�N�X�`�������������݁�
	//***********************************************************************************
	D3DLOCKED_RECT lockedRect;

	//// ���b�N
	////*********************************************************************
	TEXTURE->LockRect(0, &lockedRect, NULL, D3DLOCK_DISCARD);

	// �e�N�X�`��������(�����ɂ���)
	memset(lockedRect.pBits, 0, lockedRect.Pitch * Texture_H);

	// �e�N�X�`���������ւ̃|�C���^
	DWORD *pTexBuf = (DWORD*)lockedRect.pBits;

	for (int y = 0; y < Texture_H; y++)
	{
		for (int x = 0; x < Texture_W; x++)
		{
			memcpy((BYTE*)lockedRect.pBits + lockedRect.Pitch*y + 4 * x, &COLOR, sizeof(DWORD));
		}
	}

	//// �A�����b�N
	////*********************************************************************
	TEXTURE->UnlockRect(0);
}

//*************************************************************************
// EOF
//*************************************************************************