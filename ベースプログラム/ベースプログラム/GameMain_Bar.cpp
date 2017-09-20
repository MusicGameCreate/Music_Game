//*************************************************************************
//
// �����ɃI�u�W�F�N�g�̐���
//
//*************************************************************************

//*************************************************************************
// �C���N���[�h��
//*************************************************************************
#include "GameMain_Bar.h"
#include "CInput.h"

//*************************************************************************
// �R���X�g���N�^
//*************************************************************************
GameMain_Bar::GameMain_Bar(void)
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num	= 1;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_2D_Data = new TEXTURE_2D_DATA[nObject_Num];

	for( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_2D_Data[i].Obj_Pos	= D3DXVECTOR3(	560.0f, 360.0f, 0.0f );

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_2D_Data[i].Obj_Size	= D3DXVECTOR2( 120.0f, 340.0f );

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Pos  = D3DXVECTOR2( 0.0f, 0.0f );

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_2D_Data[i].Tex_Anim = D3DXVECTOR2( 1.0f, 1.0f );

		// �摜��RGBA�l
		//******************************************************************
		Tex_2D_Data[i].Red  =
		Tex_2D_Data[i].Green=
		Tex_2D_Data[i].Brue =
		Tex_2D_Data[i].Alpha= 255;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fScale = 1.0f;

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		Tex_2D_Data[i].fRot = 0.0f;
	}

	CTexture_2D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_2D_Base::Load_Texture("../DATA/TEXTURE/GameMain/bar.png", 0);
	
}

//*************************************************************************
// �f�X�g���N�^
//*************************************************************************
GameMain_Bar::~GameMain_Bar(void)
{
	CTexture_2D_Base::Finalise();
}

//*************************************************************************
// �X�V����
//*************************************************************************
void GameMain_Bar::Update(void)
{
	int BarSize = Tex_2D_Data[0].Obj_Size.y / LANE_NUM;
	int SelectLaneUp = -1;
	int SelectLaneDown = LANE_NUM;
	SelectLane.clear();
	MouseY = CInput::GetMousePos().y;
	// �ヌ�[���Z�o
	for (int i = 0; i < LANE_NUM; i++)
	{
		if (MouseY - (CursolSize / 2) < Tex_2D_Data[0].Obj_Pos.y - (Tex_2D_Data[0].Obj_Size.y / 2 - BarSize) + (BarSize * i))
		{
			SelectLane.push_back(i);
			//SelectLane.push_back(i + LANE_NUM);
			break;
		}
	}
	// �����[���Z�o
	for (int i = LANE_NUM - 1; i >= 0; i--)
	{
		if (MouseY + (CursolSize / 2) > Tex_2D_Data[0].Obj_Pos.y - (Tex_2D_Data[0].Obj_Size.y / 2) + (BarSize * i + 2))
		{
			SelectLane.push_back(i);
			//SelectLane.push_back(i + LANE_NUM);
			break;
		}
	}
	//AddRotate();
	CTexture_2D_Base::Update();
}

//*************************************************************************
// �`�揈��
//*************************************************************************
void GameMain_Bar::Draw(void)
{
	//CDirectX::Get_pD3DDevice()->BeginScene();
	CTexture_2D_Base::Draw(0,0);
	//CDirectX::Get_pD3DDevice()->EndScene();
}

void GameMain_Bar::Initialize(int laneSize, int cursolSize)
{
	LaneSize = laneSize;
	CursolSize = cursolSize;
}

void GameMain_Bar::AddRotate()
{
	Tex_2D_Data[0].fRot += 0.01f;
}

// 
deque<int> GameMain_Bar::GetSelectLane()
{
	return SelectLane;
}

//*************************************************************************
// EOF
//*************************************************************************
