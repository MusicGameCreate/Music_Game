//***********************************************************************************************************
//
//　 Model_Template.cpp
// 　モデル描画プログラムのテンプレートcpp
//   モデル描画基本クラスを継承しています( CModel_Base )
//
//***********************************************************************************************************

//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "Model_Template.h"

//***********************************************************************************************************
// コンストラクタ
//***********************************************************************************************************
Model_Template::Model_Template()
{
	// オブジェクトの作成個数を指定
	//*******************************************************************************************************
	nObject_Num = 1;


	// オブジェクトの個数分、必要なサイズを確保
	//*******************************************************************************************************
	Model_Data = new MODEL_DATA[nObject_Num];


	// 各種初期化
	//*******************************************************************************************************
	for ( int i = 0 ; i < nObject_Num ; i ++ )
	{
		// 座標
		//***************************************************************************************************
		Model_Data[i].Model_Pos		= D3DXVECTOR3( 0.0f,  0.0f,0.0f );

		// 回転角度
		//***************************************************************************************************
		Model_Data[i].Model_Rot		= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

		// 拡大率
		//***************************************************************************************************
		Model_Data[i].Model_Scale	= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
	}

	CModel_Base::Init("../DATA/MODEL/床.x");
}

//***********************************************************************************************************
// デストラクタ
//***********************************************************************************************************
Model_Template::~Model_Template()
{
	CModel_Base::Finalise();
}

//***********************************************************************************************************
// 更新処理
//***********************************************************************************************************
void Model_Template::Update()
{
	CModel_Base::Update();
}

//***********************************************************************************************************
// 描画処理
//***********************************************************************************************************
void Model_Template::Draw()
{
	//CModel_Base::Draw();
}