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
	vector<int>	m_AnimNum;		// アニメーション枚数
	vector<int>	m_AnimCount;	// 現在のアニメーションカウンタ
	bool		m_bUse;			// 使用フラグ
	double		m_LifeTime;		// 生存時間
	double		m_Timer;		// 生存タイマー
	int			m_nLaneNum;		// レーン番号

	LaneData	m_Data;
	int			m_nEffectType;	// エフェクトの種類
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