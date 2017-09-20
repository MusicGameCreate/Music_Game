#pragma once

#include "CTexture_3D_Base.h"
//#include "Lane.h"
#include <deque>

using namespace std;

// ���[���̏��i�[�\����
typedef struct
{
	int				m_nLaneNum;		// ���[���̐�
	D3DXVECTOR3		Pos[2];
	D3DXVECTOR3		m_vRot[2];
	D3DXVECTOR3		m_vRad[2];		// ���W�A��

	float			m_fLaneSize;	// 1���[���̃T�C�Y(y)
	D3DXVECTOR2		m_vTriSize;		// �[����[�܂ł̋���(x, y)
	D3DXVECTOR2		m_vTexSize;		// �e�N�X�`���̃T�C�Y(width, height)
									//D3DXVECTOR3		m_vStartPos;	// �m�[�c�o���ʒu
									//D3DXVECTOR3		m_vEndPos;		// �m�[�c���ňʒu
} LaneData;

class CSelectLaneEffect : public CTexture_3D_Base
{
private:
	bool	SelectFlag[LANE_NUM * 2];

	bool	NotesEffectFlag[LANE_NUM * 2];			// �m�[�c�����������̃G�t�F�N�g
	double	Timer[LANE_NUM * 2];
public:
	CSelectLaneEffect();
	~CSelectLaneEffect();

	void Initialize(LaneData data);
	void Finalize();
	void Update();
	void Draw();

	void SetSelectFlag(deque<int> selectLane);
	void NotesEffect(int LaneNum, int LaneType);
	void TimerReset(int LaneNum, int LaneType);
};