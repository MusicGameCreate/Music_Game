//***********************************************************************************************************
//
// モードセレクトシーン一括管理
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "ModeSelect_Scene.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
ModeSelect_Scene::ModeSelect_Scene(ISceneChanger* changer) : CBaseScene(changer)
{
	// ここでオブジェクトのnew処理
	Back = new ModeSelect_Back;
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
ModeSelect_Scene::~ModeSelect_Scene(void)
{
	// ここでオブジェクトのdelete処理
	delete Back;
}

void ModeSelect_Scene::Initialize()
{

}

void ModeSelect_Scene::Finalize()
{

}

//***********************************************************************************************************
// 更新
//***********************************************************************************************************
void ModeSelect_Scene::Update(void)
{
	if (CInput::GetKeyboardData(DIK_RETURN, TRIGGER))
	{
		mSceneChanger->ChangeScene(eScene_MusicSelect);
	}

	// ここでオブジェクトのupdate処理
	Back->Update();
}

//***********************************************************************************************************
// 描画
//***********************************************************************************************************
void ModeSelect_Scene::Draw(void)
{
	// 描画順は上の行から順に(但し2Dベース画像はこの限りではありません)
	Back->Draw();
}