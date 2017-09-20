// IPlayDataMgr

#pragma once

typedef enum {
	eData_SelectMusicNum,	// �I�������Ȃ̔ԍ�
	eData_Difficult,		// �I��������Փx
	eData_Normal_L_Num,		// ���m�[�}���m�[�c��
	eData_Normal_R_Num,		// �E�m�[�}���m�[�c��
	eData_Click_L_Num,		// ���N���b�N�m�[�c��
	eData_Click_R_Num,		// �E�N���b�N�m�[�c��
	eData_Wheel_Num,		// �z�C�[���m�[�c��
	eData_Score,			// �X�R�A�̒l
	eData_NowCombo,			// �p�����Ă���R���{��
	eData_MaxCombo,			// �ő�R���{��

}eDataType;

class IPlayDataMgr
{
public:
	virtual ~IPlayDataMgr() = 0;
	virtual int		GetPlayData(eDataType) = 0;
	virtual void	SetPlayData(eDataType, int nPlayDate) = 0;
};