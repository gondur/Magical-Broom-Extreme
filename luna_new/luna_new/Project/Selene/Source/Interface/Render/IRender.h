

#ifndef ___SELENE__IRENDER___
#define ___SELENE__IRENDER___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"
#include "Color.h"
#include "Class/Math/Math.h"
#include "Class/Math/Vector2D.h"
#include "Class/Math/Vector3D.h"
#include "Class/Math/Vector4D.h"
#include "Interface/Scene/ISceneManager.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
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

#endif // ___SELENE__IRENDER___

