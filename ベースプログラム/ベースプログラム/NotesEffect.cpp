#include "NotesEffect.h"
#include "TimeServer.h"

CNotesEffect::CNotesEffect()
{
	m_bUse = false;
	m_LifeTime = 0.15f;
	m_Timer = 0.0f;
	m_nLaneNum = 0;
	m_nEffectType = 0;
}

CNotesEffect::~CNotesEffect()
{

}

void CNotesEffect::Initialize(LaneData data)
{
	// �I�u�W�F�N�g�����쐬���邩�H(�Œ� 1�`)
	//**********************************************************************
	nObject_Num = 1;

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

	D3DXIMAGE_INFO	info;			// �摜���
	D3DXGetImageInfoFromFile("../DATA/TEXTURE/GameMain/NotesEffect/judge1-2.png", &info);

	for (int i = 0; i < nObject_Num; i++)
	{
		// ���W(�摜�̒��S�����_)
		//******************************************************************
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �I�u�W�F�N�g�̃T�C�Y(X,Y)
		//******************************************************************
		Tex_3D_Data[i].Obj_Size = D3DXVECTOR2(data.m_fLaneSize, data.m_fLaneSize);

		// �e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		Tex_3D_Data[i].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);

		// �A�j���[�V��������
		m_AnimNum.push_back(12);
		m_AnimCount.push_back(1);

		// 1�A�j���[�V�������̃e�N�X�`�����W(0.0f�`1.0f)
		//******************************************************************
		t = 1.0f / 12.0f;
		Tex_3D_Data[i].Tex_Anim = D3DXVECTOR2(1.0f, t);

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
	m_Data = data;

	CTexture_3D_Base::Init();

	// �e�N�X�`���ǂݍ���(�����̏ꍇ�͕�����ǂ݂���ł�������)
	// �����F	TEXTURE_FILE = �ǂݍ��݂����摜�t�@�C���̃p�X
	//			NUMBER		 = �ǂݍ��ރe�N�X�`���p�X�̔z��Ԓn(����̐�������Draw()�œn�������̐����ɂȂ�܂�)
	//						   ( 0 �` �w�肵�Ă�������)
	//**********************************************************************
	CTexture_3D_Base::Load_Texture("../DATA/TEXTURE/GameMain/NotesEffect/judge1-2.png", 0);
}

void CNotesEffect::Finalize()
{
	CTexture_3D_Base::Finalise();
}

void CNotesEffect::Update()
{
	if (!m_bUse)
		return;
	double timer = CTimeServer::GetDifference();
	m_Timer += timer;

	if (m_Timer > (m_LifeTime / (m_AnimNum[0] + 0)) * m_AnimCount[0])
	{
		for (int i = 0; i < nObject_Num; i++)
		{
			Tex_3D_Data[i].Tex_Pos.y += Tex_3D_Data[i].Tex_Anim.y;

			if (Tex_3D_Data[i].Tex_Pos.y >= 1.0f)
				Tex_3D_Data[i].Tex_Pos.y = 0.0f;
		}
		m_AnimCount[0] ++;
	}

	if (m_Timer > m_LifeTime)
	{
		m_AnimCount[0] = 1;
		Tex_3D_Data[0].Tex_Pos = D3DXVECTOR2(0.0f, 0.0f);
		m_bUse = false;
	}

	CTexture_3D_Base::Update();
}

void CNotesEffect::Draw()
{
	if (!m_bUse)
		return;
	for (int i = 0; i < nObject_Num; i++)
	{
		CTexture_3D_Base::Draw(i, 0);
	}
}

void CNotesEffect::Create(int LaneNum)
{
	m_Timer = 0.0f;
	m_nLaneNum = LaneNum;

	for (int i = 0; i < nObject_Num; i++)
	{
		Tex_3D_Data[i].Obj_Pos = D3DXVECTOR3(m_Data.Pos[0].x + (m_Data.m_vTriSize.x / 2), m_Data.Pos[0].y + (m_Data.m_vTriSize.y / 2), (m_Data.Pos[0].z + (m_Data.m_vTexSize.y / 2)) - m_Data.m_fLaneSize / 2 - (LaneNum * m_Data.m_fLaneSize));
	}

	
	m_bUse = true;	// �g�p�t���O�𗧂Ă�
}