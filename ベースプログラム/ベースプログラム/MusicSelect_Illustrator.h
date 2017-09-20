//*************************************************************************
//
// 曲セレクト画面・ジャケット製作者フォント
//
//*************************************************************************
#pragma once

//*************************************************************************
// インクルード部
//*************************************************************************
#include "CFont_Base.h"

//*************************************************************************
// クラス定義
//*************************************************************************
class MusicSelect_Illustrator : public CFont_Base
{
	int	Now_Illustrator_Length;

public:
	void Update( wchar_t* FONT, int LENGTH, bool CHANGE );
	void Draw(void);

	MusicSelect_Illustrator(void);
	virtual ~MusicSelect_Illustrator(void);
};

//*************************************************************************
// EOF
//*************************************************************************