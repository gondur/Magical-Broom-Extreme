

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Scene/CSceneCamera.h"
#include "Math/Collision.h"

#if ENABLE_3D

//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
using namespace Selene;


//-----------------------------------------------------------------------------------
/**
	@brief コンストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CSceneCamera::CSceneCamera()
	: m_fNearClip ( 0.0f )
	, m_fFarClip  ( 0.0f )
	, m_FovAngle  ( 0 )
{
	m_mCamera.Identity();
	m_mProjection.Identity();
	m_mView.Identity();
	m_mCameraInverse.Identity();
	m_mProjectionInverse.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CSceneCamera::~CSceneCamera()
{
}

//-----------------------------------------------------------------------------------
/**
	@brief ワールド→スクリーン座標変換行列取得
	@author 葉迩倭

	@return 変換行列

	ワールド空間からスクリーン座標への逆変換行列を取得します。
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::WorldToScreen( void ) const
{
	return m_mCamera;
}

//-----------------------------------------------------------------------------------
/**
	@brief ワールド→ビュー変換行列取得
	@author 葉迩倭

	@return 変換行列

	ワールド空間からカメラ空間への逆変換行列を取得します。
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::WorldToView( void ) const
{
	return m_mView;
}

//-----------------------------------------------------------------------------------
/**
	@brief スクリーン→ワールド変換行列取得
	@author 葉迩倭

	@return 変換行列

	スクリーン座標からワールド空間への逆変換行列を取得します。
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::ScreenToWorld( void ) const
{
	return m_mCameraInverse;
}

//-----------------------------------------------------------------------------------
/**
	@brief ビュー→ワールド変換行列取得
	@author 葉迩倭

	@return 変換行列

	カメラ空間からワールド空間への逆変換行列を取得します。
*/
//-----------------------------------------------------------------------------------
const CMatrix &CSceneCamera::ViewToWorld( void ) const
{
	return m_mViewInverse;
}

const CVector3D &CSceneCamera::Position( void ) const
{
	return m_vPosition;
}

//-----------------------------------------------------------------------------------
/**
	@brief ニアクリップ値取得
	@author 葉迩倭

	@return ニアクリップ値

	ニアクリップ値を取得します。
*/
//-----------------------------------------------------------------------------------
Float CSceneCamera::GetNearClip( void ) const
{
	return m_fNearClip;
}

//-----------------------------------------------------------------------------------
/**
	@brief ファークリップ値取得
	@author 葉迩倭

	@return ファークリップ値

	ファークリップ値を取得します。
*/
//-----------------------------------------------------------------------------------
Float CSceneCamera::GetFarClip( void ) const
{
	return m_fFarClip;
}

//-----------------------------------------------------------------------------------
/**
	@brief プロジェクション行列更新
	@author 葉迩倭

	@param fNearClip	[in] ニアクリップ値
	@param fFarClip		[in] ファークリップ値
	@param FovAngle		[in] 画角（1周65536とした角度）
	@param Width		[in] 表示横幅
	@param Height		[in] 表示縦幅

	プロジェクション行列を更新します。<BR>
	カメラを使用する場合には必ずこの関数でプロジェクションを作成して下さい。<BR>
	またFovAngleに0を指定すると平行投影になります。
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )
{
	m_fNearClip = fNearClip;
	m_fFarClip  = fFarClip;
	m_FovAngle  = FovAngle;

	// 平行投影
	if ( FovAngle == 0 )
	{
		m_mProjection.Ortho( toF(Width), toF(Height), fNearClip, fFarClip );
	}
	// 透視投影
	else
	{
		m_mProjection.Perspective( FovAngle, fNearClip, fFarClip, toF(Width) / toF(Height) );
	}

	// 逆行列
	m_mProjectionInverse.Inverse( m_mProjection );
}

//-----------------------------------------------------------------------------------
/**
	@brief カメラデータ初期化
	@author 葉迩倭

	カメラデータを初期化します。<BR>
	座標(0,0,0)からZ軸+方向を向いた状態になります。
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::Reset( void )
{
	// Matrix
	m_mCamera.Identity();
	m_mCameraInverse.Identity();
	m_mView.Identity();
	m_mViewInverse.Identity();
}

//-----------------------------------------------------------------------------------
/**
	@brief カメラデータ更新
	@author 葉迩倭

	カメラのデータを更新します。<BR>
	各種行列やバウンディングボックスなどは<BR>
	この関数を呼び出すことで作成されます。
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::Update( void )
{
	// Matrix
	m_mCamera.Multiply( m_mView, m_mProjection );
	m_mCameraInverse.Multiply( m_mProjectionInverse, m_mViewInverse );

	// Update Bounding
	CVector3D vMin( -1.0f, -1.0f,  0.0f );
	CVector3D vMax( +1.0f, +1.0f, +1.0f );
	Collision::CreateBoxProjection( m_BoxOBB, vMin, vMax, m_mCameraInverse );
}

//-----------------------------------------------------------------------------------
/**
	@brief カメラを変換
	@author 葉迩倭

	@param Style	[in] カメラ変換用CStyle

	Ctyleデータで定義された変換処理を<BR>
	カメラに適用します。<BR>
	カメラで使用されるのは移動/回転になります。
*/
//-----------------------------------------------------------------------------------
void CSceneCamera::SetTransform( CStyle &Style )
{
	Style.GetTransformInverse( m_mView );
	Style.GetTransform( m_mViewInverse );

	Style.GetPosition( m_vPosition );
}

//-----------------------------------------------------------------------------------
/**
	@brief ビューフラスタムカリングカリング
	@author 葉迩倭

	@param Style	[in] カメラ変換用CStyle

	Ctyleデータで定義された変換処理を<BR>
	カメラに適用します。<BR>
	カメラで使用されるのは移動/回転になります。
*/
//-----------------------------------------------------------------------------------
Bool CSceneCamera::ViewfrustumCulling( CBox &Box )
{
	return Collision::Box_Box_3D( m_BoxOBB, Box );
}

#endif // ENABLE_3D
