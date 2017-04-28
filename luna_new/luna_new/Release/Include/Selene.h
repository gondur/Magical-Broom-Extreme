//==============================================================================//
//                         DirectX9用汎用ライブラリ Selene                        //
//==============================================================================//
//                                                                              //
//    最新版の置いてあるURL                                                     //
//                                                                              //
//    TWINTAIL LOVERS.                                                          //
//      http://www.twin-tail.jp/                                                //
//                                                                              //
//    質問等発言場所                                                            //
//      TWINTAIL LOVERS.内の掲示板                                              //
//                                                                              //
//   DirectX Library 'Selene'                                                   //
//   Copyright (C) 2006 葉迩倭                                                  //
//   All rights reserved.                                                       //
//                                                                              //
//==============================================================================//


#ifndef ___SELENE_H___
#define ___SELENE_H___


#undef _UNICODE
#define _UNICODE
#undef UNICODE
#define UNICODE

#include <stdio.h>
#include <windows.h>

#pragma inline_depth ( 255 )
#pragma inline_recursion ( on )

#pragma warning ( disable: 4819 )
#pragma warning ( disable: 4201 )

typedef char					Sint8;								///< signed char 型の別定義
typedef short					Sint16;								///< signed short 型の別定義
typedef long					Sint32;								///< signed long 型の別定義
typedef __int64					Sint64;								///< signed __int64 型の別定義
typedef unsigned char			Uint8;								///< unsigned char 型の別定義
typedef unsigned short			Uint16;								///< unsigned short 型の別定義
typedef unsigned long			Uint32;								///< unsigned long 型の別定義
typedef unsigned __int64		Uint64;								///< unsigned __int64 型の別定義
typedef float					Float;								///< Float 型の別定義
typedef float					Float32;							///< Float 型の別定義
typedef double					Float64;							///< double 型の別定義
typedef long double				Float80;							///< long double 型の別定義
typedef bool					Bool;								///< Bool 型の別定義

typedef void					*FX_HANDLE;							///< エフェクトファイルのハンドル

#define ef									else if																		///< else if 簡略用マクロ

#define toF(val)							((Float)(val))																///< Float型へのキャストマクロ
#define toI(val)							((Sint32)(val))																///< Sint32型へのキャストマクロ

#define PI									(3.141592653589793238462643383279f)											///< π
#define PI2									(6.283185307179586476925286766559f)											///< 2π
#define REV(val)							toF(1.0f/toF(val))															///< 逆数算出マクロ

#define SHADER_BONE_MAX						(48)

#define MIN(N1,N2)							((N1 < N2) ? (N1) : (N2))													///< 最小値取得マクロ
#define MAX(N1,N2)							((N1 > N2) ? (N1) : (N2))													///< 最大値取得マクロ
#define SWAP(N1,N2)							{ N1 = N2 - N1; N2 -= N1; N1 += N2; }										///< 値交換マクロ

#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }							///< COM安全解放マクロ
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }								///< newメモリ安全解放
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }							///< new[]メモリ安全解放

#define ANGLE_TABLE_BIT						(16)																		///< サインテーブルのビット数
#define ANGLE_MAX							(1 << ANGLE_TABLE_BIT)														///< サインテーブルのサイズ
#define ANGLE_TABLE_MASK					(ANGLE_MAX - 1)																///< サインテーブルのアクセス用マスク
#define NORMALIZE_ANGLE(val)				((val) & ANGLE_TABLE_MASK)													///< 角度の正規化
#define DEG_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / 360.0f)													///< 度数法から専用角度
#define PI_TO_ANGLE(val)					toI(toF(val) * toF(ANGLE_MAX) / PI2)											///< 弧度法から専用角度
#define ANGLE_TO_PI(val)					(toF(val) * PI2 / toF(ANGLE_MAX))												///< 専用角度から弧度法

#define MemoryClear(PD,S)					::FillMemory((PD),(S),0x00)													///< メモリクリア
#define MemoryFill(PD,PS,S)					::FillMemory((PD),(S),(PS))													///< メモリ塗りつぶし
#define MemoryMove(PD,PS,S)					::MoveMemory((PD),(PS),(S))													///< メモリ移動
#define MemoryCopy(PD,PS,S)					::CopyMemory((PD),(PS),(S))													///< メモリコピー

#define MemGlobalAlloc(size)				(::VirtualAlloc( NULL, ((size)+4095)&~4095, MEM_COMMIT, PAGE_READWRITE ))					///< VirtuakAllocメモリ確保マクロ
#define MemGlobalFree(pointer)				if ( (pointer) != NULL ) { ::VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }	///< VirtualAllocメモリ解放マクロ

#define MemLocalAlloc(size)					::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, size )										///< HeapAllocメモリ確保マクロ
#define MemLocalFree(pointer)				if ( (pointer) != NULL ) { ::HeapFree( ::GetProcessHeap(), 0, pointer ); (pointer) = NULL; }	///< HeapAllocメモリ解放マクロ

#ifdef LIB_SELENE
#	define SELENE_DLL_API
#else // LIB_SELENE
#	ifdef DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllexport)
#	else // DLL_SELENE
#		define SELENE_DLL_API	__declspec(dllimport)
#	endif // DLL_SELENE
#endif // LIB_SELENE

namespace Selene
{
	class ICore;
	class IGraphicCard;
	class IDevice;
	class IResourceFile;
	class IFileManager;
	class IMouse;
	class IKeyboard;
	class IRender;
	class IPostEffect;
	class IPointPrimitive2D;
	class ILinePrimitive2D;
	class IPrimitive2D;
	class ISprite2D;
	class IFontSprite2D;
	class IPointPrimitive3D;
	class ILinePrimitive3D;
	class IPrimitive3D;
	class IFrame;
	class IMesh;
	class IModel;
	class ISceneCamera;
	class ISceneManager;
	class ISound;
	class ISurface;
	class ITexture;

	class CVector2D;
	class CVector3D;
	class CVector4D;
	class CMatrix;
	class CStyle;
	class CQuaternion;
}

void SELENE_DLL_API GetVersioinInfo( wchar_t *pVersionStr, Uint32 Length );



namespace Selene
{
	/**
		@brief 色情報管理クラス
		@author 葉迩倭

		各種データの色を定義するためのクラスです。<BR>
		ライブラリ内で色を指定する場合はすべてこのクラスを使います。
	*/
	class CColor
	{
	public:
		union {
			struct {
				Uint8 b;		///< 色の青成分
				Uint8 g;		///< 色の緑成分
				Uint8 r;		///< 色の赤成分
				Uint8 a;		///< 色の透明度成分
			};
			Uint32 Color;		///< 色の32Bit整数表記
		};

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CColor()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param r		[in] 赤成分（０～２５５）
			@param g		[in] 緑成分（０～２５５）
			@param b		[in] 青成分（０～２５５）
			@param a		[in] アルファ成分（０～２５５）
		*/
		CColor( Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255 )
		{
			this->a = a;
			this->r = r;
			this->g = g;
			this->b = b;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param Color	[in] 色成分
		*/
		CColor( Uint32 Color )
		{
			this->Color = Color;
		}

		/**
			@brief オペレーター=演算子
			@author 葉迩倭
		*/
		CColor operator = ( CColor &Color )
		{
			this->a = Color.a;
			this->r = Color.r;
			this->g = Color.g;
			this->b = Color.b;

			return *this;
		}

		/**
			@brief オペレーター=演算子
			@author 葉迩倭
		*/
		CColor operator = ( Uint32 Color )
		{
			this->Color = Color;

			return *this;
		}

		/**
			@brief 型変換
			@author 葉迩倭
		*/
		operator Uint32 ()
		{
			return Color;
		}

		/**
			@brief 型変換
			@author 葉迩倭
		*/
		operator const Uint32 () const
		{
			return Color;
		}
	};
}



namespace Selene
{
namespace System
{
	/**
		@brief システム初期化
		@author 葉迩倭
		@retval true	成功
		@retval false	失敗

		Seleneシステムの初期化を行います。
	*/
	SELENE_DLL_API Bool Initialize( void );

	/**
		@brief システム終了
		@author 葉迩倭

		Seleneシステムの終了をします。
	*/
	SELENE_DLL_API void Finalize( void );

	/**
		@brief 多重起動ブロック
		@author 葉迩倭
		@param pApplicationName	[in] アプリケーション名
		@retval false	既に同名のアプリケーションが起動している
		@retval true	同名のアプリケーションは存在しない

		返り値false時にアプリケーションを終了させることで<BR>
		多重起動を防止することができます。
	*/
	SELENE_DLL_API Bool BlockDualBoot( const wchar_t *pApplicationName );

	/**
		@brief SSE2サポート有無
		@author 葉迩倭
		@retval false	SSE2をサポートしていない
		@retval true	SSE2をサポートしている

		SSE2をサポートしているかどうかを調べます。
	*/
	SELENE_DLL_API Bool IsSuportSSE( void );

	/**
		@brief カレントディレクトリリセット
		@author 葉迩倭

		カレントディレクトリをアプリケーションの実行フォルダに設定します。
	*/
	SELENE_DLL_API void ResetCurrentDirectory( void );

	/**
		@brief ディレクトリ生成
		@author 葉迩倭
		@param pPath	[in] フォルダパス

		指定パスへディレクトリを生成します。<BR>
		途中のフォルダが存在しない場合、全ての階層に対してフォルダを作成していきます。
	*/
	SELENE_DLL_API void CreateDirectory( const wchar_t *pPath );

	/**
		@brief Coreの取得
		@author 葉迩倭
		@return ICoreインターフェイス

		ウィンドウを管理するICoreクラスを生成/取得します。<BR>
		現在、１つのICoreしか生成できません。
	*/
	SELENE_DLL_API ICore *CreateCore( void );
}
}



namespace Selene
{
	/**
		@brief アニメーションタイプ定義
		@author 葉迩倭
	*/
	enum eAnimationType
	{
		ANIM_TYPE_STEP,							///< ステップ補間
		ANIM_TYPE_LINEAR,						///< 線形補間
		ANIM_TYPE_TCB,							///< ＴＣＢスプライン補間
	};

	/**
		@brief キーフレームデータ
		@author 葉迩倭
	*/
	struct SKeyFrame
	{
		Bool IsIn;								///< スプライン時のIN係数を定数にするかどうか
		Bool IsOut;								///< スプライン時のOUT係数を定数にするかどうか
		Float fTime;							///< キー時間
		Float fParam;							///< キー値
		Float fIn;								///< IN係数の定数
		Float fOut;								///< OUT係数の定数

		SKeyFrame *pPrev;						///< 前方キーフレームデータポインタ
		SKeyFrame *pNext;						///< 後方キーフレームデータポインタ
	};

	/**
		@brief アニメーションクラス
		@author 葉迩倭
	*/
	class CAnimation
	{
	private:
		Float m_fTimeFirst;						///< 開始時間
		Float m_fTimeLast;						///< 終了時間
		SKeyFrame *m_pKeys;						///< キーフレームデータポインタ
		Uint32 m_KeyMax;						///< キーフレーム数

	private:
		/**
			@brief 指定時間から最も近いキーデータを取得します
			@author 葉迩倭
			@param pKeys		[in] キーフレームデータ
			@param fTime		[in] 検索時間
			@param KeyMax		[in] キー最大数
			@return キーフレームデータポインタ

			指定時間からもっとも近いキー情報を、<BR>
			バイナリサーチで検索します。
		*/
		SKeyFrame *GetKeyData( SKeyFrame *pKeys, Float fTime, Sint32 KeyMax );

		/**
			@brief エルミート補間関数を処理します
			@author 葉迩倭
			@param fTime	[in] 時間
			@param pH1		[out] パラメーター格納先１
			@param pH2		[out] パラメーター格納先２
			@param pH3		[out] パラメーター格納先３
			@param pH4		[out] パラメーター格納先４

			エルミート補間関数を使って与えられたパラメーターから<BR>
			結果を算出します。
		*/
		void Hermite( Float fTime, Float *pH1, Float *pH2, Float *pH3, Float *pH4 );

		/**
			@brief 前方のキーの出力先のパラメータを求めます
			@author 葉迩倭
			@param pKey0	[in] 前方キーデータ
			@param pKey1	[in] 後方キーデータ
			@return 算出されたパラメーター

			指定時間に対しての直前のキーの挙動を計算します。
		*/
		Float InComing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

		/**
			@brief 後方のキーの出力先のパラメータを求めます
			@author 葉迩倭
			@param pKey0	[in] 前方キーデータ
			@param pKey1	[in] 後方キーデータ
			@return 算出されたパラメーター

			指定時間に対しての直後のキーの挙動を計算します。
		*/
		Float OutGoing( SKeyFrame *pKey0, SKeyFrame *pKey1 );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param KeyMax		[in] キー最大数
		*/
		CAnimation( Uint32 KeyMax );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CAnimation();

		/**
			@brief キーフレームデータにキーを設定します
			@author 葉迩倭
			@param KeyNo		[in] 設定先キー番号
			@param fTime		[in] 設定時間
			@param fParam		[in] 設定パラメータ
			@param IsIn			[in] 入力パラメーター指定有無
			@param IsOut		[in] 出力パラメーター指定有無
			@param fIn			[in] 入力パラメーター
			@param fOut			[in] 出力パラメーター
			@return 成功時はtrue

			指定のキーに対して、補間用のパラメーターを設定します。
		*/
		virtual Bool SetKey( Uint32 KeyNo, Float fTime, Float fParam, Bool IsIn = false, Bool IsOut = false, Float fIn = 0.0f, Float fOut = 0.0f );

		/**
			@brief 指定タイプのアニメーションで指定時間における値を取得します
			@author 葉迩倭
			@param fTime		[in] 時間
			@param Type			[in] 補間タイプ
			@param fDefault		[in] デフォルト値
			@return		補間結果値

			指定時間に対して指定タイプで補間した場合の結果を取得します。
		*/
		virtual Float GetParameter( Float fTime, eAnimationType Type, Float fDefault );
	};
}



namespace Selene
{
	/**
		@brief クリティカルセクション管理クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CCriticalSection
	{
	private:
		CRITICAL_SECTION m_CriticalSection;		///< クリティカルセクション

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CCriticalSection();

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CCriticalSection();

		/**
			@brief クリティカルセクションに入る
			@author 葉迩倭

			クリティカルセクションに入ります。
		*/
		void Enter( void );

		/**
			@brief クリティカルセクションから抜ける
			@author 葉迩倭

			クリティカルセクションから抜けます。
		*/
		void Leave( void );
	};
}



namespace Selene
{
	/**
		@brief スレッド用イベントオブジェクト
		@author 葉迩倭
	*/
	class SELENE_DLL_API CEvent
	{
	private:
		HANDLE m_EventHandle[MAXIMUM_WAIT_OBJECTS];					///< イベントハンドル
		Uint32 m_HandleCount;										///< イベント数

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
			@param IsSignal		[in] シグナル状態で初期化する場合はtrue
			@param Count		[in] イベントのカウント（MAXIMUM_WAIT_OBJECTS以下）
		*/
		CEvent( Bool IsSignal = false, Uint32 Count = 1 );

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CEvent();

		/**
			@brief 指定されたイベントをシグナル状態に設定
			@author 葉迩倭
			@param No	[in] シグナル状態するイベントの番号
		*/
		virtual void Set( Uint32 No = 0 );

		/**
			@brief 指定されたイベントを非シグナル状態に設定
			@author 葉迩倭
			@param No	[in] 非シグナル状態するイベントの番号
		*/
		virtual void Reset( Uint32 No = 0 );

		/**
			@brief 指定したイベントがシグナル状態かチェック
			@author 葉迩倭
			@param No	[in] チェックするイベントの番号
			@retval false	非シグナル状態
			@retval true	シグナル状態
		*/
		virtual Bool IsSignal( Uint32 No = 0 );

		/**
			@brief 全てのイベントがシグナル状態かチェック
			@author 葉迩倭
			@retval false	非シグナル状態
			@retval true	シグナル状態
		*/
		virtual Bool IsSignalAll( void );

		/**
			@brief シグナル状態になったイベントを取得
			@author 葉迩倭
			@param TimeOut		[in] タイムアウトms時間（-1で無限）
			@retval -1		タイムアウト
			@retval 0以上	シグナル状態になったイベント番号
		*/
		virtual Sint32 Wait( Uint32 TimeOut = -1 );
	};
}



namespace Selene
{
	/**
		@brief スレッド管理操作クラス
		@author 葉迩倭

		スレッドを操作するためのクラスです。
	*/
	class SELENE_DLL_API CThread
	{
	private:
		/**
			@brief スレッド用関数
			@author 葉迩倭
			@param pArguments	[in] CThreadのポインタ

			クラスの関数を直接は指定できないので<BR>
			staticな関数を経由して呼び出す。
		*/
		static unsigned __stdcall ThreadFunc( void* pArguments );

	private:
		HANDLE m_hThread;					///< スレッドハンドル
		Uint32 m_ThreadId;					///< スレッドID
		void *m_pData;						///< スレッドデータ伝達用ポインタ
		void (*m_pMainProc)( void* );		///< スレッド関数

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CThread();

		/**
			@brief デストラクタ
			@author 葉迩倭
		*/
		virtual ~CThread();

	public:
		/**
			@brief スレッド生成
			@author 葉迩倭
			@param pThreadFunc	[in] スレッド関数
			@param pData		[in] スレッドに引き渡すデータポインタ
			@retval false	生成失敗or既にスレッドが生成されている
			@retval true	生成完了
		*/
		virtual Bool Create( void (*pThreadFunc)( void* ), void *pData );

		/**
			@brief スレッド終了待ち
			@author 葉迩倭
			@param TimeOut		[in] 終了待ちをする時間をmsで設定します。<BR>-1を指定すると無限に待ちます。

			スレッドが終了するのを待ちます
		*/
		virtual void WaitForExit( Sint32 TimeOut );

		/**
			@brief スレッドの優先度変更
			@author 葉迩倭
			@param Priority		[in] スレッド処理の優先度

			スレッドの優先度を変更します。<BR>
			デフォルトの優先度はTHREAD_PRIORITY_NORMALです。
		*/
		virtual Bool SetPriority( Sint32 Priority );

		/**
			@brief スレッドの中断を解除
			@author 葉迩倭

			スレッドのサスペンドカウントが 1 減ります。<BR>
			カウントが 0 になった時点でスレッドの中断が解除されます。
		*/
		virtual void Resume( void );

