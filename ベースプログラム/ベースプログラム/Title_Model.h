#pragma once

//******************************************
// インクルード部
//******************************************
#include "CModel_Base.h"

//******************************************
// クラス定義
//******************************************
class Title_Model : public CModel_Base
{
private:

public:
	void Update();			// 更新
	void Draw();			// 描画

	Title_Model();			// コンストラクタ
	virtual ~Title_Model();	// デストラクタ
};