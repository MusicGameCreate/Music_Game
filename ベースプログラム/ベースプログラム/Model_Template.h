// モデル描画テンプレートクラス
// 派生クラス
#ifndef _CMODEL_TEMPLATE_H_
#define _CMODEL_TEMPLATE_H_

//********************************************************
//インクルード部
//********************************************************
#include "CModel_Base.h"

//********************************************************
//クラス定義
//********************************************************
class Model_Template :public CModel_Base
{
private:

public:
	void		Update();				// 更新
	void		Draw();					// 描画

	Model_Template();					// コンストラクタ
	virtual ~Model_Template();			// デストラクタ
};

#endif