		/**
			@brief スレッドの実行を中断
			@author 葉迩倭

			指定されたスレッドの実行が中断され、<BR>
			そのスレッドのサスペンドカウントが 1 増えます。
		*/
		virtual void Suspend( void );
	};
}



namespace Selene
{
	/**
		@brief ベクトル演算クラス
	*/
	class SELENE_DLL_API CVector2D
	{
	public:
		Float x;
		Float y;

	public:
		CVector2D();
		CVector2D( const CVector2D &v );
		CVector2D( Float fPx, Float fPy );

		void Add( CVector2D &In1, CVector2D &In2 );
		void Sub( CVector2D &In1, CVector2D &In2 );
		void Set( Float fPx, Float fPy );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector2D &In );
		void Reflect( CVector2D &In1, CVector2D &In2 );

		void Normalize( void );
		Float Cross( CVector2D &In1, CVector2D &In2 );

		void Normalize( CVector2D &In );
		Float Cross( CVector2D &In );
		void Reflect( CVector2D &In );

		void Scaling( Float sx, Float sy );
		void Translation( Float px, Float py );

		CVector2D& operator += ( const CVector2D& );
		CVector2D& operator -= ( const CVector2D& );
		CVector2D& operator *= ( Float );
		CVector2D& operator /= ( Float );

		CVector2D operator + () const;
		CVector2D operator - () const;

		CVector2D operator + ( const CVector2D& ) const;
		CVector2D operator - ( const CVector2D& ) const;
		CVector2D operator * ( Float ) const;
		CVector2D operator / ( Float ) const;
	};
}



namespace Selene
{
	/**
		@brief ベクトル演算クラス
	*/
	class SELENE_DLL_API CVector3D
	{
	public:
		Float x;
		Float y;
		Float z;

	public:
		CVector3D();
		CVector3D( const CVector3D &v );
		CVector3D( Float fPx, Float fPy, Float fPz );

		void Add( CVector3D &In1, CVector3D &In2 );
		void Sub( CVector3D &In1, CVector3D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector3D &In );

		void Normalize( void );
		void Cross( CVector3D &In1, CVector3D &In2 );
		void Reflect( CVector3D &In1, CVector3D &In2 );
		void TransformNormal( CVector3D &In1, CMatrix &In2 );
		void TransformCoord( CVector3D &In1, CMatrix &In2 );
		void TransformProjection( CVector3D &In1, CMatrix &In2 );

		void Normalize( CVector3D &In );
		void Cross( CVector3D &In );
		void Reflect( CVector3D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector3D& operator += ( const CVector3D& );
		CVector3D& operator -= ( const CVector3D& );
		CVector3D& operator *= ( Float );
		CVector3D& operator /= ( Float );

		CVector3D operator + () const;
		CVector3D operator - () const;

		CVector3D operator + ( const CVector3D& ) const;
		CVector3D operator - ( const CVector3D& ) const;
		CVector3D operator * ( Float ) const;
		CVector3D operator / ( Float ) const;
	};
}



namespace Selene
{
	/**
		@brief ベクトル演算クラス
	*/
	class SELENE_DLL_API CVector4D
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		CVector4D();
		CVector4D( const CVector3D &v );
		CVector4D( const CVector4D &v );
		CVector4D( Float fPx, Float fPy, Float fPz, Float fPw = 1.0f );

		void Add( CVector4D &In1, CVector4D &In2 );
		void Sub( CVector4D &In1, CVector4D &In2 );
		void Set( Float fPx, Float fPy, Float fPz );

		Float LengthSq( void );
		Float Length( void );
		Float Dot( CVector4D &In );

		void Normalize( void );
		void Cross( CVector4D &In1, CVector4D &In2 );
		void Reflect( CVector4D &In1, CVector4D &In2 );
		void TransformNormal( CVector4D &In1, CMatrix &In2 );
		void TransformCoord( CVector4D &In1, CMatrix &In2 );
		void TransformProjection( CVector4D &In1, CMatrix &In2 );

		void Normalize( CVector4D &In );
		void Cross( CVector4D &In );
		void Reflect( CVector4D &In );
		void TransformNormal( CMatrix &In );
		void TransformCoord( CMatrix &In );
		void TransformProjection( CMatrix &In );

		void RotationX( Sint32 Angle );
		void RotationY( Sint32 Angle );
		void RotationZ( Sint32 Angle );
		void RotationAxis( Sint32 Angle, CVector3D &Axis );
		void Scaling( Float sx, Float sy, Float sz );
		void Translation( Float px, Float py, Float pz );

		CVector4D& operator += ( const CVector4D& );
		CVector4D& operator -= ( const CVector4D& );
		CVector4D& operator *= ( Float );
		CVector4D& operator /= ( Float );

		CVector4D operator + () const;
		CVector4D operator - () const;

		CVector4D operator + ( const CVector4D& ) const;
		CVector4D operator - ( const CVector4D& ) const;
		CVector4D operator * ( Float ) const;
		CVector4D operator / ( Float ) const;
	};
}



namespace Selene
{
	struct SMatrix4x4
	{
		CVector4D x;
		CVector4D y;
		CVector4D z;
		CVector4D w;
	};

	/**
		@brief 行列クラス
	*/
	class SELENE_DLL_API CMatrix
	{
	private:
		Uint8 m_Data[sizeof(SMatrix4x4) + 16];
		SMatrix4x4 &Mtx;

	public:
		CVector4D &x;
		CVector4D &y;
		CVector4D &z;
		CVector4D &w;

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix();

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( CMatrix &Mat );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( SMatrix4x4 &Mat );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix( CQuaternion &In );

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CMatrix(
			Float _11, Float _12, Float _13, Float _14,
			Float _21, Float _22, Float _23, Float _24,
			Float _31, Float _32, Float _33, Float _34,
			Float _41, Float _42, Float _43, Float _44 );

		/**
			@brief 行列の単位化
			@author 葉迩倭
		*/
		void Identity( void );

		/**
			@brief 行列の転置化
			@author 葉迩倭
			@param In	[in] 処理元行列
		*/
		void Transpose( CMatrix &In );

		/**
			@brief 行列の逆行列化
			@author 葉迩倭
			@param In	[in] 処理元行列
		*/
		void Inverse( CMatrix &In );

		/**
			@brief 行列の合成
			@author 葉迩倭
			@param In1		[in] 合成元行列１
			@param In2		[in] 合成元行列２
		*/
		void Multiply( CMatrix &In1, CMatrix &In2 );

		/**
			@brief 行列の転置行列化
			@author 葉迩倭
		*/
		void Transpose( void );

		/**
			@brief 行列の逆行列化
			@author 葉迩倭
		*/
		void Inverse( void );

		/**
			@brief 行列の合成
			@author 葉迩倭
			@param In	[in] 合成元行列
		*/
		void Multiply( CMatrix &In );

		/**
			@brief Ｘ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationX( Sint32 Angle );

		/**
			@brief Ｙ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationY( Sint32 Angle );

		/**
			@brief Ｚ軸回転角度
			@author 葉迩倭
			@param Angle	[in] 回転角度
		*/
		void RotationZ( Sint32 Angle );

		/**
			@brief ＺＸＹ回転行列を生成
			@author 葉迩倭
			@param AngleX	[in] Ｘ軸回転角度
			@param AngleY	[in] Ｙ軸回転角度
			@param AngleZ	[in] Ｚ軸回転角度
		*/
		void RotationZXY( Sint32 AngleX, Sint32 AngleY, Sint32 AngleZ );

		/**
			@brief 任意軸回転
			@author 葉迩倭
			@param Angle	[in] 角度
			@param Axis		[in] 回転軸
		*/
		void RotationAxis( Sint32 Angle, CVector3D &Axis );

		/**
			@brief 拡大縮小行列生成
			@author 葉迩倭
			@param sx	[in] Ｘ方向拡大率
			@param sy	[in] Ｙ方向拡大率
			@param sz	[in] Ｚ方向拡大率
		*/
		void Scaling( Float sx, Float sy, Float sz );

		/**
			@brief 移動行列生成
			@author 葉迩倭
			@param px	[in] Ｘ位置
			@param py	[in] Ｙ位置
			@param pz	[in] Ｚ位置
		*/
		void Translation( Float px, Float py, Float pz );

		/**
			@brief 透視変換用行列生成
			@author 葉迩倭
			@param Fov		[in] 画角
			@param NearZ	[in] 近接クリップ面
			@param FarZ		[in] 遠方クリップ面
			@param Aspect	[in] アスペクト比（＝描画エリア横幅÷描画エリア縦幅）
		*/
		void Perspective( Sint32 Fov, Float NearZ, Float FarZ, Float Aspect );

		/**
			@brief 並行投影用行列生成
			@author 葉迩倭
			@param Width	[in] 横幅
			@param Height	[in] 縦幅
			@param NearZ	[in] 近接クリップ面
			@param FarZ		[in] 遠方クリップ面
		*/
		void Ortho( Float Width, Float Height, Float NearZ, Float FarZ );

		/**
			@brief 任意点注視行列作成
			@author 葉迩倭
			@param Eye	[in] 視点
			@param At	[in] 注視点
			@param Up	[in] 上方向
		*/
		void LookAt( CVector3D &Eye, CVector3D &At, CVector3D &Up );

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 & ();

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 & () const;

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 * ();

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		operator SMatrix4x4 * () const;

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator = ( const CMatrix &In );	

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator = ( const CQuaternion &In );

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix  operator * ( const CMatrix &In );	

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CMatrix &operator *= ( const CMatrix &In );	
	};
}


namespace Selene
{
	/**
		@brief 四元数クラス
	*/
	class SELENE_DLL_API CQuaternion
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		void Add( CQuaternion &In1, CQuaternion &In2 );
		void Sub( CQuaternion &In1, CQuaternion &In2 );
		void Mul( CQuaternion &In1, CQuaternion &In2 );
		void Lerp( CQuaternion &In0, CQuaternion &In1, Float fRate );
		void Slerp( CQuaternion &In0, CQuaternion &In1, Float fRate );

		void Add( CQuaternion &In );
		void Sub( CQuaternion &In );
		void Mul( CQuaternion &In );
		void Lerp( CQuaternion &In, Float fRate );
		void Slerp( CQuaternion &In, Float fRate );

		void Identity( void );
		Float LengthSq( void );
		Float Length( void );
		Float Dot( CQuaternion &In );
		void Conjugate( void );
	};
}



namespace Selene
{
	/**
		@brief 姿勢制御クラス
	*/
	class SELENE_DLL_API CStyle
	{
	private:
		CMatrix m_mStyle;												///< 姿勢用行列
		CMatrix m_mStyleInverse;										///< 姿勢の逆行列
		CMatrix m_mTransform;											///< 変換行列
		CMatrix m_mTransformInverse;									///< 変換行列の逆行列
		CVector3D m_vUp;												///< 上方向ベクトル
		CVector3D m_vRight;												///< 右方向ベクトル
		CVector3D m_vFront;												///< 前方向ベクトル
		CVector3D m_vPosition;											///< 位置ベクトル
		CVector3D m_vScale;												///< 拡大縮小ベクトル

	public:
		CStyle();
		CStyle( const CStyle &Style );

		virtual void TransformReset( void );
		virtual void TransformUpdate( void );

		virtual void RotationX( Sint32 Rot );
		virtual void RotationY( Sint32 Rot );
		virtual void RotationZ( Sint32 Rot );
		virtual void Pitching( Sint32 Rot );
		virtual void Heading( Sint32 Rot );
		virtual void Rolling( Sint32 Rot );
		virtual void RotationQuaternion( CQuaternion &Quat );
		virtual void Translation( Float fPx, Float fPy, Float fPz );
		virtual void Scaling( Float fSx, Float fSy, Float fSz );
		virtual void LookAt( CVector3D &vEye, CVector3D &vAt, CVector3D &vUp );
		virtual void FromMatrix( CMatrix &Mat );
		virtual Sint32 GetAngleX( void );
		virtual Sint32 GetAngleY( void );
		virtual Sint32 GetAngleZ( void );
		virtual void SetPosition( CVector3D &Pos );
		virtual void SetFront( CVector3D &Vec );
		virtual void SetRight( CVector3D &Vec );
		virtual void SetUp( CVector3D &Vec );
		virtual void GetPosition( CVector3D &Pos );
		virtual void GetFront( CVector3D &Vec );
		virtual void GetRight( CVector3D &Vec );
		virtual void GetUp( CVector3D &Vec );
		virtual void GetStyle( CMatrix &Mat );
		virtual void GetStyleInverse( CMatrix &Mat );
		virtual void GetTransform( CMatrix &Mat );
		virtual void GetTransformInverse( CMatrix &Mat );

		virtual CStyle &operator = ( const CStyle &In );
	};
}



namespace Selene
{
namespace Math
{
	/**
		@brief sin取得
		@author 葉迩倭
		@param Angle	[in] 1周65536とした角度
		@return sin値

		sin値を取得します。
	*/
	SELENE_DLL_API Float Sin( Sint32 Angle );

	/**
		@brief cos取得
		@author 葉迩倭
		@param Angle	[in] 1周65536とした角度
		@return cos値

		cos値を取得します。
	*/
	SELENE_DLL_API Float Cos( Sint32 Angle );

	/**
		@brief atan2取得
		@author 葉迩倭
		@param Dx	[in] Ｘ距離
		@param Dy	[in] Ｙ距離
		@return X-Yの成す角度

		X,Yから求められるatan2の値をSeleneの角度単位に<BR>
		あわせた値で取得します。
	*/
	SELENE_DLL_API Sint32 ATan2( Float Dx, Float Dy );
}

	/**
		@brief 矩形データ
		@author 葉迩倭
	*/
	template <typename Type>
	class CRect2D
	{
	public:
		Type x;					///< Ｘ始点座標
		Type y;					///< Ｙ始点座標
		Type w;					///< Ｘサイズ
		Type h;					///< Ｙサイズ

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRect2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ始点座標
			@param y		[in] Ｙ始点座標
			@param w		[in] Ｘサイズ
			@param h		[in] Ｙサイズ
		*/
		CRect2D( Type x, Type y, Type w, Type h )
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};

