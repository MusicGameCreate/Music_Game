#pragma once
#include "BaseNotes.h"

// �z�C�[���m�[�c�N���X
class CWheelNotes : public CBaseNotes
{
private:

public:
	~CWheelNotes() override;

	void Initialize(char* fileName, LaneData data) override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	// �z�C�[���m�[�c�p�̐�p�����֐�(���[���f�[�^�A���[���������E���A���[�����ォ����)
	void Create(int laneType, int laneNum, double CourceTime) override;
};