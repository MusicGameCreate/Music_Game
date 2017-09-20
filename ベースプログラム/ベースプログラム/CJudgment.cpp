//***********************************************************************************************************
//
//		CJudgment.cpp
//		�����蔻�菈��
//
//***********************************************************************************************************


//***********************************************************************************************************
// �C���N���[�h��
//***********************************************************************************************************
#include "CJudgment.h"

//***********************************************************************************************************
// bool BOX2D
// �����F���ʏ�̂�2�̋�`�̓����蔻���Ԃ�
// �����F	D3DXVECTOR2 ALeftUp		��`A���㒸�_���W
//			D3DXVECTOR2 ARightDown	��`A�E�����_���W
//			D3DXVECTOR2 BLeftUp		��`B���㒸�_���W
//			D3DXVECTOR2 BRightDown	��`B�E�����_���W
// �߂�l�Ftrue or false
//***********************************************************************************************************
bool BOX2D(D3DXVECTOR2 ALeftUp, D3DXVECTOR2 ARightDown, D3DXVECTOR2 BLeftUp, D3DXVECTOR2 BRightDown)
{
	if	
	(
		ALeftUp.x <= BRightDown.x
		&&
		ARightDown.x >= BLeftUp.x
		&&
		ALeftUp.y <= BRightDown.y
		&&
		ARightDown.y >= BLeftUp.y
	)
		return true;
	else
		return false;
}

//***********************************************************************************************************
// bool BOX3D
// �����F�{�b�N�X3D�̓����蔻���Ԃ�(������)
// �����F�Ȃ��@�߂�l�Ftrue or false
//***********************************************************************************************************
bool BOX3D()
{
	return false;
}

//***********************************************************************************************************
// bool MouseTex2D
// �����F�}�E�X���W�ƃe�N�X�`�����W�̓����蔻���Ԃ�
// �����FMousePos, TexPos, TexSize�@�߂�l�Ftrue or false
//***********************************************************************************************************
bool MouseTex2D(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize, bool Portrait)
{
	if (!Portrait)
	{
		TexSize.x = TexSize.x / 2;
		TexSize.y = TexSize.y / 2;
		if (MousePos.x >= (TexPos.x - TexSize.x) && MousePos.x <= (TexPos.x + TexSize.x) &&
			MousePos.y >= (TexPos.y - TexSize.y) && MousePos.y <= (TexPos.y + TexSize.y))
			return true;
	}
	else
	{
		float TexTemp;
		TexTemp = TexSize.x;
		TexSize.x = TexSize.y;
		TexSize.y = TexTemp;
		TexSize.x = TexSize.x / 2;
		TexSize.y = TexSize.y / 2;
		if (MousePos.x >= (TexPos.x - TexSize.x) && MousePos.x <= (TexPos.x + TexSize.x) &&
			MousePos.y >= (TexPos.y - TexSize.y) && MousePos.y <= (TexPos.y + TexSize.y))
			return true;

	}

	return false;
}

//***********************************************************************************************************
// bool CJudgment::MouseTex2DCircle
// �����F�}�E�X���W�ƃe�N�X�`�����W�̓����蔻���Ԃ�(�~ver)
// �����FMousePos, TexPos, TexSize�@�߂�l�Ftrue or false
//***********************************************************************************************************
bool MouseTex2DCircle(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize)
{
	// �~�摜�̔��a
	TexSize.x = TexSize.x / 2;

	// �}�E�X���W�ƃe�N�X�`���̓����蔻��v�Z
	if( ((MousePos.x - TexPos.x) * (MousePos.x - TexPos.x) + 
		 (MousePos.y - TexPos.y) * (MousePos.y - TexPos.y)) <= (TexSize.x * TexSize.x) )
		return true;

	return false;
}

//***********************************************************************************************************
// bool CJudgment::CIRCLE
// �����F���ʏ�̓�̉~�̓����蔻��
// �����F	D3DXVECTOR2 APos	�~A���S���W
//			float fARudius		�~A���a
//			D3DXVECTOR2 BPos	�~B���S���W
//			float fBRudius		�~B���a
// �߂�l�Ftrue or false
//***********************************************************************************************************
bool CIRCLE(D3DXVECTOR2 APos, float fARudius, D3DXVECTOR2 BPos, float fBRudius)
{
	if	(
			sqrtf( ( APos.x - BPos.x ) * ( APos.x - BPos.x ) + ( APos.y - BPos.y ) * ( APos.y - BPos.y ) )
			<
			fARudius + fBRudius
		)
		return true;
	else
		return false;
}

//***********************************************************************************************************
// bool CJudgment::WorldModel2D
// �����F���[���h���W�ƃ��f�����W�̓����蔻���Ԃ�
// �����FWorldPos, ModelPos, ModelSize�@�߂�l�Ftrue or false
//***********************************************************************************************************
bool WorldModel2D(D3DXVECTOR3 WorldPos, D3DXVECTOR3 ModelPos, D3DXVECTOR3 ModelSize)
{
	if( WorldPos.x > (ModelPos.x - ModelSize.x) && WorldPos.x < (ModelPos.x + ModelSize.x) &&
		WorldPos.z > (ModelPos.z - ModelSize.z) && WorldPos.z < (ModelPos.z + ModelSize.z) )
		return true;
	return false;
}

//***********************************************************************************************************
// bool CJudgment::ANGLEBOXandCIRCLE
// �����F���ʏ�̊p�x�̂�����`�Ɖ~�̓����蔻��
// �����F	D3DXVECTOR2 BoxCenter		��`���S���W
//			D3DXVECTOR2 BoxSize			��`�傫��
//			float fBoxAngle				��`�p�x
//			D3DXVECTOR2 CircleCenter	�~���S���W
//			float fCircleRadius			�~���a
// �߂�l�Ftrue or false
//***********************************************************************************************************
bool ANGLEBOXandCIRCLE( D3DXVECTOR2 BoxCenter, D3DXVECTOR2 BoxSize, float fBoxAngle, D3DXVECTOR2 CircleCenter, float fCircleRadius )
{
	float cx, cy;
	cx = cosf( fBoxAngle ) * ( CircleCenter.x - BoxCenter.x ) - sinf( fBoxAngle ) * ( CircleCenter.y - BoxCenter.y ) + BoxCenter.x;
	cy = sinf( fBoxAngle ) * ( CircleCenter.x - BoxCenter.x ) + cosf( fBoxAngle ) * ( CircleCenter.y - BoxCenter.y ) + BoxCenter.y;

	float x, y;
	if ( cx < BoxCenter.x - BoxSize.x / 2.0f )
		x = BoxCenter.x - BoxSize.x / 2.0f;
	else if ( cx > BoxCenter.x + BoxSize.x / 2.0f )
		x = BoxCenter.x + BoxSize.x / 2.0f;
	else
		x = cx;
 	if ( cy < BoxCenter.y - BoxSize.y / 2.0f )
		y = BoxCenter.y - BoxSize.y / 2.0f;
	else if ( cy > BoxCenter.y + BoxSize.y / 2.0f )
		y = BoxCenter.y + BoxSize.y / 2.0f;
	else
		y = cy;

	if( sqrtf( ( cx - x ) * ( cx - x ) + ( cy - y ) * ( cy - y ) ) < fCircleRadius )
		return true;
	else
		return false;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************