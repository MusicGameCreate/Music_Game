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
class MusicSelect_BackGround : public CTexture_2D_Base
{
private:

public:
	void Update(void);
	void Draw(void);

	MusicSelect_BackGround(void);
	virtual ~MusicSelect_BackGround(void);
};

//*************************************************************************
// EOF
//*************************************************************************
