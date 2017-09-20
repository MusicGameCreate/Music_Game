#pragma once
#include "CTexture_3D_Base.h"
#include "SelectLaneEffect.h"
#include "Singleton.h"

enum LANE_TYPE
{
	LANE_LEFT,
	LANE_RIGHT,

	LANE_MAX
};

class CLane : public CTexture_3D_Base, public Singleton<CLane>
{
	friend Singleton<CLane>;
private:
	LaneData			Data;
	CSelectLaneEffect	SelectLaneEffect;

	D3DXIMAGE_INFO	info;			// âÊëúèÓïÒ
	CLane();
	~CLane();
public:

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	LaneData GetLaneData() { return Data; }
	void SetSelectLane(deque<int> selectLane) { SelectLaneEffect.SetSelectFlag(selectLane); }
	void TimerReset(int LaneNum, int LaneType);
	void NotesEffect(int LaneNum, int LaneType);
	//D3DXVECTOR2 GetLaneHarfSize() {return Data.m_vTriSize;}
	//D3DXVECTOR3 GetLaneRot() { return Data.m_vRot; };
};