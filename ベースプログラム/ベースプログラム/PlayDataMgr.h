// PlayDataMgr.h

#pragma once

#include "IPlayDataMgr.h"

class PlayDataMgr : IPlayDataMgr
{
private:
	int		nSelectMusicNum;		// �I�����ꂽ�Ȕԍ�
	int		nDifficult;				// �I�����ꂽ��Փx
	int		nNormalLeftNotesNum;	// �m�[�}�����m�[�c�̐�
	int		nNormalRightNotesNum;	// �m�[�}���E�m�[�c�̐�
	int		nClickLeftNotesNum;		// �N���b�N���m�[�c�̐�
	int		nClickRightNotesNum;	// �N���b�N�E�m�[�c�̐�
	int		nWheelNotesNum;			// �z�C�[���m�[�c�̐�
	int		nScore;					// �X�R�A�̒l
	int		nNowCombo;				// �p�����Ă���R���{��
	int		nMaxCombo;				// �ő�R���{��


public:
	PlayDataMgr();

	int GetPlayData(eDataType datatype) override;
	void SetPlayData(eDataType datetype, int nData) override;
};