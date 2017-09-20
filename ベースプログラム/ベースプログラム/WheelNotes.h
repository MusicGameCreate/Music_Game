#pragma once
#include "BaseNotes.h"

// ホイールノーツクラス
class CWheelNotes : public CBaseNotes
{
private:

public:
	~CWheelNotes() override;

	void Initialize(char* fileName, LaneData data) override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	// ホイールノーツ用の専用生成関数(レーンデータ、レーンが左か右か、レーンが上か下か)
	void Create(int laneType, int laneNum, double CourceTime) override;
};