	/**
		@brief ２次元の点
		@author 葉迩倭
	*/
	template <typename Type>
	class CPoint2D
	{
	public:
		Type x;					///< Ｘ座標
		Type y;					///< Ｙ座標

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPoint2D(){}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
		*/
		CPoint2D( Type x, Type y )
		{
			this->x = x;
			this->y = y;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator + ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x + Pt.x, this->y + Py.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator - ( CPoint2D<Type> &Pt )
		{
			return CPoint2D<Type>( this->x - Pt.x, this->y - Py.y );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator * ( Type Mul )
		{
			return CPoint2D<Type>( this->x * Mul, this->y * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> operator / ( Type Div )
		{
			return CPoint2D<Type>( this->x / Div, this->y / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator += ( CPoint2D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator -= ( CPoint2D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint2D<Type> Rotate( Sint32 Angle )
		{
			Float fSin = Math::Sin( Angle );
			Float fCos = Math::Cos( Angle );

			Float fPx = (fCos * toF(this->x)) - (fSin * toF(this->y));
			Float fPy = (fSin * toF(this->x)) + (fCos * toF(this->y));

			return CPoint2D<Type>( (Type)fPx, (Type)fPy );
		}
	};

	/**
		@brief ３次元の点
	*/
	template <typename Type>
	struct CPoint3D
	{
		Type x;							///< Ｘ位置
		Type y;							///< Ｙ位置
		Type z;							///< Ｚ位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPoint3D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
		*/
		CPoint3D( Type x, Type y, Type z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator + ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x + Pt.x, this->y + Py.y, this->z + Py.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator - ( CPoint3D<Type> &Pt )
		{
			return CPoint3D<Type>( this->x - Pt.x, this->y - Py.y, this->z - Py.z );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator * ( Type Mul )
		{
			return CPoint3D<Type>( this->x * Mul, this->y * Mul, this->z * Mul );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> operator / ( Type Div )
		{
			return CPoint3D<Type>( this->x / Div, this->y / Div, this->z / Div );
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator += ( CPoint3D<Type> &Pt )
		{
			this->x += Pt.x;
			this->y += Pt.y;
			this->z += Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator -= ( CPoint3D<Type> &Pt )
		{
			this->x -= Pt.x;
			this->y -= Pt.y;
			this->z -= Pt.z;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator *= ( Type Mul )
		{
			this->x *= Mul;
			this->y *= Mul;
			this->z *= Mul;
			return *this;
		}

		/**
			@brief オペレーター
			@author 葉迩倭
		*/
		CPoint3D<Type> &operator /= ( Type Div )
		{
			this->x /= Div;
			this->y /= Div;
			this->z /= Div;
			return *this;
		}
	};

	/**
		@brief ２次元上の円
		@author 葉迩倭
	*/
	struct CCircle
	{
		CVector2D Center;				///< 円の中心
		Float Radius;					///< 円の半径

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CCircle()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param r		[in] 半径
		*/
		CCircle( Float x, Float y, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Radius = r;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CCircle( CVector2D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief ３次元上の球
		@author 葉迩倭
	*/
	struct CSphere
	{
		CVector3D Center;					///< 球の中心
		Float Radius;							///< 球の半径

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CSphere()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x		[in] Ｘ座標
			@param y		[in] Ｙ座標
			@param z		[in] Ｚ座標
			@param r		[in] 半径
		*/
		CSphere( Float x, Float y, Float z, Float r )
		{
			this->Center.x = x;
			this->Center.y = y;
			this->Center.z = z;
			this->Radius = r;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param c		[in] 中心座標
			@param r		[in] 半径
		*/
		CSphere( CVector3D &c, Float r )
		{
			this->Center = c;
			this->Radius = r;
		}
	};

	/**
		@brief ２次元の線分
		@author 葉迩倭
	*/
	struct CLine2D
	{
		CVector2D Pt0;						///< 線分始点位置
		CVector2D Pt1;						///< 線分終点位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
		*/
		CLine2D( Float x0, Float y0, Float x1, Float y1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0		[in] 線分の頂点１
			@param pt1		[in] 線分の頂点２
		*/
		CLine2D( CVector2D &pt0, CVector2D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief ２次元の多角形
		@author 葉迩倭
	*/
	struct CPolygon2D
	{
		Uint32 Count;								///< ポイント配列のポイント数
		CVector2D *pPts;						///< ポリゴンを表すためのポイント配列のポインタ

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPolygon2D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param Cnt		[in] 頂点数
			@param pPt		[in] 頂点の配列
		*/
		CPolygon2D( Uint32 Cnt, CVector2D *pPt )
		{
			this->Count = Cnt;
			this->pPts = pPt;
		}
	};

	/**
		@brief ３次元の線分
		@author 葉迩倭
	*/
	struct CLine3D
	{
		CVector3D Pt0;						///< 線分始点位置
		CVector3D Pt1;						///< 線分終点位置

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CLine3D()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param x0		[in] Ｘ座標
			@param y0		[in] Ｙ座標
			@param z0		[in] Ｚ座標
			@param x1		[in] Ｘ座標
			@param y1		[in] Ｙ座標
			@param z1		[in] Ｚ座標
		*/
		CLine3D( Float x0, Float y0, Float z0, Float x1, Float y1, Float z1 )
		{
			this->Pt0.x = x0;
			this->Pt0.y = y0;
			this->Pt0.z = z0;
			this->Pt1.x = x1;
			this->Pt1.y = y1;
			this->Pt1.z = z1;
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param pt0	[in] 線分の頂点１
			@param pt1	[in] 線分の頂点２
		*/
		CLine3D( CVector3D &pt0, CVector3D &pt1 )
		{
			this->Pt0 = pt0;
			this->Pt1 = pt1;
		}
	};

	/**
		@brief ３次元の平面
		@author 葉迩倭
	*/
	struct CPlane
	{
		Float a;							///< 一般平面方程式におけるクリップ面の a 係数
		Float b;							///< 一般平面方程式におけるクリップ面の b 係数
		Float c;							///< 一般平面方程式におけるクリップ面の c 係数
		Float d;							///< 一般平面方程式におけるクリップ面の d 係数

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CPlane()
		{
		}

		/**
			@brief コンストラクタ
			@author 葉迩倭

			@param a	[in] 一般平面方程式におけるクリップ面の a 係数
			@param b	[in] 一般平面方程式におけるクリップ面の b 係数
			@param c	[in] 一般平面方程式におけるクリップ面の c 係数
			@param d	[in] 一般平面方程式におけるクリップ面の d 係数
		*/
		CPlane( Float a, Float b, Float c, Float d )
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		/**
			@brief 法線データから生成
			@author 葉迩倭

			@param Pt		[in] 平面上の1点
			@param vNormal	[in] 平面の法線
		*/
		void FromNormal( CVector3D &Pt, CVector3D &vNormal )
		{
			CVector3D vNrm;
			vNrm.Normalize( vNormal );
			a = vNrm.x;
			b = vNrm.y;
			c = vNrm.z;
			d = -Pt.Dot( vNrm );
		};

		/**
			@brief 平面上の３点から生成
			@author 葉迩倭

			@param Pt0		[in] 平面上の1点
			@param Pt1		[in] 平面上の1点
			@param Pt2		[in] 平面上の1点
		*/
		void FromPoint( CVector3D &vPt0, CVector3D &vPt1, CVector3D &vPt2 )
		{
			CVector3D vEdge0 = vPt1 - vPt0;
			CVector3D vEdge1 = vPt2 - vPt0;
			CVector3D vNormal;
			vNormal.Cross( vEdge0, vEdge1 );
			FromNormal( vPt0, vNormal );
		}

		/**
			@brief 内積
			@author 葉迩倭

			@param Pt	[in] 任意の点

			平面と任意の点の内積をとります。
		*/
		Float Dot( CVector3D &Pt, Float w = 1.0f )
		{
			return (a * Pt.x) + (b * Pt.y) + (c * Pt.z) + (w * d);
		}
	};

	/**
		@brief ３次元上の箱
		@author 葉迩倭
	*/
	struct CBox
	{
	public:
		CVector3D Points[8];	///< 箱の各角を表す頂点データ
		CPlane Planes[6];		///< 箱の各面を表す面データ

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CBox()
		{
		}

		/**
			@brief 頂点データから平面データ生成
			@author 葉迩倭
		*/
		void Update( void )
		{
			Planes[0].FromPoint( Points[0], Points[1], Points[2] );
			Planes[1].FromPoint( Points[6], Points[5], Points[4] );
			Planes[2].FromPoint( Points[5], Points[6], Points[2] );
			Planes[3].FromPoint( Points[7], Points[4], Points[0] );
			Planes[4].FromPoint( Points[3], Points[2], Points[6] );
			Planes[5].FromPoint( Points[4], Points[5], Points[1] );
		}
	};
}



namespace Selene
{
namespace Collision
{
	Bool Point_Point( CVector2D *pPt1, CVector2D *pPt2 );
	Bool Point_Line( CVector2D *pPt, CLine2D *pLine );
	Bool Point_Rect( CVector2D *pPt, CRect2D<Float> *pRect );
	Bool Point_Circle( CVector2D *pPt, CCircle *pCir );
	Bool Point_Polygon( CVector2D *pPt, CPolygon2D *pPoly );
	Bool Rect_Rect( CRect2D<Float> *pRect1, CRect2D<Float> *pRect2 );
	Bool Rect_Circle( CRect2D<Float> *pRect, CCircle *pCir );
	Bool Rect_Line( CRect2D<Float> *pRect, CLine2D *pLine );
	Bool Rect_Polygon( CRect2D<Float> *pRect, CPolygon2D *pPoly );
	Bool Circle_Circle( CCircle *pCir1, CCircle *pCir2 );
	Bool Circle_Line( CCircle *pCir, CLine2D *pLine );
	Bool Circle_Polygon( CCircle *pCir, CPolygon2D *pPoly );
	Bool Line_Line( CLine2D *pLine1, CLine2D *pLine2 );
	Bool Line_Polygon( CLine2D *pLine, CPolygon2D *pPoly );
	Bool Polygon_Polygon( CPolygon2D *pPoly1, CPolygon2D *pPoly2 );

	Bool Point_Point_3D( CVector3D *pPt1, CVector3D *pPt2 );
	Bool Point_Sphere_3D( CVector3D *pPt, CSphere *pSph );
	Bool Point_Line_3D( CVector3D *pPt, CLine3D *pLine );
	Bool Point_Plane_3D( CVector3D *pPt, CPlane *pPlane );
	Bool Point_Box_3D( CVector3D *pPt, CBox *pBox );
	Bool Sphere_Sphere_3D( CSphere *pSph1, CSphere *pSph2 );
	Bool Sphere_Line_3D( CSphere *pSph, CLine3D *pLine );
	Bool Sphere_Plane( CSphere *pSph, CPlane *pPlane );
	Bool Sphere_Box_3D( CSphere *pSph, CBox *pBox );
	Bool Line_Plane_3D( CLine3D *pLine, CPlane *pPlane, CVector3D *pPoints, CVector3D *pPos );
	Bool Line_Box_3D( CLine3D *pLine, CBox *pBox );
	Bool Line_Triangle_3D( CLine3D* pLine, CVector3D Points[], Float *pT, Float *pU, Float *pV );
	Bool Plane_Plane_3D( CPlane *pPlane1, CPlane *pPlane2, CVector3D Points1[], CVector3D Points2[] );
	Bool Box_Box_3D( CBox &Box1, CBox &Box2 );

	void CreateBox( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );
	void CreateBoxProjection( CBox &Out, CVector3D &MinPt, CVector3D &MaxPt, CMatrix &Matrix );

	Bool EdgeIntersectsQuad( CVector3D* pEdges, CVector3D* pFacePoints, CPlane* pPlane, CVector3D *pHitPos );

	Bool LineIntersectPolygon( CVector3D *pPtTbl[], CPlane &Plane, CVector3D *pPlanePoints[], Uint32 Count );
	Bool LineIntersectPlane( CVector3D &vIntersection, CPlane &Plane, CVector3D &Pt0, CVector3D &Pt1 );
}
}



namespace Selene
{
	/**
		@brief 乱数処理クラス
		@author 葉迩倭
	*/
	class SELENE_DLL_API CRandom
	{
		enum { N = 624UL };

	private:
		Uint32 MersenneTwister[N];			///< 乱数生成用ワーク
		Sint32 MersenneTwisterCount;		///< 乱数生成用ワーク

	private:
		/**
			@brief 擬似乱数生成
			@author 葉迩倭
			@return 乱数値

			32Bit整数の擬似乱数を生成します。
		*/
		virtual Uint32 GenerateInt32( void );

	public:
		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRandom();

		/**
			@brief コンストラクタ
			@author 葉迩倭
		*/
		CRandom( Uint32 Param );

		/**
			@brief 乱数用種設定
			@author 葉迩倭
			@param Param	[in] シード値

			乱数生成の種を設定します。
		*/
		virtual void Seed( Uint32 Param );

		/**
			@brief 32Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値

			32Bit整数の乱数値を取得します。
		*/
		virtual Uint32 GetInt32( void );

		/**
			@brief 64Bit整数乱数取得
			@author 葉迩倭
			@return 乱数値

			64Bit整数の乱数値を取得します。
		*/
		virtual Uint64 GetInt64( void );

		/**
			@brief 32Bit浮動小数乱数取得
			@author 葉迩倭
			@return 乱数値

			32Bit浮動小数の乱数値を取得します。
		*/
		virtual Float GetFloat32( void );

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値

			指定範囲内の整数乱数を取得します。
		*/
		virtual Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief 指定範囲乱数取得
			@author 葉迩倭
			@param Min [in] 最小値
			@param Max [in] 最大値
			@return 乱数値

			指定範囲内の浮動小数乱数を取得します。
		*/
		virtual Float GetFloat( Float Min, Float Max );
	};
}



namespace Selene
{
	/**
		@brief デバイス管理インターフェイス
		@author 葉迩倭
	*/
	class IDevice
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )												= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)												= 0;

		/**
			@brief レンダリングターゲットクリア
			@author 葉迩倭
			@param Color	[in] クリアに使う色
			@retval false	失敗
			@retval true	成功

			設定されたレンダリングターゲットを指定された色でクリアーします。
		*/
		virtual Bool Clear( CColor Color = 0x00000000 )								= 0;

		/**
			@brief 深度バッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定された深度バッファをクリアします。<BR>
			深度バッファが存在しない場合失敗します。
		*/
		virtual Bool ClearDepth( void )												= 0;

		/**
			@brief ステンシルバッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定されたステンシルバッファをクリアします。<BR>
			ステンシルバッファが存在しない場合失敗します。
		*/
		virtual Bool ClearStencil( void )											= 0;

		/**
			@brief 深度ステンシルバッファクリア
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			設定された深度ステンシルバッファをクリアします。<BR>
			深度ステンシルバッファが存在しない場合失敗します。
		*/
		virtual Bool ClearDepthStencil( void )										= 0;

		/**
			@brief 擬似コンソール画面に文字列を描画
			@author 葉迩倭
			@param pStr	[in] 書式付文字列(printfと同じ書式)

			コンソールのprintf()と似た文字列描画処理です。<BR>
			デバッグ用に画面に文字を描画しておきたい場合等に利用してください。
		*/
		virtual void Printf( const wchar_t *pStr, ... )								= 0;

		/**
			@brief 擬似コンソール画面をクリア
			@author 葉迩倭

			擬似コンソール画面をクリアします。
		*/
		virtual void Cls( void )													= 0;

		/**
			@brief 描画領域シザリング
			@author 葉迩倭
			@param IsEnable		[in] シザリングを有効にするか否か
			@param Rect			[in] 描画領域

			指定した描画領域内にしかレンダリングされないようになります。<BR>
			ビューポートには影響を与えません。
		*/
		virtual void SetScissor( Bool IsEnable, CRect2D<Sint32> Rect )			= 0;

		/**
			@brief IRenderインターフェイス取得
			@author 葉迩倭
			@return IRenderインターフェイス

			IRenderインターフェイスを取得します。<BR>
			画面へのレンダリング処理の全てがこのインターフェイスを<BR>
			介して行われるようになっています。<BR>
			このインターフェイスは1つのIDeviceに対して1つしか存在しません。<BR>
			また不要になったIRenderインターフェイスは必ずRelease()して下さい。
		*/
		virtual IRender *CreateRender( void )										= 0;
	};
}



namespace Selene
{
	#define GRAPHIC_CARD_DEFAULT_NO		(0x00000000)					///< デフォルトのビデオカード
	#define GRAPHIC_CARD_NV_PERF_HUD	(0xFFFFFFFF)					///< NVPerfHUD専用のビデオカード

	/**
		@brief 頂点シェーダーバージョン
		@author 葉迩倭
	*/
	enum eVertexShaderVersion
	{
		VERTEXSHADER_VERSION_2_0,			///< Version 2.0
		VERTEXSHADER_VERSION_3_0,			///< Version 3.0
	};

	/**
		@brief サーフェイスフォーマット定義
		@author 葉迩倭
	*/
	enum eSurfaceFormat
	{
		FORMAT_INVALID,						///< 無効

		FORMAT_FROM_FILE,					///< ファイルから取得

		FORMAT_DEPTH16,						///< 16Bit深度バッファ
		FORMAT_DEPTH32,						///< 32Bit深度バッファ
		FORMAT_DEPTHSTENCIL,				///< ステンシル深度バッファ

		FORMAT_DXT1,						///< DXT1圧縮フォーマットテクスチャ
		FORMAT_DXT3,						///< DXT3圧縮フォーマットテクスチャ
		FORMAT_DXT5,						///< DXT5圧縮フォーマットテクスチャ

		FORMAT_BACKBUFFER,					///< バックバッファに準拠
		FORMAT_TARGET16,					///< 16Bitレンダリングターゲット
		FORMAT_TARGET32,					///< 32Bitレンダリングターゲット
		FORMAT_TARGET_HDR,					///< HDR用レンダリングターゲット
		FORMAT_TARGET_SHADOWMAP,			///< シャドウマップ用レンダリングターゲット

		FORMAT_ALPHAONLY,					///< アルファ用テクスチャ

		FORMAT_TEXTURE32,					///< 32Bitテクスチャフォーマットに準拠
		FORMAT_TEXTURE16,					///< 16Bitテクスチャフォーマットに準拠

		FORMAT_TEXTURE_2D,					///< 2D用汎用テクスチャフォーマット
		FORMAT_TEXTURE_3D,					///< 3D用汎用テクスチャフォーマット
	};

	/**
		@brief ビデオカード管理インターフェイス
		@author 葉迩倭
	*/
	class IGraphicCard
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																	= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																	= 0;

		/**
			@brief 16Bitカラーモードを使用
			@author 葉迩倭

			フルスクリーン時の画面カラーを32Bitではなく16Bitにします。<BR>
			フィルレートの厳しい環境で速度の向上が望めますが、<BR>
			マッハバンドなどの画質的な問題も出ます。
		*/
		virtual void EnableHighlColorScreen( void )														= 0;

		/**
			@brief ピクセルシェーダーがサポートされているか取得
			@author 葉迩倭
			@param Major	[in] メジャーバージョン
			@param Minor	[in] マイナーバージョン

			現在のデバイスで指定したピクセルシェーダーをサポート<BR>
			しているかどうかを取得します。
		*/
		virtual Bool GetPixelShaderSupport( Uint16 Major, Uint16 Minor )								= 0;

		/**
			@brief 画面解像度数取得
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@return 画面解像度数

			使用可能な画面解像度の数を取得できます。<BR>
			IsFullColorフラグに応じて、16Bit/32Bitカラーの画面解像度数が取得出来ます。
		*/
		virtual Sint32 GetScreenTypeCount( Bool IsFullColor )											= 0;

		/**
			@brief 画面解像度
			@author 葉迩倭
			@param IsFullColor	[in] フルカラー(32Bit)の画面解像度か否か
			@param No			[in] 画面解像度のインデックス（最大数はGetScreenTypeCount()で取得）
			@param Width		[out] 画面横幅格納先
			@param Height		[out] 画面縦幅格納先

			使用可能な画面解像度を取得します。
		*/
		virtual void GetScreenType( Bool IsFullColor, Sint32 No, Sint32 &Width, Sint32 &Height )		= 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ数取得
			@author 葉迩倭
			@return レンダリングターゲットテクスチャサイズ数

			使用可能なレンダリングターゲットテクスチャサイズの数を取得できます。
		*/
		virtual Sint32 CreateRenderTargetTextureSizeCount( void )										= 0;

		/**
			@brief レンダリングターゲットテクスチャサイズ
			@author 葉迩倭
			@param No			[in] レンダリングターゲットテクスチャサイズのインデックス（最大数はCreateRenderTargetTextureSizeCount()で取得）
			@param pWidth		[out] 画面横幅格納先
			@param pHeight		[out] 画面縦幅格納先

			使用可能なレンダリングターゲットテクスチャサイズを取得します。
		*/
		virtual void CreateRenderTargetTextureSize( Sint32 No, Sint32 *pWidth, Sint32 *pHeight )		= 0;

		/**
			@brief グラフィックカード名称取得
			@author 葉迩倭
			@param pName		[out] 名称格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードの名称を取得します。
		*/
		virtual void GetGraphicCardName( wchar_t *pName, Uint32 NameSize )									= 0;

		/**
			@brief グラフィックカードのドライバー取得
			@author 葉迩倭
			@param pName		[out] ドライバー格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードのドライバーを取得します。
		*/
		virtual void GetGraphicCardDriver( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief グラフィックカードのバージョン取得
			@author 葉迩倭
			@param pName		[out] バージョン格納先
			@param NameSize		[in] pNameのバッファサイズ

			接続されているグラフィックカードのバージョンを取得します。
		*/
		virtual void GetGraphicCardVersion( wchar_t *pName, Uint32 NameSize )								= 0;

		/**
			@brief IDeviceインターフェイス生成
			@author 葉迩倭
			@return IDeviceインターフェイス

			グラフィックカード上のデバイス制御用のIDeviceインターフェイスを取得します。<BR>
			IDeviceインターフェイスは１つのIGraphicCardに対して１つしか存在しません。
		*/
		virtual IDevice *CreateDevice( void )															= 0;
	};
}



namespace Selene
{
	/**
		@brief フレームレート定義
		@author 葉迩倭
	*/
	enum eFrameRate
	{
		FRAME_RATE_60,
		FRAME_RATE_30,
		FRAME_RATE_20,
		FRAME_RATE_15,
		FRAME_RATE_VSYNC,
	};

	/**
		@brief ウィンドウ管理インターフェイス
		@author 葉迩倭
	*/
	class ICore
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																							= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																							= 0;

		/**
			@brief コアの初期化
			@author 葉迩倭
			@param pAppName		[in] アプリケーション名
			@param FrameRate	[in] フレームレート
			@retval false	失敗
			@retval true	成功

			アプリケーションに関する初期化を行います。
		*/
		virtual Bool Initialize( const wchar_t *pAppName, eFrameRate FrameRate )														= 0;

		/**
			@brief コアの開始
			@author 葉迩倭
			@param ScreenWidth	[in] 画面横幅
			@param ScreenHeight	[in] 画面縦幅
			@param IsWindowType	[in] ウィンドウモードフラグ

			ウィンドウを作成し、アプリケーションを起動します。<BR>
			ここでの設定で起動後変更可能なものは画面モードだけです。
		*/
		virtual void Start( Uint32 ScreenWidth, Uint32 ScreenHeight, Bool IsWindowType )										= 0;

		/**
			@brief コアの終了
			@author 葉迩倭

			ウィンドウを解体し、アプリケーションを終了します。<BR>
			この関数は終了を通知するだけで、実際にはメインループ後に<BR>
			終了処理が行われます。<BR>
		*/
		virtual void Exit( void )																								= 0;

		/**
			@brief アプリケーションメイン処理
			@author 葉迩倭
			@param IsFullActive	[in] 常時動作フラグ
			@retval false	アプリケーションは終了した
			@retval true	アプリケーションは稼働中

			IsFullActiveにtrueを指定すると、<BR>
			ウィンドウがフォーカスを失っている状態でも動作し続けます。
		*/
		virtual Bool Run( Bool IsFullActive = false )																			= 0;

		/**
			@brief ウィンドウハンドル取得
			@author 葉迩倭
			@return ウィンドウのウィンドウハンドル

			ICoreの所有するウィンドウのウィンドウハンドルを取得します。
		*/
		virtual HWND GetWindowHandle( void )																					= 0;

		/**
			@brief ウィンドウハンドル取得
			@author 葉迩倭
			@return ウィンドウのウィンドウハンドル

			ICoreの所有するウィンドウのウィンドウハンドルを取得します。
		*/
		virtual void SetVirtualScreenEnable( Bool Flag )																		= 0;

		/**
			@brief 仮想画面設定
			@author 葉迩倭
			@param RealWidth		[in] 実画面の横幅
			@param RealHeight		[in] 実画面の縦幅
			@param VirtualWidth		[in] 仮想画面の横幅
			@param VirtualHeight	[in] 仮想画面の縦幅

			可変画面サイズ用の設定を行います。<BR>
			3D用に画面のサイズを自由に変えられるように作られている場合でも<BR>
			2Dの描画は仮想画面に設定された画面サイズと見立てて描画を行います。<BR>
			つまり仮想画面が(640x480)の時に(0,0)-(640,480)への全画面の2D描画を行った場合、<BR>
			実際の画面のサイズが(320x240)や(1280x960)等のサイズであっても<BR>
			全画面に自動的に拡大縮小して描画されるということです。
		*/
		virtual void SetVirtualScreenSize( Uint32 RealWidth, Uint32 RealHeight, Uint32 VirtualWidth, Uint32 VirtualHeight )		= 0;

		/**
			@brief フレーム時間を取得します。
			@author 葉迩倭
			@return フレーム時間

			前フレームの処理にかかった時間を取得します。<BR>
			このフレーム時間は1秒で1.0になるようになっています。<BR>
			可変フレームレート系のゲームを作る場合に利用してください。
		*/
		virtual Float GetFrameTime( void )																						= 0;

		/**
			@brief フレームカウントを取得します。
			@author 葉迩倭
			@return フレーム数

			起動時からの総フレーム数を取得します。
		*/
		virtual Uint32 GetSyncCount( void )																						= 0;

		/**
			@brief フレームレートを取得します。
			@author 葉迩倭
			@return フレームレート

			現在のフレームレートを取得します。
		*/
		virtual eFrameRate GetFrameRate( void )																						= 0;

		/**
			@brief グラフィックカードインターフェイスを取得
			@author 葉迩倭
			@param GraphicCardNo	[in] グラフィックカード番号
			@param VsVer			[in] 使用する頂点シェーダーのバージョン
			@return グラフィックカードインターフェイス

			グラフィックカードに関しての初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			通常GraphicCardNoにはGRAPHIC_CARD_DEFAULT_NOを指定します。<BR>
			「NV PerfHUD」のインストールされた環境では、<BR>
			GRAPHIC_CARD_NV_PERF_HUDを指定することでそれを有効に出来ます。
		*/
		virtual IGraphicCard *CreateGraphicCard( Uint32 GraphicCardNo, eVertexShaderVersion VsVer )								= 0;

		/**
			@brief マウスインターフェイスを取得
			@author 葉迩倭
			@return マウスインターフェイス

			ICoreの所有するウィンドウに関連付けられたマウスの初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			マウスに関しての情報はこのインターフェイス経由で取得して下さい。
		*/
		virtual IMouse *GetMouse( void ) const																					= 0;

		/**
			@brief キーボードインターフェイスを取得
			@author 葉迩倭
			@return キーボードインターフェイス

			ICoreの所有するウィンドウに関連付けられたキーボードの初期化を行い、<BR>
			そのインターフェイスを取得します。<BR>
			キーボードに関しての情報はこのインターフェイス経由で取得して下さい。
		*/
		virtual IKeyboard *GetKeyboard( void ) const																			= 0;

		/**
			@brief ファイルマネージャーインターフェイス生成
			@author 葉迩倭
			@return ファイルマネージャーインターフェイス

			新規のファイルマネージャーインターフェイスを生成します。<BR>
			ファイルのパスなどの設定は全てIFileManagerを経由して行います。
			取得したファイルマネージャーインターフェイスは使用終了後には必ずRelease()して下さい。。
		*/
		virtual IFileManager *CreateFileMgr( void )																				= 0;

		/**
			@brief ファイルマネージャーインターフェイス取得
			@author 葉迩倭
			@return ファイルマネージャーインターフェイス

			現在設定されているファイルマネージャーインターフェイスを取得します。<BR>
			設定済みのファイルマネージャーインターフェイスへのアクセスを行う場合に使用してください。
		*/
		virtual IFileManager *GetFileMgrPointer( void ) const																	= 0;

		/**
			@brief ファイルマネージャーインターフェイス設定
			@author 葉迩倭
			@param pMgr	[in] ファイルマネージャーインターフェイス

			ファイルの読み込みに使われるファイルマネージャーインターフェイスを設定します。<BR>
			ファイルの読み込みはこのマネージャーを経由して行うので、<BR>
			ファイルの読み込みを行う場合は必ず設定してください。<BR>
			既に設定されているマネージャーは内部で解放されます。
		*/
		virtual void SetFileManager( IFileManager *pMgr )																		= 0;

		/**
			@brief サウンドファイル読み込み
			@author 葉迩倭
			@param pFileName		[in] サウンドファイル名(wav/ogg)
			@param IsGlobalScope	[in] サウンドのスコープ
			@retval NULL		ファイル読み込みエラー
			@retval NULL以外	サウンドインターフェイスのポインタ

			ICoreの所有するウィンドウに関連付けられたサウンドを取得します。<BR>
			IsGlobalScopeにtrueを渡すと、ウィンドウのフォーカスに関係なく<BR>
			再生されます。<BR>
			使用の終了したサウンドは必ずRelease()して下さい。
		*/
		virtual ISound *CreateSoundFromFile( const wchar_t *pFileName, Bool IsGlobalScope )										= 0;
	};
}



namespace Selene
{
	/**
		@brief シーンカメラ操作用インターフェイス
		@author 葉迩倭

		シーンのカメラを操作するためのインターフェイスです。
	*/
	class ISceneCamera
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																					= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																					= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																					= 0;

		/**
			@brief ワールド→スクリーン座標変換行列取得
			@author 葉迩倭
			@return 変換行列

			ワールド空間からスクリーン座標への逆変換行列を取得します。
		*/
		virtual const CMatrix &WorldToScreen( void ) const																= 0;

		/**
			@brief ワールド→ビュー変換行列取得
			@author 葉迩倭
			@return 変換行列

			ワールド空間からカメラ空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &WorldToView( void ) const																= 0;

		/**
			@brief スクリーン→ワールド変換行列取得
			@author 葉迩倭
			@return 変換行列

			スクリーン座標からワールド空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &ScreenToWorld( void ) const																= 0;

		/**
			@brief ビュー→ワールド変換行列取得
			@author 葉迩倭
			@return 変換行列

			カメラ空間からワールド空間への逆変換行列を取得します。
		*/
		virtual const CMatrix &ViewToWorld( void ) const																= 0;

		/**
			@brief ニアクリップ値取得
			@author 葉迩倭

			@return ニアクリップ値

			ニアクリップ値を取得します。
		*/
		virtual Float GetNearClip( void ) const																			= 0;

		/**
			@brief ファークリップ値取得
			@author 葉迩倭

			@return ファークリップ値

			ファークリップ値を取得します。
		*/
		virtual Float GetFarClip( void ) const																			= 0;

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
		virtual void UpdateProjection( Float fNearClip, Float fFarClip, Sint32 FovAngle, Uint32 Width, Uint32 Height )	= 0;

		/**
			@brief カメラデータ初期化
			@author 葉迩倭

			カメラデータを初期化します。<BR>
			座標(0,0,0)からZ軸+方向を向いた状態になります。
		*/
		virtual void Reset( void )																						= 0;

		/**
			@brief カメラデータ更新
			@author 葉迩倭

			カメラのデータを更新します。<BR>
			各種行列やバウンディングボックスなどは<BR>
			この関数を呼び出すことで作成されます。
		*/
		virtual void Update( void )																						= 0;

		/**
			@brief カメラを変換
			@author 葉迩倭

			@param Style	[in] カメラ変換用CStyle

			Ctyleデータで定義された変換処理を<BR>
			カメラに適用します。<BR>
			カメラで使用されるのは移動/回転になります。
		*/
		virtual void SetTransform( CStyle &Style )																		= 0;
	};
}



namespace Selene
{
	/**
		@brief シーンレンダリングモード
		@author 葉迩倭
	*/
	enum eSceneMode
	{
		SCENE_MODE_NOT_MANAGED,			///< レンダリングしか行わない
		SCENE_MODE_MANAGED,				///< 内部で深度バッファやレンダリングターゲットを管理する
		SCENE_MODE_1PASS_DOF,			///< 1PASSで被写界深度処理を行う（アルファブレンディングはできなくなります
		SCENE_MODE_2PASS_DOF,			///< 2PASSで被写界深度処理を行う（アルファブレンディングができます
		SCENE_MODE_1PASS_DOF_HIGH,		///< 1PASSで高画質被写界深度処理を行う（アルファブレンディングはできなくなります
		SCENE_MODE_2PASS_DOF_HIGH,		///< 2PASSで高画質被写界深度処理を行う（アルファブレンディングができます
	};

	/**
		@brief シーンレンダリングモード
		@author 葉迩倭
	*/
	enum eSceneModeOption
	{
		SCENE_MODE_OPTION_NO,					///< オプションなし
		SCENE_MODE_OPTION_HDR,					///< HDRレンダリングを行います（アルファブレンディング・アルファテストはできなくなります
		SCENE_MODE_OPTION_EDGE,					///< エッジレンダリングを行います
		SCENE_MODE_OPTION_SHADOW,				///< 影のレンダリングを行います
	};

	/**
		@brief シーン管理用インターフェイス
		@author 葉迩倭

		シーン管理を行うためのインターフェイスです。
	*/
	class ISceneManager
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																								= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																								= 0;

		/**
			@brief シーンカメラ取得
			@author 葉迩倭
			@return カメラデータ

			シーンに関連付けられたカメラを取得します。
		*/
		virtual ISceneCamera *GetSceneCamera( void )																				= 0;

		/**
			@brief シーン初期化
			@author 葉迩倭

			シーンのライトやフォグなどのデータをリセットします。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void Reset( void )																									= 0;

		/**
			@brief シーン開始
			@author 葉迩倭
			@param IsSort	[in] シーン内のオブジェクトをソートするかどうか

			シーン管理を開始します。<BR>
			この時点でカメラのデータが確定しますので<BR>
			この関数を呼び出したあとのカメラの更新は全て無効です。
		*/
		virtual void Begin( Bool IsSort )																							= 0;

		/**
			@brief シーン終了
			@author 葉迩倭

			シーンの管理を完了します。
		*/
		virtual void End( void )																									= 0;

		/**
			@brief シーンレンダリング
			@author 葉迩倭
			@param IsDrawBuffer	[in] 内部用バッファの表示（デバッグ用）

			シーンの管理で構築されたシーンをレンダリングします。<BR>
			この関数をコールした段階で内部で描画処理が開始されます。<BR>
			必ずIRender::Begin()～IRender::End()間で呼び出してください。
		*/
		virtual void Rendering( Bool IsDrawBuffer = false )																			= 0;

		/**
			@brief シャドウ用カメラ設定
			@author 葉迩倭
			@param vPosition	[in] カメラ位置
			@param vTarget		[in] カメラ注視点
			@param Fov			[in] 画角（1周65536とした角度）
			@param fNear		[in] 近クリップ面
			@param fFar			[in] 遠クリップ面

			シャドウ用のカメラデータを設定します。
		*/
		virtual void SetShadowLight( CVector3D &vPosition, CVector3D &vTarget, Float fSize, Float fNear, Float fFar, Float fBias )	= 0;

		/**
			@brief フォグON/OFF
			@author 葉迩倭
			@param Enable	[in] フォグを適用する場合ON

			シーンに適用されるフォグをON/OFFします。
		*/
		virtual void SetFogEnable( Bool Enable )																					= 0;

		/**
			@brief フォグ情報設定
			@author 葉迩倭

			@param fNear	[in] フォグ開始Z（このZより前はフォグに影響されない）
			@param fFar		[in] フォグ終了Z（このZより後は完全にColorの色になる）
			@param Color	[in] フォグの色

			シーンに適用されるフォグのパラメーターを設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetFog( Float fNear, Float fFar, CColor Color )																= 0;

		/**
			@brief 被写界深度用のフォーカス位置を設定します。
			@author 葉迩倭

			@param fForcusZ	[in] フォーカスのＺ（カメラ基準）
			@param fPower	[in] 被写界深度強度

			被写界深度のフォーカス位置を設定します。
		*/
		virtual void SetDepthOfFieldForcus( Float fForcusZ, Float fPower )															= 0;

		/**
			@brief アンビエントライト設定
			@author 葉迩倭
			@param vColorSky	[in] シーン内の天球の環境光の色
			@param vColorEarth	[in] シーン内の地表の環境光の色

			シーンの環境光を設定します。<BR>
			半球ライティングを行うために、天球と地表の色を設定します。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetAmbientLight( CVector3D &vColorSky, CVector3D &vColorEarth )												= 0;

		/**
			@brief ディレクションライト設定
			@author 葉迩倭
			@param vDirect	[in] シーン内の平行光源の方向
			@param vColor	[in] シーン内の平行光源の色

			シーンに大して1つだけ平行光源を割り当てることができます。<BR>
			太陽のように遥か遠方に存在し、オブジェクトの位置によって<BR>
			光の方向が変わらないようなライトに向いています。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void SetDirectionLight( CVector3D &vDirect, CVector3D &vColor )														= 0;

		/**
			@brief ポイントライト追加
			@author 葉迩倭
			@param vPosition	[in] シーン内の点光源の位置
			@param vColor		[in] シーン内の点光源の色
			@param fDistance	[in] シー内の点光源の影響距離

			シーンに対して点光源を追加します<BR>
			最大で32個のライトを設定でき、そのうち最もオブジェクトに近い<BR>
			4つのライトがオブジェクトに適用されます。<BR>
			この関数はBegin()-End()内で呼び出すと失敗します。
		*/
		virtual void AddPointLight( CVector3D &vPosition, CVector3D &vColor, Float fDistance )										= 0;

		/**
			@brief レンダリングターゲットのサイズを設定
			@author 葉迩倭
			@param Size		[in] サイズ

			シーンのレンダリングターゲットのサイズを指定します。<BR>
			eSceneModeがSCENE_MODE_NORMAL以外の場合に使われる各種<BR>
			バッファのサイズに関係します。
		*/
		virtual CPoint2D<Uint32> SetRenderTargetSize( CPoint2D<Uint32> Size )														= 0;

		/**
			@brief レンダリングリクエスト数取得
			@author 葉迩倭
			@return レンダリングリクエスト数

			シーンにリクエストレンダリング数を取得します。
		*/
		virtual Uint32 GetRenderingRequestCount( void )																				= 0;

		/**
			@brief レンダリング数取得
			@author 葉迩倭
			@return レンダリング数

			シーンで実行されたレンダリング数を取得します。<BR>
			2Pass系の処理等もカウントされるので、<BR>
			リクエスト数以上の値になることもあります。
		*/
		virtual Uint32 GetRenderingCount( void )																					= 0;

		/**
			@brief レンダリングピクセル数取得
			@author 葉迩倭
			@return レンダリングピクセル数

			レンダリングしたモデルのレンダリングピクセル数を取得します。<BR>
			サポートされていないビデオカードの場合は0xFFFFFFFFが返ります。
		*/
		virtual Uint32 GetOcculusion( Uint32 Index )																				= 0;
	};
}



namespace Selene
{
	/**
		@brief テクスチャステージ定義
		@author 葉迩倭

		テクスチャステージに関しての定義です。<BR>
		3Dオブジェクトに関しては基本的にシェーダー内で<BR>
		UVを計算するようになっているので、<BR>
		頂点データとして保持するUVはカラーマップとライトマップだけです。
	*/
	enum
	{
		TEXTURE_STAGE_00			= 0,	///< テクスチャステージ０
		TEXTURE_STAGE_01,					///< テクスチャステージ１
		TEXTURE_STAGE_02,					///< テクスチャステージ２
		TEXTURE_STAGE_03,					///< テクスチャステージ３
		TEXTURE_STAGE_04,					///< テクスチャステージ４
		TEXTURE_STAGE_05,					///< テクスチャステージ５
		TEXTURE_STAGE_06,					///< テクスチャステージ６
		TEXTURE_STAGE_07,					///< テクスチャステージ７
		TEXTURE_STAGE_MAX,					///< テクスチャステージ最大数

		MESH_TEXTURE_COLORMAP		= 0,	///< メッシュ用カラーマップ
		MESH_TEXTURE_LIGHTMAP,				///< ライトマップ（現在使われていません
		MESH_TEXTURE_NORMALMAP,				///< バンプor視差マップ用法線マップ
		MESH_TEXTURE_SHADOWMAP,				///< シャドウマップ
		MESH_TEXTURE_MAX,					///< 3Dモデル用UV数
	};

	/**
		@brief マルチテクスチャ演算タイプ
		@author 葉迩倭

		マルチテクスチャ使用時のステージ毎の演算方法を定義します。
	*/
	enum eTextureOperationType
	{
		TEXTURE_OP_NONE,				///< 以下ステージ無効
		TEXTURE_OP_MUL,					///< Color = [下位ステージ]×[テクスチャ]
		TEXTURE_OP_ADD,					///< Color = [下位ステージ]＋[テクスチャ]
		TEXTURE_OP_SUB,					///< Color = [下位ステージ]－[テクスチャ]
	};

	/**
		@brief 頂点定義
		@author 葉迩倭

		頂点定義クラスの作成時に指定するフラグです。<BR>
		なお VERTEX_ELEMENT_PRIMITIVE、VERTEX_ELEMENT_SPRITE、VERTEX_ELEMENT_3DBASE は<BR>
		独立しており排他です。
	*/
	enum eVertexElement
	{
		VERTEX_ELEMENT_PRIMITIVE	= 1 << 0,			///< 位置と色だけを含む最も単純な2D用頂点
		VERTEX_ELEMENT_SPRITE		= 1 << 1,			///< 位置と色とテクスチャUVを含む2D用頂点
		VERTEX_ELEMENT_3DBASE		= 1 << 2,			///< 位置と色を含むもっとも単純な3D頂点
		VERTEX_ELEMENT_3DTEXTURE	= 1 << 3,			///< テクスチャUVを含む基本的な3D用頂点
		VERTEX_ELEMENT_3DLIGHT		= 1 << 4,			///< ライティングに関する法線を含む3D頂点
		VERTEX_ELEMENT_3DBUMP		= 1 << 5,			///< バンプマップに関する接線を含む3D頂点
		VERTEX_ELEMENT_3DANIMATION	= 1 << 6,			///< スキニングに関するボーンのインデックス＆ウェイトを含む3D頂点
	};

	/**
		@brief 描画タイプ定義
		@author 葉迩倭

		各種描画タイプに関しての定義です。
	*/
	enum eDrawType
	{
		DRAW_TYPE_NORMAL,					///< 通常描画
		DRAW_TYPE_BLEND,					///< 半透明描画
		DRAW_TYPE_ADD,						///< 加算描画
		DRAW_TYPE_ADD_NOALPHA,				///< 加算描画（アルファ値無効）
		DRAW_TYPE_SUB,						///< 減算描画（アルファ値無効）
		DRAW_TYPE_SUB_NOALPHA,				///< 減算描画（アルファ値無効）
		DRAW_TYPE_MULTIPLE,					///< 乗算描画
		DRAW_TYPE_SCREEN,					///< スクリーン描画
	};

	/**
		@brief カリングタイプ定義
		@author 葉迩倭

		ポリゴンの表裏に描画に関しての定義です。
	*/
	enum eCullType
	{
		CULL_FRONT,							///< 表の場合のみ描画
		CULL_BACK,							///< 裏の場合のみ描画
		CULL_NONE,							///< 裏表両面描画
	};

	/**
		@brief カリングタイプ定義
		@author 葉迩倭

		ポリゴンの表裏に描画に関しての定義です。
	*/
	enum eTextureFilterType
	{
		TEXTURE_FILTER_DISABLE,				///< フィルタリング無し
		TEXTURE_FILTER_BILINEAR,			///< バイリニアフィルタリング
		TEXTURE_FILTER_ANISOTROPY_LOW,		///< 異方性フィルタリング/低画質
		TEXTURE_FILTER_ANISOTROPY_HIGH,		///< 異方性フィルタリング/高画質
	};

	/**
		@brief テクスチャサンプリング方法
		@author 葉迩倭

		0.0～1.0以外の範囲を指定した場合の挙動に関しての定義です。<BR>
		Seleneでは２の累乗以外のサイズのテクスチャもドライバが<BR>
		対応していれば作成・利用する事が可能です。<BR>
		ただし２の累乗以外のサイズのテクスチャを利用する場合は、<BR>
		TEXTURE_ADDRESS_CLAMP を指定していなければなりません。
	*/
	enum eTextureAddressType
	{
		TEXTURE_ADDRESS_REPEAT,				///< UVがテクスチャの範囲外の時、繰り返します。
		TEXTURE_ADDRESS_CLAMP,				///< UVがテクスチャの範囲外の時、(0、テクスチャサイズ）に制限します。
	};

	/**
		@brief 2D描画用頂点
		@author 葉迩倭

		2D描画用の基本頂点データです。<BR>
		主にIPointPrimitive2D/ILinePrimitive2D<BR>
		クラスで使用します。<BR>
		VERTEX_ELEMENT_PRIMITIVEフラグを指定して作成した<BR>
		頂点定義ではこの構造体を使います。
	*/
	struct SVertex2D
	{
		CVector4D Pos;		///< 位置
		CColor Col;			///< 頂点色
	};

	/**
		@brief 2D描画用頂点
		@author 葉迩倭

		2D描画用のテクスチャUV付き頂点データです。<BR>
		主にIPrimitive2D/ISprite2D/IFontSprite2D<BR>
		クラスで使用します。<BR>
		VERTEX_ELEMENT_SPRITEフラグを指定して作成した<BR>
		頂点定義ではこの構造体を使います。
	*/
	struct SVertex2DTex
	{
		CVector4D Pos;		///< 位置
		CColor Col;			///< 頂点色
		CVector2D Tex;		///< テクスチャUV
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用の基本頂点データです。<BR>
		VERTEX_ELEMENT_BASEフラグを指定して作成した<BR>
		頂点定義に対しては１つ目の構造体としてこの構造体が<BR>
		定義されます。
	*/
	struct SVertex3DBase
	{
		CVector3D Pos;		///< 位置
		CColor Col;			///< 頂点色
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のテクスチャUV用頂点データです。<BR>
		VERTEX_ELEMENT_3DTEXTUREフラグを指定して作成した<BR>
		頂点定義に対しては１つ目の構造体としてこの構造体が<BR>
		定義されます。
	*/
	struct SVertex3DTexture
	{
		CVector2D TexColor;		///< テクスチャUV
		CVector2D TexLight;		///< テクスチャUV
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のライティング用頂点データです。<BR>
		VERTEX_ELEMENT_3DLIGHTフラグを指定して作成した<BR>
		頂点定義に対しては２つ目の構造体としてこの構造体が<BR>
		定義されます。
	*/
	struct SVertex3DLight
	{
		CVector3D Norm;		///< 法線
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のバンプマッピング用頂点データです。<BR>
		VERTEX_ELEMENT_3DBUMPフラグを指定して作成した<BR>
		頂点定義に対しては３つ目の構造体としてこの構造体が<BR>
		定義されます。
	*/
	struct SVertex3DBump
	{
		CVector3D Tangent;	///< 接線
	};

	/**
		@brief 3D描画用頂点
		@author 葉迩倭

		3D描画用のスキニング用頂点データです。<BR>
		VERTEX_ELEMENT_3DANIMATIONフラグを指定して作成した<BR>
		頂点定義に対しては４つ目の構造体としてこの構造体が<BR>
		定義されます。<BR>
		１つの頂点につき２つのボーンの計算が行われます。
	*/
	struct SVertex3DAnimation
	{
		Float Weight;		///< ウェイト（１番目のウェイトだけを指定、２番目はシェーダー内で1.0-Weightで算出）
		Uint8 Index[4];		///< ボーンインデックス
	};

	/**
		@brief テクスチャ生成用コンフィグ
		@author 葉迩倭

		テクスチャ生成時に参照される<BR>
		作成用パラメーターが定義されるクラスです。
	*/
	class CTextureConfig
	{
	private:
		CColor m_KeyColor;			///< カラーキーの色
		eSurfaceFormat m_Format;	///< サーフェイスフォーマット

	public:
		/**
			@brief カラーキー（透明色）設定
			@author 葉迩倭
			@param Col	[in] カラーキー（透明色）に使う色<BR>0x00000000の時カラーキー（透明色）OFF

			テクスチャを読み込んだ際に指定した色のアルファを0にし、<BR>
			カラーキー処理を行ったようにそのピクセルを描画<BR>
			されないようにします。
		*/
		void SetColorKey( CColor Col )
		{
			m_KeyColor = Col;
		}

		/**
			@brief サーフェイスフォーマット設定
			@author 葉迩倭
			@param Fmt	[in] サーフェイスフォーマット

			テクスチャ読み込み時のサーフェイスフォーマットを設定します。<BR>
			無効なフォーマットを指定した場合、作成は失敗します。
		*/
		void SetFormat( eSurfaceFormat Fmt )
		{
			m_Format = Fmt;
		}

		/**
			@brief カラーキーを取得
			@author 葉迩倭
			@retval	0		カラーキー処理を行わない
			@retval	0以外	その色をカラーキーとする
		*/
		CColor GetColorKey( void )
		{
			return m_KeyColor;
		}

		/**
			@brief サーフェイスフォーマットを取得します
			@author 葉迩倭
			@return サーフェイスフォーマット
		*/
		eSurfaceFormat GetFormat( void )
		{
			return m_Format;
		}
	};

	/**
		@brief レンダラーインターフェイス
		@author 葉迩倭

		画面に対する全ての描画処理を管理します。<BR>
		描画用の各種クラスも全てこのクラスから取得します<BR>
		またこのインターフェイスは1つのIDeviceインターフェイスに対して1つしか作成されません。
	*/
	class IRender
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																																					= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																																					= 0;

		/**
			@brief テクスチャ設定
			@author 葉迩倭
			@param Stage	[in] 設定するステージ（０～７）
			@param pTex		[in] 設定するテクスチャ（NULLで無効化）
			@retval false	失敗
			@retval true	成功

			テクスチャをレンダラーに設定します。<BR>
			一度設定されたテクスチャはNULLを設定するまで<BR>
			有効になっています。
		*/
		virtual Bool SetTexture( Uint32 Stage, ITexture *pTex )																															= 0;

		/**
			@brief レンダリングターゲット設定
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターゲットをバックバッファに戻します。
		*/
		virtual Bool ResetRenderTarget( void )																																			= 0;

		/**
			@brief レンダリングターゲット設定
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターゲットとして設定します。<BR>
			CreateRenderTarget()で生成されたテクスチャ以外は失敗します。
		*/
		virtual Bool SetRenderTarget( ITexture *pTexture )																																= 0;

		/**
			@brief レンダリングターゲットに設定
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗

			サーフェイスをレンダリングターゲットとして設定します。<BR>
			レンダリングターゲットとして生成されたサーフェイスでない場合は<BR>
			この関数は失敗します。
		*/
		virtual Bool SetRenderTarget( ISurface *pSurface )																																= 0;

		/**
			@brief レンダリングターゲット取得
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターゲットを取得します。
		*/
		virtual Bool GetRenderTarget( ITexture **ppTexture )																															= 0;

		/**
			@brief レンダリングターゲット取得
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗

			レンダリングターゲットを取得します。
		*/
		virtual Bool GetRenderTarget( ISurface **ppSurface )																															= 0;

		/**
			@brief 深度ステンシルバッファに設定
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗

			サーフェイスを深度ステンシルサーフェイスとして設定します。<BR>
			深度ステンシルサーフェイスとして生成されたサーフェイスでない場合は<BR>
			この関数は失敗します。
		*/
		virtual Bool SetDepthStencil( ISurface *pSurface )																																= 0;

		/**
			@brief レンダリング処理開始通知
			@author 葉迩倭

			レンダラーに対してこれからレンダリング処理を<BR>
			開始するという事を通知します。
		*/
		virtual void Begin( void )																																						= 0;

		/**
			@brief レンダリング処理終了通知
			@author 葉迩倭

			レンダラーに対してこれでレンダリング処理を<BR>
			終了するということを通知します。
		*/
		virtual void End( void )																																						= 0;

		/**
			@brief ポストエフェクト管理インターフェイス生成
			@author 葉迩倭
			@return ポストエフェクト管理インターフェイス

			ポストエフェクト管理用のインターフェイスを生成します。<BR>
			テクスチャを使ったポストエフェクトに関する処理は全てこのインターフェイスを介します。
		*/
		virtual IPostEffect *CreatePostEffect( void )																																	= 0;

		/**
			@brief シーン管理インターフェイス生成
			@author 葉迩倭
			@return シーン管理インターフェイス

			シーン管理用のインターフェイスを生成します。<BR>
			3Dに関するレンダリング処理は全てこのインターフェイスを介します。
		*/
		virtual ISceneManager *CreateSceneManager( eSceneMode Mode = SCENE_MODE_MANAGED, eSceneModeOption Option = SCENE_MODE_OPTION_NO )												= 0;

		/**
			@brief 2Dポイントプリミティブインターフェイス生成
			@author 葉迩倭
			@param PointMax	[in] 内部バッファ格納可能ポイント数
			@return 2Dポイントプリミティブインターフェイス

			2Dの点描画用のインターフェイスを生成します。<BR>
			画面に点を打つ場合はこのインターフェイスを使います。
		*/
		virtual IPointPrimitive2D *CreatePointPrimitive2D( Uint32 PointMax )																											= 0;

		/**
			@brief 2Dラインプリミティブインターフェイス生成
			@author 葉迩倭
			@param LineMax	[in] 内部バッファ格納可能ライン数
			@return 2Dラインプリミティブインターフェイス

			2Dの点描画用のインターフェイスを生成します。<BR>
			画面に線を引く場合はこのインターフェイスを使います。
		*/
		virtual ILinePrimitive2D *CreateLinePrimitive2D( Uint32 LineMax )																												= 0;

		/**
			@brief 2Dポリゴンプリミティブインターフェイス生成
			@author 葉迩倭
			@param PrimitiveMax	[in] 内部バッファ格納可能頂点数（通常１つの三角形に三頂点消費する）
			@return 2Dポリゴンプリミティブインターフェイス

			2Dのポリゴン（三角形）を描画するためのインターフェイスを生成します。<BR>
			最小単位である三角形ごとの描画を行う場合はこのインターフェイスを使います。
		*/
		virtual IPrimitive2D *CreatePrimitive2D( Uint32 PrimitiveMax )																													= 0;

		/**
			@brief 2Dスプライトインターフェイス生成
			@author 葉迩倭
			@param PrimitiveMax	[in] 内部バッファ格納可能頂点数（通常１つの三角形に三頂点消費する）
			@param pTexture		[in] スプライトに関連付けるテクスチャインターフェイス
			@return 2Dスプライトインターフェイス

			2Dのスプライトを描画するためのインターフェイスを生成します。<BR>
			IPrimitive2Dを継承しており、内部的にはIPrimitive2Dでの描画を行っています。<BR>
			テクスチャを使った最も簡単なスプライト描画が可能なインターフェイスです。
		*/
		virtual ISprite2D *CreateSprite2D( Uint32 PrimitiveMax, ITexture *pTexture )																									= 0;

		/**
			@brief 2D用フォントスプライトインターフェイス生成
			@author 葉迩倭
			@param pBuffer		[in] 描画利用文字列（ここで指定した文字を画像として展開し使えるようにします）
			@param FontMax		[in] 最大フォント数（内部の頂点バッファ数）
			@param pFontFace	[in] フォント書体
			@param FontSize		[in] フォントサイズ
			@param IsItalic		[in] 斜体フォントON/OFF
			@param IsBold		[in] 太字フォントON/OFF
			@param IsAntialias	[in] アンチエイリアスフォントON/OFF
			@return 2Dフォントスプライトインターフェイス

			2Dのフォントスプライトを描画するためのインターフェイスを生成します。<BR>
			ISprite2Dを利用しており、内部的にはISprite2Dでの描画を行っています。<BR>
			テクスチャに事前に文字を画像として展開しておくことで、高速に文字列の<BR>
			描画を行うことが可能です。
		*/
		virtual IFontSprite2D *CreateFontSprite2D( const wchar_t *pBuffer, Uint32 FontMax, const wchar_t *pFontFace, Uint32 FontSize, Bool IsItalic, Bool IsBold, Bool IsAntialias )	= 0;

		/**
			@brief 2D用フォントスプライトインターフェイス生成
			@author 葉迩倭
			@param pFileName	[in] フォントスプライト用定義ファイル
			@param pExt			[in] フォントスプライト用画像ファイル拡張子
			@param FontMax		[in] 最大フォント数（内部の頂点バッファ数）
			@return 2Dフォントスプライトインターフェイス

			2Dのフォントスプライトを描画するためのインターフェイスを生成します。<BR>
			ISprite2Dを利用しており、内部的にはISprite2Dでの描画を行っています。<BR>
			FontUtilityで生成した定義ファイルとテクスチャを使って、高速に文字列の<BR>
			描画を行うことが可能です。
		*/
		virtual IFontSprite2D *CreateFontSprite2DFromFile( const wchar_t *pFileName, const wchar_t *pExt, Uint32 FontMax )																= 0;

		/**
			@brief 3Dポイントプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax	[in] ポイントの最大数
			@param IsDynamic	[in] ダイナミックバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dポイントプリミティブインターフェイス

			3Dのポイント描画用のインターフェイスを生成します。<BR>
			位置及び色データのみで、テクスチャやライトなどの不可効果をつけることは出来ません。
		*/
		virtual IPointPrimitive3D *CreatePointPrimitive3D( Uint32 VertexMax, Bool IsDynamic )																							= 0;

		/**
			@brief 3Dラインプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax	[in] ラインの最大数
			@param IsDynamic	[in] ダイナミックバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dラインプリミティブインターフェイス

			3Dのライン描画用のインターフェイスを生成します。<BR>
			位置及び色データのみで、テクスチャやライトなどの不可効果をつけることは出来ません。
		*/
		virtual ILinePrimitive3D *CreateLinePrimitive3D( Uint32 VertexMax, Bool IsDynamic )																								= 0;

		/**
			@brief 3Dポリゴンプリミティブインターフェイス生成
			@author 葉迩倭
			@param VertexMax	[in] 内部頂点バッファの最大数
			@param IndexMax		[in] 内部インデックスバッファの最大数
			@param VertexFlag	[in] 頂点データフラグ（eVertexElementの組み合わせ）
			@param IsDynamic		[in] ダイナミックバッファの使用ON/OFF（頻繁に書き換える場合はtrueにして下さい）
			@return 3Dポリゴンプリミティブインターフェイス

			3Dのポリゴン（三角形）を描画するためのインターフェイスを生成します。<BR>
			最小単位である三角形ごとの描画を行う場合はこのインターフェイスを使います。<BR>
			またインデックスを使用した効率的な描画をサポートします。<BR>
			VertexFlagは頂点のフォーマットを指定するもので eVertexElement 列挙型の中から<BR>
			VERTEX_ELEMENT_PRIMITIVE と VERTEX_ELEMENT_SPRITE を除いたものを指定します。<BR>
			複数組み合わせる場合は | 演算子で指定してください。<BR>
			利用されるシェーダーは内部で作成された固定シェーダーが利用されます。<BR>
			現在のバージョンではバンプマップに関する処理は行われません。<BR>
			<BR>
			（例）法線を持ちライティング可能な頂点 -> VERTEX_ELEMENT_3DTEXTURE | VERTEX_ELEMENT_3DLIGHT
		*/
		virtual IPrimitive3D *CreatePrimitive3D( Uint32 VertexMax, Uint32 IndexMax, Uint32 VertexFlag, Bool IsDynamic )																	= 0;

		/**
			@brief モデルをファイルから生成
			@author 葉迩倭
			@param pFileName	[in] モデル名

			SMF形式のモデルファイルを読み込みます。<BR>
			SMFファイルはConvertX2SMFを使うことでXファイルから生成できます。
		*/
		virtual IModel *CreateModelFromFile( const wchar_t *pFileName )																													= 0;

		/**
			@brief モデルをメモリから生成
			@author 葉迩倭
			@param pData	[in] モデルデータ
			@param Size		[in] データサイズ

			SMF形式のモデルデータを読み込みます。<BR>
			SMFファイルはConvertX2SMFを使うことでXファイルから生成できます。
		*/
		virtual IModel *CreateModelFromMemory( const Uint8 *pData, Uint32 Size )																										= 0;

		/**
			@brief デバイスからサーフェイスを生成
			@author 葉迩倭
			@param Width	[in] サーフェイスの横幅
			@param Height	[in] サーフェイスの縦幅
			@param Format	[in] サーフェイスのフォーマット
			@return サーフェイスインターフェイス
		*/
		virtual ISurface *CreateDepthStencilSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format )																				= 0;

		/**
			@brief デバイスからサーフェイスを生成
			@author 葉迩倭
			@param Width		[in] サーフェイスの横幅
			@param Height		[in] サーフェイスの縦幅
			@param Format		[in] サーフェイスのフォーマット
			@param pCopyTarget	[in] Copy使用時のコピー先のサーフェイス（フォーマット変換機能のチェック用）
			@return サーフェイスインターフェイス
		*/
		virtual ISurface *CreateRenderTargetSurface( Uint32 Width, Uint32 Height, eSurfaceFormat Format, ISurface *pCopyTarget )														= 0;

		/**
			@brief テクスチャ読み込み用コンフィグデータを取得
			@author 葉迩倭
			@return テクスチャコンフィグデータ
		*/
		virtual CTextureConfig &GetTextureConfig( void )																																= 0;

		/**
			@brief テクスチャ読み込み用コンフィグデータ設定
			@author 葉迩倭
			@param Conf		[in] テクスチャコンフィグデータ
		*/
		virtual void SetTextureConfig( CTextureConfig &Conf )																															= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param Width	[in] テクスチャの横幅
			@param Height	[in] テクスチャの縦幅
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTexture( Uint32 Width, Uint32 Height )																													= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromFile( const wchar_t *pFileName )																												= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pData	[in] データのポインタ
			@param Size		[in] データサイズ
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromMemory( void *pData, Uint32 Size )																											= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param Width	[in] テクスチャの横幅
			@param Height	[in] テクスチャの縦幅
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureRenderTarget( Uint32 Width, Uint32 Height )																										= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@param fHeight	[in] 法線マップの高さ倍率
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromFileForNormalMap( const wchar_t *pFileName, Float fHeight )																					= 0;

		/**
			@brief デバイスからテクスチャを生成
			@author 葉迩倭
			@param pData	[in] データのポインタ
			@param Size		[in] データサイズ
			@param fHeight	[in] 法線マップの高さ倍率
			@return テクスチャインターフェイス
		*/
		virtual ITexture *CreateTextureFromMemoryForNormalMap( const void *pData, Uint32 Size, Float fHeight )																			= 0;

		/**
			@brief 描画タイプ設定
			@author 葉迩倭
			@param Type		[in] 描画タイプ

			ポリゴンの描画タイプを設定します。
		*/
		virtual void SetDrawType( eDrawType Type )																																		= 0;

		/**
			@brief 表裏判定タイプ設定
			@author 葉迩倭
			@param Type		[in] 表裏判定タイプ

			ポリゴンの表裏判定タイプを設定します。
		*/
		virtual void SetCullType( eCullType Type )																																		= 0;

		/**
			@brief フィルタリングタイプ設定
			@author 葉迩倭
			@param Stage	[in] 設定ステージ
			@param Type		[in] フィルタリングタイプ

			テクスチャステージ毎のフィルタリングタイプを設定します。<BR>
			TEXTURE_FILTER_ANISOTROPY系 のフィルタがサポートされないハードウェアでは<BR>
			TEXTURE_FILTER_BILINEAR が使われます。
		*/
		virtual void SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )																													= 0;

		/**
			@brief テクスチャアドレッシングタイプ設定
			@author 葉迩倭
			@param Stage	[in] 設定ステージ
			@param Type		[in] アドレッシングタイプ

			テクスチャステージ毎のテクスチャアドレッシングタイプを設定します。<BR>
			0.0～1.0の範囲外のUVを指定した時にどの様な処理を行うかを指定します。
		*/
		virtual void SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )																									= 0;

		/**
			@brief テクスチャオペレーションタイプ設定
			@author 葉迩倭
			@param Stage	[in] 設定ステージ
			@param Type		[in] オペレーションタイプ

			テクスチャステージ毎のテクスチャカラーオペレーションタイプを設定します。<BR>
			下位ステージとの合成方法の処理を指定します。
		*/
		virtual void SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )																								= 0;

		/**
			@brief 深度テストON/OFF設定
			@author 葉迩倭
			@param Flag		[in] 深度テストON/OFF

			深度テストのON/OFFを設定します。
		*/
		virtual void SetDepthTestEnable( Bool Flag )																																	= 0;

		/**
			@brief 深度バッファ書き込みON/OFF設定
			@author 葉迩倭
			@param Flag		[in] 深度バッファ書き込みON/OFF

			深度バッファ書き込みのON/OFFを設定します。
		*/
		virtual void SetDepthWriteEnable( Bool Flag )																																	= 0;

		/**
			@brief アルファテストON/OFF設定
			@author 葉迩倭
			@param Flag		[in] アルファテストON/OFF

			アルファテストのON/OFFを設定します。
		*/
		virtual void SetAlphaTestEnable( Bool Flag )																																	= 0;

		/**
			@brief ステートの設定をスタックに退避します
			@author 葉迩倭
			@retval false	スタックオーバーフロー
			@retval true	エラー無し

			現在のステートをスタックに退避させます。<BR>
			この関数によって退避されるステートは以下の関数で設定したものです。<BR>
			・void SetDrawType( eDrawType Type )<BR>
			・void SetCullType( eCullType Type )<BR>
			・void SetTextureFilterType( Uint32 Stage, eTextureFilterType Type )<BR>
			・void SetTextureAddressType( Uint32 Stage, eTextureAddressType Type )<BR>
			・void SetFogEnable( Bool Flag )<BR>
			・void SetFogColor( CColor Color )<BR>
			・void SetDepthTestEnable( Bool Flag )<BR>
			・void SetDepthWriteEnable( Bool Flag )<BR>
			・void SetAlphaTestEnable( Bool Flag )<BR>
			・void SetTextureOperationType( Uint32 Stage, eTextureOperationType Type )<BR>
			・Bool SetTexture( Uint32 Stage, ITexture *pTex )
		*/
		virtual Bool StatePush( void )																																					= 0;

		/**
			@brief ステートの設定をスタックから復帰します
			@author 葉迩倭
			@retval false	スタックオーバーフロー
			@retval true	エラー無し

			現在のステートをスタックに退避去れているステートに戻します。
		*/
		virtual Bool StatePop( void )																																					= 0;

		/**
			@brief ステートの設定を初期状態にリセットします
			@author 葉迩倭

			現在のステートをスタックに退避去れているステートに戻します。<BR>
			・SetDrawType( DRAW_TYPE_NORMAL )<BR>
			・SetDrawType( DRAW_TYPE_NORMAL )<BR>
			・SetCullType( CULL_FRONT )<BR>
			・SetFogEnable( false )<BR>
			・SetFogColor( 0x00000000 )<BR>
			・SetDepthTestEnable( false )<BR>
			・SetDepthWriteEnable( false )<BR>
			・void SetAlphaTestEnable( true )<BR>
			・SetTextureFilterType( <Stage>, TEXTURE_FILTER_DISABLE )<BR>
			・SetTextureAddressType( <Stage>, TEXTURE_ADDRESS_REPEAT )<BR>
			・SetTextureOperationType( <Stage>, <Stage>==0?TEXTURE_OP_MUL:TEXTURE_OP_NONE )<BR>
			・SetTexture( <Stage>, NULL )
		*/
		virtual void StateInit( void )																																					= 0;
	};
}



namespace Selene
{
	/**
		@brief ポストエフェクトインターフェイス
		@author 葉迩倭
	*/
	class IPostEffect
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																																			= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																																			= 0;

		/**
			@brief テクスチャを使った矩形レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			単純な矩形をテクスチャ対応でレンダリングします。
		*/
		virtual void SingleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																	= 0;

		/**
			@brief マルチテクスチャを使った矩形レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param SrcTbl		[in] テクスチャUV矩形
			@param TypeTbl		[in] ステージ毎の演算タイプ
			@param pTexTbl		[in] テクスチャ
			@param StageCount	[in] 利用するステージ数

			単純な矩形をマルチテクスチャ対応でレンダリングします。<BR>
			2D描画におけるマルチテクスチャ用途は主にポストエフェクトなので<BR>
			その部分に特化した機能として実装してあります。
		*/
		virtual void MultipleTexture( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> SrcTbl[], eTextureOperationType TypeTbl[], ITexture *pTexTbl[], Uint32 StageCount )		= 0;

		/**
			@brief グレイスケール化レンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ
			@param fRate		[in] 適用度(0.0～1.0)

			カラー画像をグレースケール化します。<BR>
			fRate引数によって、段階的にグレースケール化する事が可能です。<BR>
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Grayscale( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex, Float fRate )																= 0;

		/**
			@brief ユニバーサルトランジションレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param fRate		[in] 合成レート(0.0～1.0)
			@param SrcBase		[in] ベーステクスチャUV矩形
			@param pBaseTex		[in] ベーステクスチャインターフェイス
			@param SrcRule		[in] ルールテクスチャUV矩形
			@param pRuleTex		[in] ルールテクスチャインターフェイス

			グレースケールのルール画像を用いてユニバーサルトランジションを行います。<BR>
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void UniversalTransition( CRect2D<Sint32> &Dst, Float fRate, CRect2D<Sint32> &SrcBase, ITexture *pBaseTex, CRect2D<Sint32> &SrcRule, ITexture *pRuleTex )			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			3x3ボックスフィルタで画像をぼかします。
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Blur9Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			4x4ボックスフィルタで画像をぼかします。
			ピクセルシェーダー1.1をサポートしないビデオカードの場合<BR>
			SingleTexture()に置き換えられます。
		*/
		virtual void Blur16Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;

		/**
			@brief 画像をぼかしてレンダリング
			@author 葉迩倭
			@param Dst			[in] 描画先矩形
			@param Color		[in] 描画色
			@param Src			[in] テクスチャUV矩形
			@param pTex			[in] テクスチャ

			8x8ボックスフィルタで画像をぼかします。<BR>
			ピクセルシェーダー2.0をサポートしないビデオカードの場合<BR>
			Blur16Box()に置き換えられます。
		*/
		virtual void Blur64Box( CRect2D<Sint32> &Dst, CColor Color, CRect2D<Sint32> &Src, ITexture *pTex )																			= 0;
	};
}



namespace Selene
{
	/**
		@brief 2Dポイントプリミティブ管理インターフェイス
		@author 葉迩倭
	*/
	class IPointPrimitive2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )							= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )							= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )							= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )								= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )								= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPoint	[in] 頂点データ
			@param Count	[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SVertex2D *pPoint, Uint32 Count )	= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )							= 0;
	};
}



namespace Selene
{
	/**
		@brief ラインプリミティブ用頂点データ
@author 葉迩倭
	*/
	struct SLineVertex2D
	{
		SVertex2D v1;
		SVertex2D v2;
	};

	/**
		@brief 2Dラインプリミティブ管理インターフェイス
		@author 葉迩倭
	*/
	class ILinePrimitive2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )									= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )									= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pLine	[in] ラインデータ
			@param Count	[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SLineVertex2D *pLine, Uint32 Count )		= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )								= 0;
	};
}



namespace Selene
{
	/**
		@brief プリミティブ用頂点データ
		@author 葉迩倭
	*/
	struct SPrimitiveVertex2D
	{
		SVertex2DTex v1;
		SVertex2DTex v2;
		SVertex2DTex v3;
	};

	/**
		@brief 2Dプリミティブ管理インターフェイス
		@author 葉迩倭
	*/
	class IPrimitive2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )																														= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPrimitive	[in] プリミティブデータ
			@param Count		[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief 四角形描画
			@author 葉迩倭
			@param DstRect	[in] 描画矩形データ
			@param Color	[in] 描画色

			単純な四角形を描画します。
		*/
		virtual void Square( CRect2D<Sint32> &DstRect, CColor Color )																					= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭
			@param DstRect	[in] 描画矩形データ
			@param Color	[in] 描画色
			@param Angle	[in] 1周を65536とした回転角度

			回転付きの四角形を描画します。
		*/
		virtual void SquareRotate( CRect2D<Sint32> &DstRect, CColor Color, Sint32 Angle )																= 0;

		/**
			@brief 多角形描画
			@author 葉迩倭
			@param Pos		[in] 中心位置
			@param fRadius	[in] 描画半径
			@param Color	[in] 描画色
			@param Num		[in] 角数

			単純な多角形を描画します。
		*/
		virtual void Polygon( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num )															= 0;

		/**
			@brief 回転付き多角形描画
			@author 葉迩倭
			@param Pos		[in] 中心位置
			@param fRadius	[in] 描画半径
			@param Color	[in] 描画色
			@param Num		[in] 角数
			@param Angle	[in] 1周を65536とした回転角度

			回転付き多角形を描画します。
		*/
		virtual void PolygonRotate( CPoint2D<Sint32> Pos, Float fRadius, CColor Color, Sint32 Num, Sint32 Angle )										= 0;

		/**
			@brief リング状描画
			@author 葉迩倭
			@param Pos			[in] 中心位置
			@param fInRadius	[in] 内周半径
			@param fOutRadius	[in] 外周半径
			@param InColor		[in] 内周描画色
			@param OutColor		[in] 外周描画色
			@param Num			[in] 角数

			リング状ポリゴンを描画します。
		*/
		virtual void Ring( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num )						= 0;

		/**
			@brief 回転付きリング状描画
			@author 葉迩倭
			@param Pos			[in] 中心位置
			@param fInRadius	[in] 内周半径
			@param fOutRadius	[in] 外周半径
			@param InColor		[in] 内周描画色
			@param OutColor		[in] 外周描画色
			@param Num			[in] 角数
			@param Angle	[in] 1周を65536とした回転角度

			回転付きリング状ポリゴンを描画します。
		*/
		virtual void RingRotate( CPoint2D<Sint32> Pos, Float fInRadius, Float fOutRadius, CColor InColor, CColor OutColor, Sint32 Num, Sint32 Angle )	= 0;
	};
}



namespace Selene
{
	/**
		@brief 2Dスプライト管理インターフェイス
		@author 葉迩倭
	*/
	class ISprite2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																													= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																													= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )																														= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )																														= 0;

