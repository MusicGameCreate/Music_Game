#pragma once

//******************************************
// インクルード部
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// クラス定義
//******************************************
class Fade_Background : public CTexture_2D_Base
{
private:
	int		nAddAlpha;
	int		nFrameCnt;
	bool		bFrame;

public:
	void		Update();				// 更新
	void		Draw();					// 描画

	Fade_Background();				// コンストラクタ
	virtual ~Fade_Background();		// デストラクタ
};