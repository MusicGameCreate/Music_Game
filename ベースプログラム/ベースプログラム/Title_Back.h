#pragma once

//******************************************
// インクルード部
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// クラス定義
//******************************************
class Title_Back : public CTexture_2D_Base
{
private:

public:
	void Update();			// 更新
	void Draw();			// 描画

	Title_Back();			// コンストラクタ
	virtual ~Title_Back();	// デストラクタ
};