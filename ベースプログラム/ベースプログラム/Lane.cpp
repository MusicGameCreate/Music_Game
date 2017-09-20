#include "Lane.h"

D3DXVECTOR3 BaseLanePos(1238.0f, -856.0f, -58.0f);
//D3DXVECTOR3 BaseLanePos(0.0f, 0.0f, -55.0f);
//float fPos = 1536.0f;
//float fRot = 44.67f;
//float fRot = 7.10f;
float fRot = 0.60f;



CLane::CLane()
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num = 2;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_3D_Data = new TEXTURE_3D_DATA[nObject_Num];

	//bLife = new bool[nObject_Num];
	//Move_Speed = new D3DXVECTOR3[nObject_Num];
	//nSet_Texture = new int[nObject_Num];
	//nDir = new int[nObject_Num];

	// �e��ݒ���w��
	//**********************************************************************
	bBillboard = false;	// �r���{�[�h�ɂ��邩�ǂ���
	bAlphaTest = true;	// ���e�X�g��K�p���邩�ǂ���

	D3DXGetImageInfoFromFile("../DATA/TEXTURE/GameMain/Lane/�m�[�c���[��.png", &info);

	for (int i = 0; i < nObject_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(3000.0f, 440.0f);

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, 1.0f);

		// �摜��RGBA�l
		//******************************************************************
		Tex_3D_Data[i].Red = 255;
		Tex_3D_Data[i].Green = 255;
		Tex_3D_Data[i].Brue = 255;
		Tex_3D_Data[i].Alpha = 255;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_3D_Data[i].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		Tex_3D_Data[i].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//bLife[i] = false;
		//nSet_Texture[i] = 0;
		//nDir[i] = NULL;
	}

	CTexture_3D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/Lane/�m�[�c���[��.png", 0);

	Tex_3D_Data[0].Obj_Pos = D3DXVECTOR3(-BaseLanePos.x, BaseLanePos.y, BaseLanePos.z);
	Tex_3D_Data[0].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, fRot);
	Data.m_vRad[0] = D3DXVECTOR3(0.0f, 0.0f, fRot);

	Tex_3D_Data[1].Obj_Pos = D3DXVECTOR3(BaseLanePos.x, BaseLanePos.y, BaseLanePos.z);
	Tex_3D_Data[1].Obj_Rot = D3DXVECTOR3(0.0f, 0.0f, -fRot);
	Data.m_vRad[1] = D3DXVECTOR3(0.0f, 0.0f, -fRot);

	// �I�u�W�F�N�g�̊p�x����I�u�W�F�N�g�̒[����[�܂ł̋������v�Z
	Data.m_vRot[0].z = fRot * 180.0f / D3DX_PI;
	while (Data.m_vRot[0].z >= 360.0f)
		Data.m_vRot[0].z -= 360.0f;
	Data.m_vRot[1].z = Data.m_vRot[0].z - 90.0f;
	//Data.m_vRot[0].z = -Data.m_vRot[1].z - 90.0f;
	Data.m_vTriSize.x = fabs((Tex_3D_Data[0].Obj_Size.x) * cosf(Data.m_vRad[0].z));
	Data.m_vTriSize.y = fabs((Tex_3D_Data[0].Obj_Size.x) * sinf(Data.m_vRad[0].z));

	Tex_3D_Data[0].Obj_Pos.x = -Data.m_vTriSize.x / 2;
	Tex_3D_Data[1].Obj_Pos.x = Data.m_vTriSize.x / 2;

	Data.m_nLaneNum = LANE_NUM;
	Data.m_fLaneSize = Tex_3D_Data[0].Obj_Size.y / Data.m_nLaneNum;

	Data.Pos[LANE_LEFT] = Tex_3D_Data[LANE_LEFT].Obj_Pos;
	Data.Pos[LANE_RIGHT] = Tex_3D_Data[LANE_RIGHT].Obj_Pos;

	Data.m_vTexSize = Tex_3D_Data[0].Obj_Size;

	//Tex_3D_Data[0].Obj_Pos.x -= (1500.0f + Data.m_fLaneSize / 2);
	//Tex_3D_Data[1].Obj_Pos.x += (1500.0f + Data.m_fLaneSize / 2);

	SelectLaneEffect.Initialize(Data);
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
CLane::~CLane(void)
{
	//delete[] bLife;
	//delete[] nDir;
	//delete[] Move_Speed;
	//delete[] nSet_Texture;
	CLane::Finalize();
}

void CLane::Initialize()
{

}

void CLane::Finalize()
{
	SelectLaneEffect.Finalise();
	CTexture_3D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void CLane::Update(void)
{
	SelectLaneEffect.Update();

	//if (CInput::GetKeyboardData(DIK_A, TRIGGER))
	//{
	//	fRot += 0.01f;
	//	Tex_3D_Data[0].Obj_Rot.z = fRot;
	//	Tex_3D_Data[1].Obj_Rot.z = -fRot;
	//}
	//if (CInput::GetKeyboardData(DIK_S, TRIGGER))
	//{
	//	fRot -= 0.01f;
	//	Tex_3D_Data[0].Obj_Rot.z = fRot;
	//	Tex_3D_Data[1].Obj_Rot.z = -fRot;
	//}

	//if (CInput::GetKeyboardData(DIK_D, PRESS))
	//{
	//	BaseLanePos.x += 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.x = -BaseLanePos.x;
	//	Tex_3D_Data[1].Obj_Pos.x = BaseLanePos.x;
	//}
	//if (CInput::GetKeyboardData(DIK_F, PRESS))
	//{
	//	BaseLanePos.x -= 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.x = -BaseLanePos.x;
	//	Tex_3D_Data[1].Obj_Pos.x = BaseLanePos.x;
	//}
	//if (CInput::GetKeyboardData(DIK_Q, PRESS))
	//{
	//	BaseLanePos.y -= 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.y = BaseLanePos.y;
	//	Tex_3D_Data[1].Obj_Pos.y = BaseLanePos.y;
	//}
	//if (CInput::GetKeyboardData(DIK_W, PRESS))
	//{
	//	BaseLanePos.y += 1.0f;
	//	Tex_3D_Data[0].Obj_Pos.y = BaseLanePos.y;
	//	Tex_3D_Data[1].Obj_Pos.y = BaseLanePos.y;
	//}

	//if (CInput::GetKeyboardData(DIK_LSHIFT, TRIGGER))
	//{
	//	Debug_Save_ObjectPos("���[�����W", Tex_3D_Data[0].Obj_Pos);
	//	Debug_Save_ObjectPos("���[���p�x", Tex_3D_Data[0].Obj_Rot);
	//}

	CTexture_3D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void CLane::Draw(void)
{
	SelectLaneEffect.Draw();
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_3D_Base::Draw(i, 0);
	}
}

void CLane::NotesEffect(int LaneNum, int LaneType)
{
	SelectLaneEffect.NotesEffect(LaneNum, LaneType);
}

void CLane::TimerReset(int LaneNum, int LaneType)
{
	SelectLaneEffect.TimerReset(LaneNum, LaneType);
}

//*************************************************************************
// EOF
//*************************************************************************
