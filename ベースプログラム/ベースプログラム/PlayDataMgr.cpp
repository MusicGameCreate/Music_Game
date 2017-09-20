// PlayDataMgr.cpp

#include "PlayDataMgr.h"

PlayDataMgr::PlayDataMgr(void)
{
	nSelectMusicNum = 0;
	nNormalLeftNotesNum = 0;
	nNormalRightNotesNum = 0;
	nClickLeftNotesNum = 0;
	nClickRightNotesNum = 0;
	nWheelNotesNum = 0;
	nScore = 0;
	nNowCombo = 0;
	nMaxCombo = 0;
}

int PlayDataMgr::GetPlayData(eDataType datatype)
{
	switch (datatype)
	{
	case eData_SelectMusicNum:
		return nSelectMusicNum;
	case eData_Difficult:
		return nDifficult;
	case eData_Normal_L_Num:
		return nNormalLeftNotesNum;
	case eData_Normal_R_Num:
		return nNormalRightNotesNum;
	case eData_Click_L_Num:
		return nClickLeftNotesNum;
	case eData_Click_R_Num:
		return nClickRightNotesNum;
	case eData_Wheel_Num:
		return nWheelNotesNum;
	case eData_Score:
		return nScore;
	case eData_NowCombo:
		return nNowCombo;
	case eData_MaxCombo:
		return nMaxCombo;
	}
}

void PlayDataMgr::SetPlayData(eDataType datatype, int nData)
{
	switch (datatype)
	{
	case eData_SelectMusicNum:
		nSelectMusicNum = nData;
		break;
	case eData_Difficult:
		nDifficult = nData;
		break;
	case eData_Normal_L_Num:
		nNormalLeftNotesNum = nData;
		break;
	case eData_Normal_R_Num:
		nNormalRightNotesNum = nData;
		break;
	case eData_Click_L_Num:
		nClickLeftNotesNum = nData;
		break;
	case eData_Click_R_Num:
		nClickRightNotesNum = nData;
		break;
	case eData_Wheel_Num:
		nWheelNotesNum = nData;
		break;
	case eData_Score:
		nScore = nData;
		break;
	case eData_NowCombo:
		nNowCombo = nData;
		break;
	case eData_MaxCombo:
		nMaxCombo = nData;
		break;
	}
}