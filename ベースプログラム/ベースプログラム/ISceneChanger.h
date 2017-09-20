// ISceneChanger.h

#pragma once

typedef enum
{
	eScene_None,		// なし
	eScene_Title,		// タイトル画面
	eScene_ModeSelect,	// モードセレクト
	eScene_Option,		// オプション
	eScene_MusicSelect,	// 曲セレクト
	eScene_Game,		// ゲーム画面
	eScene_Result,		// リザルト画面
	eScene_End,			// 終了
}eScene;

// シーンを変更するためのインターフェイスクラス
class ISceneChanger
{
public:
	virtual ~ISceneChanger(void) = 0;
	virtual void ChangeScene(eScene NextScene) = 0;	// 指定シーンに遷移
};