// IPlayDataMgr

#pragma once

typedef enum {
	eData_SelectMusicNum,	// 選択した曲の番号
	eData_Difficult,		// 選択した難易度
	eData_Normal_L_Num,		// 左ノーマルノーツ数
	eData_Normal_R_Num,		// 右ノーマルノーツ数
	eData_Click_L_Num,		// 左クリックノーツ数
	eData_Click_R_Num,		// 右クリックノーツ数
	eData_Wheel_Num,		// ホイールノーツ数
	eData_Score,			// スコアの値
	eData_NowCombo,			// 継続しているコンボ数
	eData_MaxCombo,			// 最大コンボ数

}eDataType;

class IPlayDataMgr
{
public:
	virtual ~IPlayDataMgr() = 0;
	virtual int		GetPlayData(eDataType) = 0;
	virtual void	SetPlayData(eDataType, int nPlayDate) = 0;
};