#pragma once
#include "Define.h"
#include "CTexture_3D_Base.h"
#include "Lane.h"
#include "CTimer.h"

// �m�[�c���N���X
class CBaseNotes : public CTexture_3D_Base
{
protected:
	double		m_dMajorTime;	// �ꏬ�߂̎���
	double		m_Timer;		// �ꏬ�߂̎��Ԍv���p�^�C�}�[
	int			m_nLaneType;	// ���[���̕���
	int			m_nLaneNum;		// ���[���ԍ�
	double		m_dBPM;			// BPM
	double		m_dHiSpeed;		// �n�C�X�s
	D3DXVECTOR2	m_vNotexVec;	// 1�b�ԂŐi�ރm�[�c�̑��x
	double		m_dLifeTime;	// ��������
	bool		m_bUse;			// �����t���O
	D3DXVECTOR3	m_vStartPos;		// �����n�_
	D3DXVECTOR3	m_vEndPos;			// ���B�n�_

	D3DXIMAGE_INFO	info;			// �摜���
	LaneData	m_Data;
public:
	CBaseNotes();
	virtual ~CBaseNotes();

	virtual void Initialize(char* filePass, LaneData data);
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
	// �m�[�c�����֐�(���[���f�[�^�A���[���������E���A���[���̏ォ��̔ԍ�)
	virtual void Create(int laneType, int laneNum, double CourseTime);

	// �Z�b�^

	void SetSpeed(double bpm, double hispeed, double majorTime);				// �m�[�c�ړ����x�ݒ�
	void SetUseFlag(bool use) { m_bUse = use; }				// �g�p�t���O���O������Z�b�g

															// �Q�b�^

	inline int GetUseFlag() { return m_bUse; }		// �g�p�t���O��Ԃ�
	virtual double GetTiming();						// ����^�C�~���O��Ԃ�(�}�C�i�X�Ȃ瑬���A�v���X�Ȃ�x��)
	inline int GetLaneNum() { return m_nLaneNum; }	// ���݂̃��[���ԍ���Ԃ�
	inline int GetLaneType() { return m_nLaneType; }// ���݂̃��[���̕�����Ԃ�
};