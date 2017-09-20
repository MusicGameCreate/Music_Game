#pragma once

#include "BaseNotes.h"

class CLongNotes : public CBaseNotes
{
private:
	// �����O�m�[�c�p
	D3DXVECTOR2 TriDelta;
	double		HitTimer;
	int			NotesNum;		// �m�[�c�̃T�C�Y
								//bool		HitFlag;		// �{�^����������Ă��邩�ǂ���
	bool		MissFlag;		// �r���Ń{�^���������ꂽ���ǂ���
	bool		DecitionFlag;	// ����^�C�~���O�ɓ��������ǂ���
	bool		UpdateFlag;		// �����O������^�C�~���O�ɓ������u��
public:
	~CLongNotes() override;

	void Initialize(char* filePass, LaneData data) override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	// �����O�m�[�c�p�̐�p�����֐�(���[���������E���A���[�����ォ�����A�ꏬ�߂̎��ԁA�����̒x�ꂽ����)
	void Create(int laneType, int laneNum, double CourceTime) override;

	void SetNotesSize(int notesNum) { NotesNum = notesNum; }// ���m�[�c���̃T�C�Y���ݒ�
															//void SetHitFlag(bool flag) { HitFlag = flag; }			// �m�[�c��������Ă��邩�ǂ����Z�b�g
	void SetMissFlag(bool flag) { MissFlag = flag; }
	void SetDecitionFlag(bool flag) { DecitionFlag = flag; }

	double GetTiming() override;
	//bool GetHitFlag() { return HitFlag; }		// �m�[�c�����ɉ�����Ă��邩�ǂ����Ԃ�
	bool GetMissFlag() { return MissFlag; }
	bool GetDecitionFlag() { return DecitionFlag; }
};