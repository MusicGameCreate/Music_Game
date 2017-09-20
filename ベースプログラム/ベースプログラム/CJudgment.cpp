//***********************************************************************************************************
//
//		CJudgment.cpp
//		当たり判定処理
//
//***********************************************************************************************************


//***********************************************************************************************************
// インクルード部
//***********************************************************************************************************
#include "CJudgment.h"

//***********************************************************************************************************
// bool BOX2D
// 説明：平面上のの2つの矩形の当たり判定を返す
// 引数：	D3DXVECTOR2 ALeftUp		矩形A左上頂点座標
//			D3DXVECTOR2 ARightDown	矩形A右下頂点座標
//			D3DXVECTOR2 BLeftUp		矩形B左上頂点座標
//			D3DXVECTOR2 BRightDown	矩形B右下頂点座標
// 戻り値：true or false
//***********************************************************************************************************
bool BOX2D(D3DXVECTOR2 ALeftUp, D3DXVECTOR2 ARightDown, D3DXVECTOR2 BLeftUp, D3DXVECTOR2 BRightDown)
{
	if	
	(
		ALeftUp.x <= BRightDown.x
		&&
		ARightDown.x >= BLeftUp.x
		&&
		ALeftUp.y <= BRightDown.y
		&&
		ARightDown.y >= BLeftUp.y
	)
		return true;
	else
		return false;
}

//***********************************************************************************************************
// bool BOX3D
// 説明：ボックス3Dの当たり判定を返す(未制作)
// 引数：なし　戻り値：true or false
//***********************************************************************************************************
bool BOX3D()
{
	return false;
}

//***********************************************************************************************************
// bool MouseTex2D
// 説明：マウス座標とテクスチャ座標の当たり判定を返す
// 引数：MousePos, TexPos, TexSize　戻り値：true or false
//***********************************************************************************************************
bool MouseTex2D(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize, bool Portrait)
{
	if (!Portrait)
	{
		TexSize.x = TexSize.x / 2;
		TexSize.y = TexSize.y / 2;
		if (MousePos.x >= (TexPos.x - TexSize.x) && MousePos.x <= (TexPos.x + TexSize.x) &&
			MousePos.y >= (TexPos.y - TexSize.y) && MousePos.y <= (TexPos.y + TexSize.y))
			return true;
	}
	else
	{
		float TexTemp;
		TexTemp = TexSize.x;
		TexSize.x = TexSize.y;
		TexSize.y = TexTemp;
		TexSize.x = TexSize.x / 2;
		TexSize.y = TexSize.y / 2;
		if (MousePos.x >= (TexPos.x - TexSize.x) && MousePos.x <= (TexPos.x + TexSize.x) &&
			MousePos.y >= (TexPos.y - TexSize.y) && MousePos.y <= (TexPos.y + TexSize.y))
			return true;

	}

	return false;
}

//***********************************************************************************************************
// bool CJudgment::MouseTex2DCircle
// 説明：マウス座標とテクスチャ座標の当たり判定を返す(円ver)
// 引数：MousePos, TexPos, TexSize　戻り値：true or false
//***********************************************************************************************************
bool MouseTex2DCircle(D3DXVECTOR3 MousePos, D3DXVECTOR3 TexPos, D3DXVECTOR2 TexSize)
{
	// 円画像の半径
	TexSize.x = TexSize.x / 2;

	// マウス座標とテクスチャの当たり判定計算
	if( ((MousePos.x - TexPos.x) * (MousePos.x - TexPos.x) + 
		 (MousePos.y - TexPos.y) * (MousePos.y - TexPos.y)) <= (TexSize.x * TexSize.x) )
		return true;

	return false;
}

//***********************************************************************************************************
// bool CJudgment::CIRCLE
// 説明：平面上の二つの円の当たり判定
// 引数：	D3DXVECTOR2 APos	円A中心座標
//			float fARudius		円A半径
//			D3DXVECTOR2 BPos	円B中心座標
//			float fBRudius		円B半径
// 戻り値：true or false
//***********************************************************************************************************
bool CIRCLE(D3DXVECTOR2 APos, float fARudius, D3DXVECTOR2 BPos, float fBRudius)
{
	if	(
			sqrtf( ( APos.x - BPos.x ) * ( APos.x - BPos.x ) + ( APos.y - BPos.y ) * ( APos.y - BPos.y ) )
			<
			fARudius + fBRudius
		)
		return true;
	else
		return false;
}

//***********************************************************************************************************
// bool CJudgment::WorldModel2D
// 説明：ワールド座標とモデル座標の当たり判定を返す
// 引数：WorldPos, ModelPos, ModelSize　戻り値：true or false
//***********************************************************************************************************
bool WorldModel2D(D3DXVECTOR3 WorldPos, D3DXVECTOR3 ModelPos, D3DXVECTOR3 ModelSize)
{
	if( WorldPos.x > (ModelPos.x - ModelSize.x) && WorldPos.x < (ModelPos.x + ModelSize.x) &&
		WorldPos.z > (ModelPos.z - ModelSize.z) && WorldPos.z < (ModelPos.z + ModelSize.z) )
		return true;
	return false;
}

//***********************************************************************************************************
// bool CJudgment::ANGLEBOXandCIRCLE
// 説明：平面上の角度のついた矩形と円の当たり判定
// 引数：	D3DXVECTOR2 BoxCenter		矩形中心座標
//			D3DXVECTOR2 BoxSize			矩形大きさ
//			float fBoxAngle				矩形角度
//			D3DXVECTOR2 CircleCenter	円中心座標
//			float fCircleRadius			円半径
// 戻り値：true or false
//***********************************************************************************************************
bool ANGLEBOXandCIRCLE( D3DXVECTOR2 BoxCenter, D3DXVECTOR2 BoxSize, float fBoxAngle, D3DXVECTOR2 CircleCenter, float fCircleRadius )
{
	float cx, cy;
	cx = cosf( fBoxAngle ) * ( CircleCenter.x - BoxCenter.x ) - sinf( fBoxAngle ) * ( CircleCenter.y - BoxCenter.y ) + BoxCenter.x;
	cy = sinf( fBoxAngle ) * ( CircleCenter.x - BoxCenter.x ) + cosf( fBoxAngle ) * ( CircleCenter.y - BoxCenter.y ) + BoxCenter.y;

	float x, y;
	if ( cx < BoxCenter.x - BoxSize.x / 2.0f )
		x = BoxCenter.x - BoxSize.x / 2.0f;
	else if ( cx > BoxCenter.x + BoxSize.x / 2.0f )
		x = BoxCenter.x + BoxSize.x / 2.0f;
	else
		x = cx;
 	if ( cy < BoxCenter.y - BoxSize.y / 2.0f )
		y = BoxCenter.y - BoxSize.y / 2.0f;
	else if ( cy > BoxCenter.y + BoxSize.y / 2.0f )
		y = BoxCenter.y + BoxSize.y / 2.0f;
	else
		y = cy;

	if( sqrtf( ( cx - x ) * ( cx - x ) + ( cy - y ) * ( cy - y ) ) < fCircleRadius )
		return true;
	else
		return false;
}

//***********************************************************************************************************
// EOF
//***********************************************************************************************************