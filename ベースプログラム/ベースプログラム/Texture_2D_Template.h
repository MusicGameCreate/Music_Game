// 2D画像描画クラス
#ifndef _TEXTURE_2D_TEMPLATE_H_
#define _TEXTURE_2D_TEMPLATE_H_

//******************************************
// インクルード部
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// クラス定義
//******************************************
class Texture_2D_Template : public CTexture_2D_Base
{
private:

public:
	void Update();					// 更新
	void Draw();						// 描画

	Texture_2D_Template();			// コンストラクタ
	virtual ~Texture_2D_Template();	// デストラクタ
};

#endif