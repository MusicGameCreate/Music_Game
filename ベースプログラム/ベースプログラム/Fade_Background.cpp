// �t�F�[�h��ʕ`��I�u�W�F�N�g(2D�`���{�N���X���p��)( CTexture_2D_Base )
// �\����ς��邩���Ȃ̂ŗv�ύX

#include "Fade_Background.h"

//******************************
// �R���X�g���N�^
//******************************
Fade_Background::Fade_Background()				
{
	// �I�u�W�F�N�g�����g�p���邩�H(�Œ� 1�`)
	nObject_Num		= 1;

	// ���l�𑝌������邽�߂Ɏg�p(�v�ύX)
	nAddAlpha	= 5;

	//for( int i = 0 ; i < nObject_Num ; i ++ )
	//{
	//	// ���W(�摜�̒��S�����_)
	//	Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	SCREEN_WIDTH / 2,
	//											SCREEN_HEIGHT / 2,
	//											0.0f );

	//	// �I�u�W�F�N�g�̃T�C�Y(X,Y)
	//	Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( SCREEN_WIDTH, SCREEN_HEIGHT );

	//	// �e�N�X�`�����W(0.0f�`1.0f)
	//	Tex_2D_Data[i].Tex_Pos	= D3DXVECTOR2( 0.0f, 0.0f );
	//
	//	// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
	//	Tex_2D_Data[i].Tex_Anim	= D3DXVECTOR2( 1.0f, 1.0f );

	//	// �摜�̃A���t�@
	//	Tex_2D_Data[i].Alpha	= 0;

	//	// �摜�̊g�嗦(0.0f�`)
	//	Tex_2D_Data[i].fScale	= 1.0f;

	//	// �摜�̉�]�p�x(0.0f�`)
	//	Tex_2D_Data[i].fRot		= 0.0f;
	//}
	
	nFrameCnt	= 0;
	bFrame		= false;

	CTexture_2D_Base::Init();
	CTexture_2D_Base::Load_Texture( "../DATA/TEXTURE/�t�F�[�h��ʗp/Fade.png", 0 );
}

//******************************
// �f�X�g���N�^
//******************************
Fade_Background::~Fade_Background()
{
	CTexture_2D_Base::Finalise();
}

//******************************
// �X�V
//******************************
void Fade_Background::Update()
{

}

//******************************
// �`��
//******************************
void Fade_Background::Draw()
{
	CTexture_2D_Base::Draw(0,0);
}