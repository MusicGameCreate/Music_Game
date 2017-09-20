#pragma once

#include "CTexture_3D_Base.h"
#include "Lane.h"
#include <vector>

using namespace std;

enum EFFECT_TYPE
{
	EFFECT_CRITICAL,
	EFFECT_FAST,
	EFFECT_SLOW,

	EFFECT_MAX
};

class CNotesEffect : public CTexture_3D_Base
{
private:
	vector<int>	m_AnimNum;		// �A�j���[�V��������
	vector<int>	m_AnimCount;	// ���݂̃A�j���[�V�����J�E���^
	bool		m_bUse;			// �g�p�t���O
	double		m_LifeTime;		// ��������
	double		m_Timer;		// �����^�C�}�[
	int			m_nLaneNum;		// ���[���ԍ�

	LaneData	m_Data;
	int			m_nEffectType;	// �G�t�F�N�g�̎��
	float t;
public:
	CNotesEffect();
	~CNotesEffect();

	void Initialize(LaneData data);
	void Finalize();
	void Update();
	void Draw();

	void Create(int LaneNum);

	bool GetUseFlag() { return m_bUse; }
	int	GetLaneNum() { return m_nLaneNum; }
};