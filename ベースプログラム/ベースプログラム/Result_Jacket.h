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
class Result_Jacket : public CTexture_2D_Base
{
private:

public:
	void Update(void);
	void Draw(void);

	Result_Jacket(void);
	virtual ~Result_Jacket(void);
};

//*************************************************************************
// EOF
//*************************************************************************
