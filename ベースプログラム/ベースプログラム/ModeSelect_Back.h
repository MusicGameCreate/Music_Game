#pragma once

//******************************************
// インクルード部
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// クラス定義
//******************************************
class ModeSelect_Back : public CTexture_2D_Base
{
private:

public:
	void Update();				// 更新
	void Draw();				// 描画

	ModeSelect_Back();			// コンストラクタ
	virtual ~ModeSelect_Back();	// デストラクタ
};