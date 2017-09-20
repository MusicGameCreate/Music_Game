#include "SelectLaneEffect.h"
#include "TimeServer.h"

const double EffectTime = 0.15f;

CSelectLaneEffect::CSelectLaneEffect()
{
	for (int i = 0; i < LANE_NUM * 2; i++)
	{
		SelectFlag[i] = false;
		NotesEffectFlag[i] = false;
		Timer[i] = 0.0f;
	}
}

CSelectLaneEffect::~CSelectLaneEffect()
{
	CTexture_3D_Base::Finalise();
}

void CSelectLaneEffect::Initialize(LaneData data)
{

	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num = LANE_NUM * 2;

	// �e�N�X�`��������ގg�p���邩�H(�Œ� 1�`)
	//**********************************************************************
	nUse_Texture_Num = 1;

	// �I�u�W�F�N�g�̌����A�K�v�ȃT�C�Y���m��
	//**********************************************************************
	Tex_3D_Data = new TEXTURE_3D_DATA[nObject_Num];

	for (int i = 0; i < nObject_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		//if (i / LANE_NUM == 0)
		//{// ��
		//Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(-data.m_vTriSize.x / 2, -data.m_vTriSize.y / 2, ((data.Pos[0].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		//}
		//else
		//{
		//	Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(data.Pos[1].x, data.Pos[1].y, ((data.Pos[1].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		//}

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(3000.0f, data.m_fLaneSize);

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
		Tex_3D_Data[i].Alpha = 128;

		// �摜�̊g�嗦( 0.0f�` )
		//******************************************************************
		Tex_3D_Data[i].Obj_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// �摜�̉�]�p�x( 0.0f�` )
		//******************************************************************
		//Tex_3D_Data[i].Obj_Rot = D3DXVECTOR3(data.m_vRot[nObject_Num / LANE_NUM].x, 0.0f, 0.0f);
		//Tex_3D_Data[i].Obj_Rot = data.m_vRot[0];
	}
	
	CTexture_3D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/Lane/SelectLaneEffect.png", 0);

	for (int i = 0; i < LANE_NUM; i++)
	{
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(data.Pos[0].x, data.Pos[0].y - 1.0f, ((data.Pos[0].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		//Tex_3D_Data[i].Obj_Pos.x -= 2000;
		//Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(data.Pos[0].x, data.Pos[0].y, ((data.Pos[0].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		Tex_3D_Data[i].Obj_Rot = data.m_vRad[0];
	}
	for (int i = LANE_NUM; i < LANE_NUM*2; i++)
	{
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(data.Pos[1].x, data.Pos[1].y - 1.0f, ((data.Pos[1].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		//Tex_3D_Data[i].Obj_Pos.x -= 2000;
		//Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(data.Pos[1].x, data.Pos[1].y, ((data.Pos[1].z + (data.m_vTexSize.y / 2)) - data.m_fLaneSize / 2) - ((i % LANE_NUM) * data.m_fLaneSize));
		Tex_3D_Data[i].Obj_Rot = data.m_vRad[1];
	}
}

void CSelectLaneEffect::Finalize()
{

}

void CSelectLaneEffect::Update()
{
	for (int i = 0; i < LANE_NUM * 2; i++)
	{
		if (!NotesEffectFlag[i])
			continue;
		Timer[i] += CTimeServer::GetDifference();
		if (Timer[i] > EffectTime)
		{
			Timer[i] = 0.0f;
			NotesEffectFlag[i] = false;
			Tex_3D_Data[i].Red = 255;
			Tex_3D_Data[i].Green = 255;
			Tex_3D_Data[i].Brue = 255;
			Tex_3D_Data[i].Alpha = 128;
		}
	}
	CTexture_3D_Base::Update();
}

void CSelectLaneEffect::Draw()
{
	for (int i = 0; i < nObject_Num; i++)
	{
		if (!SelectFlag[i])
			continue;
		CTexture_3D_Base::Draw(i, 0);
	}
}

void CSelectLaneEffect::SetSelectFlag(deque<int> selectLane)
{
	for (int i = 0; i < LANE_NUM*2; i++)
	{
		SelectFlag[i] = false;
	}
	if (selectLane.size() < 2)
		return;
	int Up = selectLane.front();
	selectLane.pop_front();
	int Down = selectLane.front();
	selectLane.pop_front();
	for (int i = Up; i <= Down; i++)
	{
		SelectFlag[i] = true;
		SelectFlag[i + LANE_NUM] = true;
	}
}

void CSelectLaneEffect::NotesEffect(int LaneNum, int LaneType)
{
	NotesEffectFlag[LaneNum + (LaneType * LANE_NUM)] = true;

	Tex_3D_Data[LaneNum + (LaneType * LANE_NUM)].Green = 0;
	Tex_3D_Data[LaneNum + (LaneType * LANE_NUM)].Red = 255;
	Tex_3D_Data[LaneNum + (LaneType * LANE_NUM)].Brue = 0;
	Tex_3D_Data[LaneNum + (LaneType * LANE_NUM)].Alpha = 128;
}

void CSelectLaneEffect::TimerReset(int LaneNum, int LaneType)
{
	Timer[LaneNum + (LaneType * LANE_NUM)] = 0.0f;
}