		/**
			@brief 内部バッファへデータ追加
			@author 葉迩倭
			@param pPrimitive	[in] プリミティブデータ
			@param Count		[in] 追加数

			内部バッファのデータの追加を行います。<BR>
			この関数を呼び出す前に必ずBeing関数でデータ追加の開始を宣言して下さい。
		*/
		virtual Bool Push( SPrimitiveVertex2D *pPrimitive, Uint32 Count )																				= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )																													= 0;

		/**
			@brief 四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色

			最も単純なスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquare( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color )														= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param DstRect		[in] 転送先スクリーンの矩形
			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Color		[in] 頂点色
			@param Angle		[in] 1周65536とした回転角度

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawSquareRotate( CRect2D<Sint32> &DstRect, CRect2D<Sint32> &SrcRect, CColor Color, Uint32 Angle )									= 0;

		/**
			@brief 回転付き四角形描画
			@author 葉迩倭

			@param Pos		[in] 描画位置の配列
			@param Width	[in] 頂点ごとの幅の配列
			@param Angle	[in] 1周65536とした回転角度の配列
			@param Color	[in] 描画色の配列
			@param Count	[in] 各要素の配列数
			@param Src		[in] 転送元テクスチャの矩形

			回転付きスプライトを描画することが出来ます。<BR>
			この関数はデータを描画バッファに追加するだけで<BR>
			実際のレンダリング処理はRendering関数呼び出し時に開始されます。
		*/
		virtual void DrawList( CPoint2D<Float> Pos[], Float Width[], Sint32 Angle[], CColor Color[], Sint32 Count, CRect2D<Sint32> &Src )				= 0;

		/**
			@brief 放射状フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			中心に向かってフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )													= 0;

		/**
			@brief 円状回転フェード
			@author 葉迩倭

			@param SrcRect		[in] 転送元テクスチャの矩形
			@param Divide		[in] 円周のポリゴンの分割数
			@param Side			[in] １辺あたりのポリゴンの分割数
			@param Alpha		[in] 透明度

			時計回りにフェードするエフェクトです。<BR>
			画面の切り替え時などに利用できると思います。
		*/
		virtual void CircleRoundFade( CRect2D<Sint32> &SrcRect, Sint32 Divide, Sint32 Side, Sint32 Alpha )												= 0;
	};
}



