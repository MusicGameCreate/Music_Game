#pragma once

#include "BaseNotes.h"

class CLongNotes : public CBaseNotes
{
private:
	// ロングノーツ用
	D3DXVECTOR2 TriDelta;
	double		HitTimer;
	int			NotesNum;		// ノーツのサイズ
								//bool		HitFlag;		// ボタンが押されているかどうか
	bool		MissFlag;		// 途中でボタンが離されたかどうか
	bool		DecitionFlag;	// 判定タイミングに入ったかどうか
	bool		UpdateFlag;		// ロングが判定タイミングに入った瞬間
public:
	~CLongNotes() override;

	void Initialize(char* filePass, LaneData data) override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	// ロングノーツ用の専用生成関数(レーンが左か右か、レーンが上か下か、一小節の時間、生成の遅れた時間)
	void Create(int laneType, int laneNum, double CourceTime) override;

	void SetNotesSize(int notesNum) { NotesNum = notesNum; }// 何ノーツ分のサイズか設定
															//void SetHitFlag(bool flag) { HitFlag = flag; }			// ノーツが押されているかどうかセット
	void SetMissFlag(bool flag) { MissFlag = flag; }
	void SetDecitionFlag(bool flag) { DecitionFlag = flag; }

	double GetTiming() override;
	//bool GetHitFlag() { return HitFlag; }		// ノーツが既に押されているかどうか返す
	bool GetMissFlag() { return MissFlag; }
	bool GetDecitionFlag() { return DecitionFlag; }
};