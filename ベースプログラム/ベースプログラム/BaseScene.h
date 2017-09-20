// BaseScene.h

#pragma once

#include "ISceneChanger.h"

// シーンの基底クラス
class CBaseScene
{
protected:
	ISceneChanger*	mSceneChanger;	// クラス所有元にシーン切り替えを伝える

public:
	CBaseScene(ISceneChanger* changer);

	virtual ~CBaseScene(void){}
	virtual void Initialize(void) {}	// 初期化処理は実装しなくてもいい
	virtual void Finalize(void) {}		// 終了処理は実装しなくてもいい
	virtual void Update(void) = 0;		// 更新処理は必ず継承先で実装
	virtual void Draw(void) = 0;		// 描画処理は必ず継承先で実装
};