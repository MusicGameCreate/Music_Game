#pragma once
#include "Define.h"
#include "CTexture_3D_Base.h"
#include "Lane.h"
#include "CTimer.h"

// ノーツ基底クラス
class CBaseNotes : public CTexture_3D_Base
{
protected:
	double		m_dMajorTime;	// 一小節の時間
	double		m_Timer;		// 一小節の時間計測用タイマー
	int			m_nLaneType;	// レーンの方向
	int			m_nLaneNum;		// レーン番号
	double		m_dBPM;			// BPM
	double		m_dHiSpeed;		// ハイスピ
	D3DXVECTOR2	m_vNotexVec;	// 1秒間で進むノーツの速度
	double		m_dLifeTime;	// 生存時間
	bool		m_bUse;			// 生存フラグ
	D3DXVECTOR3	m_vStartPos;		// 生成地点
	D3DXVECTOR3	m_vEndPos;			// 到達地点

	D3DXIMAGE_INFO	info;			// 画像情報
	LaneData	m_Data;
public:
	CBaseNotes();
	virtual ~CBaseNotes();

	virtual void Initialize(char* filePass, LaneData data);
	virtual void Finalize();
	virtual void Update();
	virtual void Draw();
	// ノーツ生成関数(レーンデータ、レーンが左か右か、レーンの上からの番号)
	virtual void Create(int laneType, int laneNum, double CourseTime);

	// セッタ

	void SetSpeed(double bpm, double hispeed, double majorTime);				// ノーツ移動速度設定
	void SetUseFlag(bool use) { m_bUse = use; }				// 使用フラグを外部からセット

															// ゲッタ

	inline int GetUseFlag() { return m_bUse; }		// 使用フラグを返す
	virtual double GetTiming();						// 判定タイミングを返す(マイナスなら速い、プラスなら遅い)
	inline int GetLaneNum() { return m_nLaneNum; }	// 現在のレーン番号を返す
	inline int GetLaneType() { return m_nLaneType; }// 現在のレーンの方向を返す
};