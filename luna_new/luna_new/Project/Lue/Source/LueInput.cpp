

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueInput.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------------------------
extern IMouse *Lue_GetMouse( void );
extern IKeyboard *Lue_GetKeyboard( void );


//------------------------------------------------------------------------------------------------
/**
	@brief キーボッドの入力バッファをクリア
	@author 葉迩倭

	キーボードの情報が格納されている入力バッファをクリアします。
*/
//------------------------------------------------------------------------------------------------
void LueInput_ClearKeyBuffer( void )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	pKeyboard->ClearKeyBuffer();
}


//------------------------------------------------------------------------------------------------
/**
	@brief キーボード入力バッファの取得
	@author 葉迩倭

	@retval 0		入力なし
	@return 0以外	押されたキーのキーコード

	キーボード入力バッファ内のデータを１つづつ取り出します。<BR>
	バッファが空になった時点で LUE_VK_NONE が返ります。
*/
//------------------------------------------------------------------------------------------------
eLueVirtualKey LueInput_GetKeyBuffer( void )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	return (eLueVirtualKey)pKeyboard->GetKeyBuffer();
}


//------------------------------------------------------------------------------------------------
/**
	@brief キーボード情報取得
	@author 葉迩倭

	@param Key	[in] 調べたいキーのキーコード

	@retval LTRUE	押されている
	@retval LFALSE	押されていない
*/
//------------------------------------------------------------------------------------------------
eLueBool LueInput_GetKeyData( eLueVirtualKey Key )
{
	IKeyboard *pKeyboard = Lue_GetKeyboard();

	return pKeyboard->GetKeyData( (eVirtualKeyCode)Key ) ? LTRUE : LFALSE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief マウス情報取得
	@author 葉迩倭

	@return マウスデータ

	マウスの情報を取得します。
*/
//------------------------------------------------------------------------------------------------
LueMouseData LueInput_GetMouseData( void )
{
	IMouse *pMouse = Lue_GetMouse();

	LueMouseData Mouse = {
		pMouse->GetPosX(),
		pMouse->GetPosY(),
		pMouse->GetPosW(),
		pMouse->GetMoveX(),
		pMouse->GetMoveY(),
		pMouse->GetClickL(),
		pMouse->GetClickR(),
		pMouse->GetClickW(),
		pMouse->GetDoubleClickL(),
		pMouse->GetDoubleClickR(),
		pMouse->GetDoubleClickW(),
		(eLueMouseState)pMouse->GetStateL(),
		(eLueMouseState)pMouse->GetStateR(),
		(eLueMouseState)pMouse->GetStateW(),
	};

	return Mouse;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ジョイスティック情報取得
	@author 葉迩倭

	@param No	[in] ジョイスティック番号

	@return ジョイスティックデータ

	指定接続番号のジョイスティックのデータを取得します。<BR>
	指定接続番号のジョイスティックが接続されていない場合は<BR>
	IsActive メンバ変数に LFALSE が設定されます。
*/
//------------------------------------------------------------------------------------------------
LueJoyStickData LueInput_GetJoystickData( int No )
{
	LueJoyStickData DstJoy = { LFALSE };
/*
	SJoystickData SrcJoy;
	if ( CInput::GetJoystickData( No, &SrcJoy ) )
	{
		DstJoy.IsActive		= LTRUE;
		DstJoy.Px			= SrcJoy.Px;
		DstJoy.Py			= SrcJoy.Py;
		DstJoy.Pz			= SrcJoy.Pz;
		DstJoy.Rx			= SrcJoy.Rx;
		DstJoy.Ry			= SrcJoy.Ry;
		DstJoy.Rz			= SrcJoy.Rz;
		DstJoy.Vx			= SrcJoy.Vx;
		DstJoy.Vy			= SrcJoy.Vy;
		DstJoy.Vz			= SrcJoy.Vz;
		DstJoy.VRx			= SrcJoy.VRx;
		DstJoy.VRy			= SrcJoy.VRy;
		DstJoy.VRz			= SrcJoy.VRz;
		DstJoy.Ax			= SrcJoy.Ax;
		DstJoy.Ay			= SrcJoy.Ay;
		DstJoy.Az			= SrcJoy.Az;
		DstJoy.ARx			= SrcJoy.ARx;
		DstJoy.ARy			= SrcJoy.ARy;
		DstJoy.ARz			= SrcJoy.ARz;
		DstJoy.Fx			= SrcJoy.Fx;
		DstJoy.Fy			= SrcJoy.Fy;
		DstJoy.Fz			= SrcJoy.Fz;
		DstJoy.FRx			= SrcJoy.FRx;
		DstJoy.FRy			= SrcJoy.FRy;
		DstJoy.FRz			= SrcJoy.FRz;
		DstJoy.Slider[0]	= SrcJoy.Slider[0];
		DstJoy.Slider[1]	= SrcJoy.Slider[1];
		DstJoy.Pov[0]		= SrcJoy.Pov[0];
		DstJoy.Pov[1]		= SrcJoy.Pov[1];
		DstJoy.Pov[2]		= SrcJoy.Pov[2];
		DstJoy.Pov[3]		= SrcJoy.Pov[3];
		for ( Sint32 i = 0; i < LPAD_BUTTON_MAX; i++ )
		{
			DstJoy.Button[i] = SrcJoy.Button[i];
		}
	}
*/
	return DstJoy;
}


} // extern "C"

