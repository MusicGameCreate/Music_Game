//***********************************************************************************************************
//
// フェードシーン一括管理
//
//***********************************************************************************************************
#pragma once

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Fade_Background.h"

//***********************************************************************************************************
// クラス定義
//***********************************************************************************************************
class Fade_Scene
{
private:
	Fade_Background*	Background;

public:
	void		Update(void);		// 更新
	void		Draw(void);			// 描画

	Fade_Scene(void);				// コンストラクタ
	virtual ~Fade_Scene(void);		// デストラクタ
};

//***********************************************************************************************************
// EOF
//***********************************************************************************************************