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
class Result_HiScore : public CTexture_2D_Base
{
private:
	int nHi_Score;	// 過去最高スコアを格納

public:
	void Update(void);
	void Draw(void);

	Result_HiScore(void);
	virtual ~Result_HiScore(void);
};

//*************************************************************************
// EOF
//*************************************************************************
