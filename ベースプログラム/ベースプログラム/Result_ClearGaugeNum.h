//*************************************************************************
//
// ここにオブジェクトの説明
//
//*************************************************************************
#pragma once 

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CTexture_2D_Base.h" 

//*************************************************************************
// クラス定義
//*************************************************************************
class Result_ClearGaugeNum : public CTexture_2D_Base
{
private:
	int nGauge;

	int nFrame_Cnt;
	int nGauge_Work;

public:
	void Update(void);
	void Draw(void);

	Result_ClearGaugeNum(int nData);
	virtual ~Result_ClearGaugeNum(void);
};

//*************************************************************************
// EOF
//*************************************************************************
