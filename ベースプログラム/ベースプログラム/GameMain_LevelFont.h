#pragma once

//******************************************
// インクルード部
//******************************************
#include "CTexture_2D_Base.h"

//******************************************
// クラス定義
//******************************************
class GameMain_LevelFont : public CTexture_2D_Base
{
private:

public:
	void Update();					// 更新
	void Draw();					// 描画

	GameMain_LevelFont();			// コンストラクタ
	virtual ~GameMain_LevelFont();	// デストラクタ
};