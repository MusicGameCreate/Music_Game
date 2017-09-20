// PlayDataMgr.h

#pragma once

#include "IPlayDataMgr.h"

class PlayDataMgr : IPlayDataMgr
{
private:
	int		nSelectMusicNum;		// 選択された曲番号
	int		nDifficult;				// 選択された難易度
	int		nNormalLeftNotesNum;	// ノーマル左ノーツの数
	int		nNormalRightNotesNum;	// ノーマル右ノーツの数
	int		nClickLeftNotesNum;		// クリック左ノーツの数
	int		nClickRightNotesNum;	// クリック右ノーツの数
	int		nWheelNotesNum;			// ホイールノーツの数
	int		nScore;					// スコアの値
	int		nNowCombo;				// 継続しているコンボ数
	int		nMaxCombo;				// 最大コンボ数


public:
	PlayDataMgr();

	int GetPlayData(eDataType datatype) override;
	void SetPlayData(eDataType datetype, int nData) override;
};