namespace Selene
{
	/**
		@brief フォントスプライト管理インターフェイス
		@author 葉迩倭
	*/
	class IFontSprite2D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																			= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																			= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																			= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )																				= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )																				= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容のレンダリングを行います。
		*/
		virtual void Rendering( void )																			= 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色

			等幅フォントで文字列の描画を行います。<BR>
			生成時の書体が等幅フォントでない場合は正しく描画されない事があります。
		*/
		virtual void DrawString( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief 文字列描画
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@param Color	[in] 描画色

			プロポーショナルフォントで文字列の描画を行います。<BR>
			生成時の書体がプロポーショナルフォントでなくても正しく描画されます。
		*/
		virtual void DrawStringP( const wchar_t *pStr, CPoint2D<Sint32> Pos, CColor Color )						= 0;

		/**
			@brief 文字描画
			@author 葉迩倭
			@param Chara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色

			指定位置に文字を描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawChara( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color )						= 0;

		/**
			@brief 回転付き文字描画
			@author 葉迩倭
			@param Chara	[in] 描画文字
			@param Dst		[in] 描画矩形
			@param Color	[in] 描画色
			@param Angle	[in] 1周を65536とした回転角度

			指定位置に文字を回転付きで描画します。<BR>
			この関数では文字の拡大縮小をサポートします。
		*/
		virtual Sint32 DrawCharaRotate( const wchar_t Chara, CRect2D<Sint32> &Dst, CColor Color, Sint32 Angle )	= 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@return		描画完了時の座標

			等幅フォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual CPoint2D<Sint32> GetStringLastPos( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;

		/**
			@brief 文字列描画完了位置取得
			@author 葉迩倭
			@param pStr		[in] 描画文字列
			@param Pos		[in] 描画座標
			@return		描画完了時の座標

			プロポーショナルフォントで文字列の描画を行った場合の最終的な描画終了位置を取得します。<BR>
			改行が含まれる場合は改行を考慮した最終位置を返すので、<BR>
			文字列の最大幅を取得したい場合は注意してください。
		*/
		virtual CPoint2D<Sint32> GetStringLastPosP( const wchar_t *pStr, CPoint2D<Sint32> Pos )					= 0;
	};
}



