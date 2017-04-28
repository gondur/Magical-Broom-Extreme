

#ifndef ___SELENE__IRESOURCEFILE___
#define ___SELENE__IRESOURCEFILE___


//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
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

#endif // ___SELENE__IRESOURCEFILE___

