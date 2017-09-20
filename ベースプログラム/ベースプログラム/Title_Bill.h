#pragma once

//******************************************
// インクルード部
//******************************************
#include "CTexture_3D_Base.h"

//******************************************
// クラス定義
//******************************************
class Title_Bill : public CTexture_3D_Base
{
private:
	int nAddAlpha;

public:
	void Update();			// 更新
	void Draw();			// 描画

	Title_Bill();			// コンストラクタ
	virtual ~Title_Bill();	// デストラクタ
};