namespace Selene
{
	/**
		@brief 3Dポイントプリミティブ描画クラス
		@author 葉迩倭
	*/
	class IPointPrimitive3D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭
			@return シーン内の識別番号

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual Sint32 Rendering( void )									= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pPoint		[in] ポイントデータ
			@param PointCount	[in] ポイント数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			生成時に指定した頂点フォーマットに適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBase *pPoint, Uint32 PointCount )		= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )											= 0;

		/**
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief マテリアル色設定
			@author 葉迩倭
			@param Color	[in] マテリアルの色

			マテリアルの色を設定します。
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}



namespace Selene
{
	/**
		@brief 3Dプリミティブ基本データ
		@author 葉迩倭

		ILinePrimitive3Dで描画を行う際に使用する頂点データ。
	*/
	struct SPrimitive3DVertexLine
	{
		SVertex3DBase v1;			///< 位置・頂点色
		SVertex3DBase v2;			///< 位置・頂点色
	};

	/**
		@brief 3Dラインプリミティブ描画クラス
		@author 葉迩倭
	*/
	class ILinePrimitive3D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭
			@return シーン内の識別番号

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pLine		[in] ラインデータ
			@param LineCount	[in] ライン数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			生成時に指定した頂点フォーマットに適合した頂点データを設定してください。
		*/
		virtual Bool Push( SPrimitive3DVertexLine *pLine, Uint32 LineCount )		= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )											= 0;

		/**
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief マテリアル色設定
			@author 葉迩倭
			@param Color	[in] マテリアルの色

			マテリアルの色を設定します。
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;
	};
}



namespace Selene
{
	/**
		@brief 3Dプリミティブ描画クラス
		@author 葉迩倭

		ポリゴンデータを自分で作るときに使用するためのクラスです。<BR>
		作成時にフラグで指定した頂点データとインデックスデータを<BR>
		プログラムでバッファに追加していきレンダリングします。<BR>
		ライティングやスキニングなどの機能がサポートされていますが、<BR>
		バンプマッピングはサポートされていません。<BR>
	<BR>
		また現行のバージョンでは内部で所持しているシェーダーでしか<BR>
		レンダリングをする事ができません。<BR>
		この制限は修正予定です。
	*/
	class IPrimitive3D
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭
			@return シーン内の識別番号

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual Sint32 Rendering( void )										= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBase *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DTexture *pVtx, Uint32 Count )	= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DLight *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DBump *pVtx, Uint32 Count )		= 0;

		/**
			@brief 頂点データを追加
			@author 葉迩倭
			@param pVtx		[in] 頂点データ
			@param Count	[in] 頂点数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへ頂点データを追加します。<BR>
			適合した頂点データを設定してください。
		*/
		virtual Bool Push( SVertex3DAnimation *pVtx, Uint32 Count )	= 0;

		/**
			@brief インデックスデータを追加
			@author 葉迩倭
			@param pIndex		[in] インデックスデータ
			@param IndexCount	[in] インデックス数
			@retval false	追加できなかった（バッファーオーバーフロー）
			@retval true	追加できた

			内部バッファへインデックスデータを追加します。<BR>
			生成時に指定したインデックスフォーマットに適合したインデックスデータを設定してください。
		*/
		virtual Bool Push( Uint16 *pIndex, Uint32 IndexCount )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DBase &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DTexture &Vtx, Uint32 Index )		= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DLight &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DBump &Vtx, Uint32 Index )			= 0;

		/**
			@brief 頂点データを取得
			@author 葉迩倭
			@param Vtx		[in] 取得する頂点データ
			@param Index	[in] 取得する頂点インデックス
			@retval false	取得できなかった（インデックスが範囲外）
			@retval true	取得できた

			内部バッファの頂点データを取得します。
		*/
		virtual Bool Get( SVertex3DAnimation &Vtx, Uint32 Index )		= 0;

		/**
			@brief 頂点数取得
			@author 葉迩倭
			@return 追加要求をした頂点の数

			追加要求を行ったSVertex3DBase頂点の数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Uint32 GetVertexCount( void )								= 0;

		/**
			@brief インデックス数取得
			@author 葉迩倭
			@return 追加要求をしたインデックスの数

			追加要求を行ったインデックスの数を取得します。<BR>
			この値は実際に追加された数ではなく、Pushを行って追加された数を<BR>
			取得するので、実際に持てる最大数以上の数を返す場合があります。
		*/
		virtual Uint32 GetIndexCount( void )								= 0;

		/**
			@brief データ追加開始宣言
			@author 葉迩倭

			内部バッファへのデータの追加を行うことを通知します。<BR>
			この関数を呼ばずにPush*系の関数を呼ばないようにしてください。
		*/
		virtual void Begin( void )											= 0;

		/**
			@brief データ追加終了宣言
			@author 葉迩倭

			内部バッファへのデータの追加を完了したことを通知します。<BR>
			この関数を呼ぶ前に必ずBegin関数を呼ぶようにしてください。
		*/
		virtual void End( void )											= 0;

		/**
			@brief ボーン数設定
			@author 葉迩倭
			@param BoneCount	[in] ボーン数

			レンダリングに使われるボーンの数を設定します。
		*/
		virtual void SetBoneCount( Sint32 BoneCount )						= 0;

		/**
			@brief オフセット用ボーン設定
			@author 葉迩倭
			@param No		[in] ボーン番号
			@param Matrix	[in] オフセット行列

			指定番号のボーンの親からのオフセット用の行列を設定します。
		*/
		virtual void SetBoneOffsetMatrix( Uint32 No, CMatrix &Matrix )		= 0;

		/**
			@brief トランスフォーム用ボーン設定
			@author 葉迩倭
			@param No		[in] ボーン番号
			@param Matrix	[in] トランスフォーム行列

			指定番号のボーンのトランスフォーム用の行列を設定します。
		*/
		virtual void SetBoneTransformMatrix( Uint32 No, CMatrix &Matrix )	= 0;

		/**
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief マテリアル色設定
			@author 葉迩倭
			@param Color	[in] マテリアルの色

			マテリアルの色を設定します。
		*/
		virtual void SetMaterialColor( CColor Color )						= 0;

		/**
			@brief スペキュラ色設定
			@author 葉迩倭
			@param Color	[in] スペキュラの色

			スペキュラの色を設定します。
		*/
		virtual void SetSpecularColor( CColor Color )						= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param fRefractive		[in] スペキュラの屈折率(初期20.0f)

			マテリアルのスペキュラの屈折率を設定します
		*/
		virtual void SetSpecularRefractive( Float fRefractive )				= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param fRoughly			[in] スペキュラの粗さ(初期0.5f)

			マテリアルのスペキュラの粗さを設定します
		*/
		virtual void SetSpecularRoughly( Float fRoughly )					= 0;
	};
}



