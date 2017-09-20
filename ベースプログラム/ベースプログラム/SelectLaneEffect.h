#pragma once

#include "CTexture_3D_Base.h"
//#include "Lane.h"
#include <deque>

using namespace std;

// レーンの情報格納構造体
typedef struct
{
	int				m_nLaneNum;		// レーンの数
	D3DXVECTOR3		Pos[2];
	D3DXVECTOR3		m_vRot[2];
	D3DXVECTOR3		m_vRad[2];		// ラジアン

	float			m_fLaneSize;	// 1レーンのサイズ(y)
	D3DXVECTOR2		m_vTriSize;		// 端から端までの距離(x, y)
	D3DXVECTOR2		m_vTexSize;		// テクスチャのサイズ(width, height)
									//D3DXVECTOR3		m_vStartPos;	// ノーツ出現位置
									//D3DXVECTOR3		m_vEndPos;		// ノーツ消滅位置
} LaneData;

class CSelectLaneEffect : public CTexture_3D_Base
{
private:
	bool	SelectFlag[LANE_NUM * 2];

	bool	NotesEffectFlag[LANE_NUM * 2];			// ノーツが消えた時のエフェクト
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