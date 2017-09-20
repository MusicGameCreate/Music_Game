//*************************************************************************
//
// �t�H���g�����N���X
//
//*************************************************************************
#pragma once

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "CDirectX.h"

//*************************************************************************
// �\���̒�`
//*************************************************************************
typedef struct
{
	D3DXVECTOR2	Obj_Pos;	// ���W(�摜�̒��S�����_)
	D3DXVECTOR2	Obj_Size;	// �I�u�W�F�N�g�̃T�C�Y(X,Y)
	int			Red;		// �摜��R�l
	int			Green;		// �摜��G�l
	int			Brue;		// �摜��B�l
	int			Alpha;		// �摜�̃A���t�@�l
}FONT_DATA;

//*************************************************************************
// �N���X��`
//*************************************************************************
class CFont_Base
{
	LPDIRECT3DTEXTURE9*	pTexture;			// �e�N�X�`���f�[�^�ւ̃|�C���^
	VERTEX_2D*			aVertex;			// ���_���
	HFONT				hFONT;				// 
	

protected:
	FONT_DATA*			Font_Data;			// �e�N�X�`�����܂Ƃߍ\����
	int					nObject_Num;		// �I�u�W�F�N�g�����������邩�H(��{��1�����Ă����Ă�������)
	int					nUse_Texture_Num;	// �e�N�X�`���͉��g�p���邩�H(��{��1�����Ă����Ă�������)
	D3DXVECTOR2			Standard_Pos;		// �t�H���g�`��̊�_

private:
	void				MakeVertex();		// ���_��񏉊���
	void				SetVertex(); 		// ���_���W�X�V
	void				SetColor();	 		// �e�N�X�`���J���[���X�V
	void				SetTexture();		// �e�N�X�`�����W�X�V

protected:
	void				Delete_Texture(int LENGTH);	// �e�N�X�`���폜

public:
	virtual void Init(int FONT_SIZE);								// ������
	virtual void Create_Texture(wchar_t* FONT_CHAR,int nLength);	// �����e�N�X�`���쐬
	virtual void Finalise(int LENGTH);								// �I��
	virtual void Update(void);										// �X�V
	virtual void Draw(int NUMBER, int SET_TEXTURE);					// �`��

	CFont_Base(void);											// �R���X�g���N�^
	virtual ~CFont_Base(void);										// �f�X�g���N�^
};

//*************************************************************************
// EOF
//*************************************************************************