namespace Selene
{
	class IMesh
	{
	public:
		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )													= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)													= 0;

		/**
			@brief 鏡面反射用モデルに変換
			@author 葉迩倭

			この関数を呼び出すと事で鏡面反射を有効化出来ます。<BR>
			平行光源に対しての単純なフォン鏡面反射が適用されるようになります。
		*/
		virtual void ConvertReflexMesh( void )											= 0;

		/**
			@brief バンプマップ用モデルに変換
			@author 葉迩倭
			@param pTexNormal	[in] バンプ用法線マップ

			この関数を呼び出すと事でバンプマップを有効化出来ます。<BR>
			ただし以下の条件を満たしている必要があります。<BR>
			・テクスチャUVデータを持っている<BR>
			・法線・接線データを持っている<BR>
			<BR>
			通常ConvertX2SMFで作成した場合は元のXファイルにテクスチャが含まれて入れば、<BR>
			上記のデータは含まれています。<BR>
			またこのとき指定するテクスチャは法線マップである必要があります。<BR>
			法線マップはIRender::CreateTextureFromFileForNormalMap()か
			IRender::CreateTextureFromMemoryForNormalMap()関数で作成できます。
		*/
		virtual void ConvertBumpMesh( ITexture *pTexNormal )								= 0;

		/**
			@brief 視差マップ用モデルに変換
			@author 葉迩倭
			@param pTexNormal		[in] バンプ用法線マップ
			@param fParallaxDepth	[in] 視差深度（だいたい0.01～0.05程度）

			この関数を呼び出すと事で視差マップを有効化出来ます。<BR>
			ただし以下の条件を満たしている必要があります。<BR>
			・テクスチャUVデータを持っている<BR>
			・法線・接線データを持っている<BR>
			<BR>
			通常ConvertX2SMFで作成した場合は元のXファイルにテクスチャが含まれて入れば、<BR>
			上記のデータは含まれています。<BR>
			法線マップはIRender::CreateTextureFromFileForNormalMap()か
			IRender::CreateTextureFromMemoryForNormalMap()関数で作成できます。
		*/
		virtual void ConvertParallaxMesh( ITexture *pTexNormal, Float fParallaxDepth )	= 0;

		/**
			@brief マテリアルの数を取得
			@author 葉迩倭
			@return マテリアル数

			メッシュが所持するマテリアルの数を取得します
		*/
		virtual Uint32 GetMaterialCount( void )											= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param Color			[in] スペキュラの色

			マテリアルごとのスペキュラの色を設定します
		*/
		virtual void SetSpecularColor( Uint32 MaterialIndex, CColor Color )				= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param fRefractive		[in] スペキュラの屈折率(初期20.0f)

			マテリアルごとのスペキュラの屈折率を設定します
		*/
		virtual void SetSpecularRefractive( Uint32 MaterialIndex, Float fRefractive )	= 0;

		/**
			@brief スペキュラ設定
			@author 葉迩倭
			@param MaterialIndex	[in] マテリアル番号
			@param fRoughly			[in] スペキュラの粗さ(初期0.5f)

			マテリアルごとのスペキュラの粗さを設定します
		*/
		virtual void SetSpecularRoughly( Uint32 MaterialIndex, Float fRoughly )			= 0;

		/**
			@brief 法線データの可視化をします
			@author 葉迩倭
			@param fLength	[in] 長さ

			メッシュの法線・接線・従法線データを可視化させることができます。
		*/
		virtual void NormalVisible( Float fLength )										= 0;

		/**
			@brief バウンディングデータの可視化をします
			@author 葉迩倭

			メッシュのバウンディングボックスを可視化させることができます。
		*/
		virtual void BoundingVisible( void )											= 0;

		/**
			@brief レンダリングID取得
			@author 葉迩倭

			レンダリング時のシーンIDを取得します。
		*/
		virtual Sint32 GetRenderID( void )												= 0;
	};
}



namespace Selene
{
	class IFrame
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;
	};
}



namespace Selene
{
	class IModel
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )										= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )										= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)										= 0;

		/**
			@brief 座標変換用姿勢データ設定
			@author 葉迩倭
			@param Style	[in] 姿勢データ

			座標変換用の姿勢データを設定します。
		*/
		virtual void SetTransform( CStyle &Style )							= 0;

		/**
			@brief 内部バッファのレンダリング
			@author 葉迩倭

			内部バッファの内容をシーンマネージャーに対してレンダリングリクエストをします。<BR>
			実際のレンダリング処理はシーンマネージャー内で行われます。<BR>
			そのため、この関数はレンダリング処理を待たずに戻ってきます。
		*/
		virtual void Rendering( void )										= 0;

		/**
			@brief フレームデータ取得
			@author 葉迩倭
			@param FrameIndex	[in] フレーム番号
			@param pFrame		[in] フレーム格納先

			モデル内のフレームデータを取得します。<BR>
			取得したフレームは不要になったらRelease()してください。
		*/
		virtual Bool GetFrame( Uint32 FrameIndex, IFrame *&pFrame )			= 0;

		/**
			@brief フレーム数取得
			@author 葉迩倭
			@return フレーム数

			モデル内のフレーム数を取得します。
		*/
		virtual Uint32 GetFrameCount( void )								= 0;

		/**
			@brief メッシュデータ取得
			@author 葉迩倭
			@param MeshIndex	[in] メッシュ番号
			@param pMesh		[in] メッシュ格納先

			モデル内のメッシュデータを取得します。<BR>
			取得したメッシュは不要になったらRelease()してください。
		*/
		virtual Bool GetMesh( Uint32 MeshIndex, IMesh *&pMesh )				= 0;

		/**
			@brief メッシュ数取得
			@author 葉迩倭
			@return メッシュ数

			モデル内のメッシュ数を取得します。
		*/
		virtual Uint32 GetMeshCount( void )									= 0;
	};
}



namespace Selene
{
	/**
		@brief テクスチャインターフェイス
		@author 葉迩倭

		テクスチャを操作するためのインターフェイスです。<BR>
		IRenderインターフェイスから取得できます。
	*/
	class ITexture
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )																		= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )																		= 0;

		/**
			@brief 矩形コピー
			@author 葉迩倭
			@param pDstRect		[in] 転送先テクスチャの矩形
			@param pSrcTex		[in] 転送元テクスチャ
			@param pSrcRect		[in] 転送元テクスチャの矩形
			@param IsUvToTexel	[in] テクスチャサイズとイメージサイズが一致しない場合の補正をするか否か
			@retval true	成功
			@retval false	失敗

			テクスチャ同士の拡大縮小コピーを行います。<BR>
			テクスチャ間でフォーマットが異なる場合は<BR>
			ハードウェアのフォーマット変換のサポートがないと<BR>
			この関数は失敗します。<BR>
			またこのコピー処理にはいくつかの制限が存在します。<BR>
			・通常テクスチャから通常テクスチャの拡大縮小コピーはできません。<BR>
			・バックバッファから通常テクスチャへのコピーはできません。
		*/
		virtual Bool Copy( RECT *pDstRect, ITexture *pSrcTex, RECT *pSrcRect, Bool IsUvToTexel = false )	= 0;

		/**
			@brief レンダリングターゲットをダウンロード
			@author 葉迩倭
			@retval false	失敗
			@retval true	成功

			レンダリングターサーフェイス<BR>
			現在のレンダリングターゲットの内容をコピーします。
		*/
		virtual Bool DownloadRenderTarget( void )															= 0;

		/**
			@brief テクスチャ更新
			@author 葉迩倭

			バックアップ用システムメモリマテリアルの内容を<BR>
			VRAM上のマテリアルへ転送します。
		*/
		virtual void UpdateTexture( void )																	= 0;

		/**
			@brief 画像ファイルとして保存
			@author 葉迩倭
			@param pFileName	[in] テクスチャファイル名
			@retval false	失敗
			@retval true	成功

			テクスチャの内容をTGA画像ファイルとして保存します。
		*/
		virtual Bool SaveToTGA( const wchar_t *pFileName )													= 0;

		/**
			@brief 実テクスチャサイズ取得
			@author 葉迩倭
			@return テクスチャの実サイズ

			テクスチャのサイズを取得します。<BR>
			２の累乗でないテクスチャを作成した際に<BR>
			デバイスがそのサイズをさぽーとしていないときは<BR>
			内包できる大きさの２の累乗のサイズになっています。
		*/
		virtual CPoint2D<Uint32> GetSize( void )															= 0;
	};
}



namespace Selene
{
	/**
		@brief マテリアルインターフェイス
		@author 葉迩倭

		サーフェイスフェイス操作するためのインターフェイスです。<BR>
		IRenderインターフェイスから取得できます。
	*/
	class ISurface
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )											= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )											= 0;

		/**
			@brief バックバッファにコピー
			@author 葉迩倭
			@retval true	成功
			@retval false	失敗

			サーフェイスフェイスバックバッファにコピーします。<BR>
			ただし深度ステンシルマテリアルやフォーマット変換にハードウェアが<BR>
			対応していないフォーマットのマテリアルでは失敗します。
		*/
		virtual Bool CopyToBackBuffer( void )									= 0;

		/**
			@brief マテリアルのコピー
			@author 葉迩倭
			@param pDstRect		[in] 転送先マテリアルの矩形
			@param pSrc			[in] 転送元マテリアル
			@param pSrcRect		[in] 転送元マテリアルの矩形
			@retval true	成功
			@retval false	失敗

			マテリアル同士の拡大縮小コピーを行います。<BR>
			マテリアル間でフォーマットが異なる場合は<BR>
			ハードウェアのフォーマット変換のサポートがないと<BR>
			この関数は失敗します。<BR>
			またこのコピー処理にはいくつかの制限が存在します。<BR>
			・通常マテリアルから通常マテリアルの拡大縮小コピーはできません。<BR>
			・バックバッファから通常マテリアルへのコピーはできません。
		*/
		virtual Bool Copy( RECT *pDstRect, ISurface *pSrc, RECT *pSrcRect )		= 0;
	};
}



namespace Selene
{
	/**
		@brief ファイルシーク定義
		@author 葉迩倭
	*/
	enum eSeekFlag
	{
		SEEK_FILE_CURRENT,					///< カレント位置
		SEEK_FILE_START,					///< 先頭位置
		SEEK_FILE_END,						///< 終端位置
	};

	/**
		@brief ファイル管理クラス
		@author 葉迩倭
	*/
	class IFileManager
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )																		= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)																		= 0;

		/**
			@brief ファイルロードパス設定
			@author 葉迩倭
			@param Priority		[in] 検索プライオリティ
			@param pRootPath	[in] ルートディレクトリ
			@param pPackFile	[in] パックファイル名

			ファイルの読み込みを行うルートのディレクトリを設定します。<BR>
			ここで設定されたパスおよびパックファイルは同列に扱われます。<BR>
			つまりプログラムの変更なく双方にまったく同じようにアクセス可能です。
		*/
		virtual void SetLoadPath( Uint32 Priority, const wchar_t *pRootPath, const wchar_t *pPackFile )		= 0;

		/**
			@brief カレントディレクトリ設定
			@author 葉迩倭
			@param pCurrentDir	[in] ディレクトリ名

			ファイル検索を行う際のカレントのディレクトリを設定します。<BR>
			ここで設定されたディレクトリをルートとしてファイルの検索を行います。
		*/
		virtual void SetCurrentDirectory( wchar_t *pCurrentDir )											= 0;

		/**
			@brief ファイルロード
			@author 葉迩倭
			@param pFile	[in] ファイル名
			@param ppData	[out] ファイルデータ格納先
			@param pSize	[out] ファイルサイズ格納先
			@retval true	成功
			@retval false	失敗

			ファイルをロードします。<BR>
			SetLoadPath() で指定されている[フォルダ]→[パックファイル]の<BR>
			順にファイルを検索します。
		*/
		virtual Bool Load( const wchar_t *pFile, void **ppData, Uint32 *pSize )								= 0;

		/**
			@brief データ解放
			@author 葉迩倭
			@param pData	[in] データ

			Load()関数で取得したデータをメモリから解放します。<BR>
			この関数を使った方法以外での解放は環境依存するため、<BR>
			正しく解放されない可能性があります。
		*/
		virtual void Free( void *pData )																	= 0;

		/**
			@brief ファイルオープン
			@author 葉迩倭
			@param pFile		[in] ファイル名
			@retval NULL		失敗
			@retval NULL以外	ファイルインターフェイス

			リソースファイルをオープンします。<BR>
			ここでいうリソースファイルはゲームで使われるデータ全般の事です。<BR>
			つまりパックファイルの内容、およびルートディレクトリ以下のデータです。<BR>
			SetLoadPath() で指定されている[フォルダ]→[パックファイル]の<BR>
			順にファイルを検索します。<BR>
			オープンしたファイルはパックファイルであっても、<BR>
			通常のファイルと同じようにアクセスすることが出来ます。<BR>
			またこの関数から取得したIFIleインターフェイスは読み取り専用です。<BR>
			使用が終了したIFileインターフェイスはRelease()で解放してください。
		*/
		virtual IResourceFile *FileOpen( const wchar_t *pFile )												= 0;
	};
}



namespace Selene
{
	/**
		@brief リソースファイル操作
		@author 葉迩倭
	*/
	class IResourceFile
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void	)								= 0;

		/**
			@brief ファイルへの読み込み
			@author 葉迩倭
			@param pData	[in] 読み込みデータ
			@param Size		[in] 読み込みデータサイズ
			@return 実際に書き込んだバイト数

			ファイルへの読み込みを行います。<BR>
			読み込み可能なファイルはインターフェイス生成時に<BR>
			FILE_OPEN_TYPE_READかFILE_OPEN_TYPE_READ_WRITEフラグを<BR>
			指定する必要があります。
		*/
		virtual Uint32 Read( void *pData, Uint32 Size )				= 0;

		/**
			@brief ファイル名取得
			@author 葉迩倭
			@return ファイル名の先頭アドレス

			ファイル名の先頭アドレスを取得します。
		*/
		virtual const wchar_t *GetNamePointer( void )				= 0;

		/**
			@brief ファイルサイズ取得
			@author 葉迩倭
			@return ファイルサイズ

			ファイルのサイズを取得します。
		*/
		virtual Uint32 GetFileSize( void )							= 0;

		/**
			@brief ファイルポインター位置取得
			@author 葉迩倭
			@return ファイルポインターの位置

			現在のファイルポインタの位置を取得します。
		*/
		virtual Uint32 GetFilePosition( void )						= 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置

			ファイルポインターの位置をファイルの先頭からOffsetバイト移動します。
		*/
		virtual Uint32 SeekStart( Sint32 Offset )					= 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置

			ファイルポインターの位置をファイルの終端からOffsetバイト移動します。
		*/
		virtual Uint32 SeekEnd( Sint32 Offset )						= 0;

		/**
			@brief ファイルシーク
			@author 葉迩倭
			@param Offset	[in] 移動量
			@return ファイルポインターの位置

			ファイルポインターの位置を現在の位置からOffsetバイト移動します。
		*/
		virtual Uint32 Seek( Sint32 Offset )						= 0;
	};
}



namespace Selene
{
	/**
		@brief マウスボタン状態定義
		@author 葉迩倭
	*/
	enum eMouseState
	{
		MOUSE_FREE,							///< マウスボタンは押されていない
		MOUSE_PULL,							///< マウスボタンは離された
		MOUSE_PUSH,							///< マウスボタンは押された
		MOUSE_HOLD,							///< マウスボタンは押されつづけている
	};

	/**
		@brief マウス管理インターフェイス
		@author 葉迩倭
	*/
	class IMouse
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )					= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )					= 0;

		/**
			@brief マウスのX座標取得
			@author 葉迩倭
			@return X座標

			マウスポインターのスクリーン座標上のX座標を取得します。
		*/
		virtual Sint32 GetPosX( void ) const			= 0;

		/**
			@brief マウスのY座標取得
			@author 葉迩倭
			@return Y座標

			マウスポインターのスクリーン座標上のY座標を取得します。
		*/
		virtual Sint32 GetPosY( void ) const			= 0;

		/**
			@brief マウスのホイール回転量取得
			@author 葉迩倭
			@return ホイール回転量

			マウスホイールの回転量を取得します。
		*/
		virtual Sint32 GetPosW( void ) const			= 0;

		/**
			@brief マウスのX移動量取得
			@author 葉迩倭
			@return X移動量

			マウスポインターのスクリーン移動量上のX移動量を取得します。
		*/
		virtual Sint32 GetMoveX( void ) const			= 0;

		/**
			@brief マウスのY移動量取得
			@author 葉迩倭
			@return Y移動量

			マウスポインターのスクリーン移動量上のY移動量を取得します。
		*/
		virtual Sint32 GetMoveY( void ) const			= 0;

		/**
			@brief マウスの左クリック状態取得
			@author 葉迩倭
			@retval false	左ボタンは押されていない
			@retval true	左ボタンは押されている

			マウスの左ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickL( void ) const			= 0;

		/**
			@brief マウスの右クリック状態取得
			@author 葉迩倭
			@retval false	右ボタンは押されていない
			@retval true	右ボタンは押されている

			マウスの右ボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickR( void ) const			= 0;

		/**
			@brief マウスのホイールクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンは押されていない
			@retval true	ホイールボタンは押されている

			マウスのホイールボタンの状態を取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetClickW( void ) const			= 0;

		/**
			@brief マウスの左ダブルクリック状態取得
			@author 葉迩倭
			@retval false	左ボタンはダブルクリックされていない
			@retval true	左ボタンはダブルクリックされた

			マウスの左ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickL( void ) const		= 0;

		/**
			@brief マウスの右ダブルクリック状態取得
			@author 葉迩倭
			@retval false	右ボタンはダブルクリックされていない
			@retval true	右ボタンはダブルクリックされた

			マウスの右ボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickR( void ) const		= 0;

		/**
			@brief マウスのホイールダブルクリック状態取得
			@author 葉迩倭
			@retval false	ホイールボタンはダブルクリックされていない
			@retval true	ホイールボタンはダブルクリックされた

			マウスのホイールボタンがダブルクリックされたかを取得します。<BR>
			この関数ではON/OFFしか取得できません。
		*/
		virtual Bool GetDoubleClickW( void ) const		= 0;

		/**
			@brief マウスの左ボタン状態取得
			@author 葉迩倭
			@return		左ボタンの状態

			マウスの左ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState GetStateL( void ) const		= 0;

		/**
			@brief マウスの右ボタン状態取得
			@author 葉迩倭
			@return		右ボタンの状態

			マウスの右ボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateR( void ) const		= 0;

		/**
			@brief マウスのホイールボタン状態取得
			@author 葉迩倭
			@return		ホイールボタンの状態

			マウスのホイールボタンの詳細な情報を取得します。
		*/
		virtual eMouseState	GetStateW( void ) const		= 0;
	};
}



namespace Selene
{
	/**
		@brief 仮想キーコード
		@author 葉迩倭
	*/
	enum eVirtualKeyCode
	{
		SELENE_VK_ESCAPE          = 0x01,
		SELENE_VK_1               = 0x02,
		SELENE_VK_2               = 0x03,
		SELENE_VK_3               = 0x04,
		SELENE_VK_4               = 0x05,
		SELENE_VK_5               = 0x06,
		SELENE_VK_6               = 0x07,
		SELENE_VK_7               = 0x08,
		SELENE_VK_8               = 0x09,
		SELENE_VK_9               = 0x0A,
		SELENE_VK_0               = 0x0B,
		SELENE_VK_MINUS           = 0x0C,
		SELENE_VK_EQUALS          = 0x0D,
		SELENE_VK_BACK            = 0x0E,
		SELENE_VK_TAB             = 0x0F,
		SELENE_VK_Q               = 0x10,
		SELENE_VK_W               = 0x11,
		SELENE_VK_E               = 0x12,
		SELENE_VK_R               = 0x13,
		SELENE_VK_T               = 0x14,
		SELENE_VK_Y               = 0x15,
		SELENE_VK_U               = 0x16,
		SELENE_VK_I               = 0x17,
		SELENE_VK_O               = 0x18,
		SELENE_VK_P               = 0x19,
		SELENE_VK_LBRACKET        = 0x1A,
		SELENE_VK_RBRACKET        = 0x1B,
		SELENE_VK_RETURN          = 0x1C,
		SELENE_VK_LCONTROL        = 0x1D,
		SELENE_VK_A               = 0x1E,
		SELENE_VK_S               = 0x1F,
		SELENE_VK_D               = 0x20,
		SELENE_VK_F               = 0x21,
		SELENE_VK_G               = 0x22,
		SELENE_VK_H               = 0x23,
		SELENE_VK_J               = 0x24,
		SELENE_VK_K               = 0x25,
		SELENE_VK_L               = 0x26,
		SELENE_VK_SEMICOLON       = 0x27,
		SELENE_VK_APOSTROPHE      = 0x28,
		SELENE_VK_GRAVE           = 0x29,
		SELENE_VK_LSHIFT          = 0x2A,
		SELENE_VK_BACKSLASH       = 0x2B,
		SELENE_VK_Z               = 0x2C,
		SELENE_VK_X               = 0x2D,
		SELENE_VK_C               = 0x2E,
		SELENE_VK_V               = 0x2F,
		SELENE_VK_B               = 0x30,
		SELENE_VK_N               = 0x31,
		SELENE_VK_M               = 0x32,
		SELENE_VK_COMMA           = 0x33,
		SELENE_VK_PERIOD          = 0x34,
		SELENE_VK_SLASH           = 0x35,
		SELENE_VK_RSHIFT          = 0x36,
		SELENE_VK_MULTIPLY        = 0x37,
		SELENE_VK_LMENU           = 0x38,
		SELENE_VK_SPACE           = 0x39,
		SELENE_VK_CAPITAL         = 0x3A,
		SELENE_VK_F1              = 0x3B,
		SELENE_VK_F2              = 0x3C,
		SELENE_VK_F3              = 0x3D,
		SELENE_VK_F4              = 0x3E,
		SELENE_VK_F5              = 0x3F,
		SELENE_VK_F6              = 0x40,
		SELENE_VK_F7              = 0x41,
		SELENE_VK_F8              = 0x42,
		SELENE_VK_F9              = 0x43,
		SELENE_VK_F10             = 0x44,
		SELENE_VK_NUMLOCK         = 0x45,
		SELENE_VK_SCROLL          = 0x46,
		SELENE_VK_NUMPAD7         = 0x47,
		SELENE_VK_NUMPAD8         = 0x48,
		SELENE_VK_NUMPAD9         = 0x49,
		SELENE_VK_SUBTRACT        = 0x4A,
		SELENE_VK_NUMPAD4         = 0x4B,
		SELENE_VK_NUMPAD5         = 0x4C,
		SELENE_VK_NUMPAD6         = 0x4D,
		SELENE_VK_ADD             = 0x4E,
		SELENE_VK_NUMPAD1         = 0x4F,
		SELENE_VK_NUMPAD2         = 0x50,
		SELENE_VK_NUMPAD3         = 0x51,
		SELENE_VK_NUMPAD0         = 0x52,
		SELENE_VK_DECIMAL         = 0x53,
		SELENE_VK_OEM_102         = 0x56,
		SELENE_VK_F11             = 0x57,
		SELENE_VK_F12             = 0x58,
		SELENE_VK_KANA            = 0x70,
		SELENE_VK_ABNT_C1         = 0x73,
		SELENE_VK_CONVERT         = 0x79,
		SELENE_VK_NOCONVERT       = 0x7B,
		SELENE_VK_YEN             = 0x7D,
		SELENE_VK_ABNT_C2         = 0x7E,
		SELENE_VK_NUMPADEQUALS    = 0x8D,
		SELENE_VK_PREVTRACK       = 0x90,
		SELENE_VK_NUMPADENTER     = 0x9C,
		SELENE_VK_RCONTROL        = 0x9D,
		SELENE_VK_NUMPADCOMMA     = 0xB3,
		SELENE_VK_DIVIDE          = 0xB5,
		SELENE_VK_SYSRQ           = 0xB7,
		SELENE_VK_RMENU           = 0xB8,
		SELENE_VK_PAUSE           = 0xC5,
		SELENE_VK_HOME            = 0xC7,
		SELENE_VK_UP              = 0xC8,
		SELENE_VK_PRIOR           = 0xC9,
		SELENE_VK_LEFT            = 0xCB,
		SELENE_VK_RIGHT           = 0xCD,
		SELENE_VK_END             = 0xCF,
		SELENE_VK_DOWN            = 0xD0,
		SELENE_VK_NEXT            = 0xD1,
		SELENE_VK_INSERT          = 0xD2,
		SELENE_VK_DELETE          = 0xD3,
		SELENE_VK_LWIN            = 0xDB,
		SELENE_VK_RWIN            = 0xDC,

		SELENE_VK_NONE            = 0x00000000
	};

	/**
		@brief キーボード管理インターフェイス
		@author 葉迩倭
	*/
	class IKeyboard
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )											= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照カウント

			参照カウンタをデクリメントし、<BR>
			参照カウントが0になった時点でメモリから解放します。
		*/
		virtual Uint32 Release( void )						= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照カウント

			参照カウンタをインクリメントします。<BR>
			インクリメントした参照カウントはRelease()を呼ぶことによりデクリメントされます。<BR>
			AddRef()をしたインターフェイスは必ずRelease()で解放してください。
		*/
		virtual Uint32 AddRef( void )						= 0;

		/**
			@brief キー入力バッファフラッシュ
			@author 葉迩倭

			キー入力バッファに蓄積した入力バッファをクリアします。
		*/
		virtual void ClearKeyBuffer( void )					= 0;

		/**
			@brief キー入力バッファからデータ取得
			@author 葉迩倭
			@return 入力されたキーのキーコード

			キー入力バッファに蓄積されたデータを取り出します。<BR>
			押されたキーを全て取り出す時はwhile()文等で処理してください。
		*/
		virtual eVirtualKeyCode GetKeyBuffer( void )		= 0;

		/**
			@brief キーが押されているかチェックする
			@author 葉迩倭
			@retval false	押されていない
			@retval true	押されている

			指定されたキーが現在押されているかチェックします。<BR>
			純粋にキーのON/OFFのみ取得できます。
		*/
		virtual Bool GetKeyData( eVirtualKeyCode Key )		= 0;
	};
}



namespace Selene
{
	/**
		@brief サウンド管理クラス
		@author 葉迩倭

		サウンドの処理を行うクラスです。<BR>
		WAV/圧縮WAVE/OGGの再生に対応しています。
	*/
	class ISound
	{
	public:
		/**
			@brief 有効性チェック
			@author 葉迩倭
			@retval true 無効
			@retval false 有効

			インターフェイスが有効か無効かを調べます。
		*/
		virtual Bool IsInvalid( void )								= 0;

		/**
			@brief 参照カウンタデクリメント
			@author 葉迩倭
			@return デクリメント後の参照値
		*/
		virtual Uint32 Release( void )								= 0;

		/**
			@brief 参照カウンタインクリメント
			@author 葉迩倭
			@return インクリメント後の参照値
		*/
		virtual Uint32 AddRef( void )								= 0;

		/**
			@brief 再生
			@author 葉迩倭
			@param LoopCount		[in] ループカウント
			@param LoopInSample		[in] ループ後開始位置サンプル数

			読み込んだサウンドデータの再生を開始します。<BR>
			ループ数と、ループ後再生開始位置をサンプル単位で指定できます。
		*/
		virtual void Play( Uint32 LoopCount, Uint32 LoopInSample )	= 0;

		/**
			@brief 停止
			@author 葉迩倭

			再生中のサウンドを停止します。
		*/
		virtual void Stop( void )									= 0;

		/**
			@brief 一時停止/解除
			@author 葉迩倭

			再生中のサウンドを一時停止、<BR>
			一時停止中のサウンドを再生します。
		*/
		virtual void Pause( void )									= 0;

		/**
			@brief ボリューム変更
			@author 葉迩倭
			@param fVolume	[in] ボリューム（0～100）

			ボリュームの変更を行います。
		*/
		virtual void SetVolume( Float fVolume )						= 0;

		/**
			@brief パン移動
			@author 葉迩倭
			@param fPan	[in] パン（-100～+100）

			パンの移動を行います。
		*/
		virtual void SetPan( Float fPan )							= 0;

		/**
			@brief 再生チェック
			@author 葉迩倭
			@retval false	再生していない
			@retval true	再生している

			現在再生中のサウンドかどうか調べます。
		*/
		virtual Bool IsPlay( void )									= 0;
	};
}


#endif  // ___SELENE_H___


