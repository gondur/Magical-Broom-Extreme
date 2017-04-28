

//------------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------------
#include "LueBase.h"
#include "LueFile.h"


//------------------------------------------------------------------------------------------------
// NameSpace
//------------------------------------------------------------------------------------------------
using namespace Selene;


//------------------------------------------------------------------------------------------------
// for C compiler
//------------------------------------------------------------------------------------------------
extern "C" {


//------------------------------------------------------------------------------------------------
// ProtoType
//------------------------------------------------------------------------------------------------
extern ICore *Lue_GetCore( void );
extern void MBCStoWCS( const char *pSrc, wchar_t *pDst );


//------------------------------------------------------------------------------------------------
/**
	@brief ファイル読み込み
	@author 葉迩倭

	@param pFile	[in] 読み込みファイル名
	@param ppData	[out] 読み込みデータ格納先
	@param pSize	[out] 読み込みデータサイズ格納先

	@retval LTRUE	読み込み成功
	@retval LFALSE	読み込み失敗

	ファイルの読み込みを行います。<BR>
	読み込みが成功すると内部でメモリが確保され、<BR>
	そのアドレスが ppData に格納され、ファイルサイズが pSize に格納されます。<BR>
	読み込み後、不要になったファイルデータは File_Release 関数でメモリ上から解放してください。
*/
//------------------------------------------------------------------------------------------------
eLueBool LueFile_Load( const char *pFile, void **ppData, unsigned int *pSize )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFile, wTemp );
	return Lue_GetCore()->GetFileMgrPointer()->Load( wTemp, ppData, (Uint32*)pSize ) ? LTRUE : LFALSE;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイル解放
	@author 葉迩倭

	@param pData	[in] 読み込みデータ解放

	File_Load 関数で読み込んだデータを解放します。<BR>
	この関数で解放を行わないとアプリケーションが終了しても<BR>
	メモリから削除されません。
*/
//------------------------------------------------------------------------------------------------
void LueFile_Release( void *pData )
{
	MemGlobalFree( pData );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルのオープン
	@author 葉迩倭

	@param pFile	[in] ファイル名

	@retval NULL		ファイルオープン失敗
	@return NULL以外	ファイルのファイルポインタ

	オープン中のファイルのクローズします。
*/
//------------------------------------------------------------------------------------------------
LUE_FILEPTR LueFile_FileOpen( const char *pFile )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pFile, wTemp );
	return (LUE_FILEPTR)Lue_GetCore()->GetFileMgrPointer()->FileOpen( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルのクローズ
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルのクローズします。
*/
//------------------------------------------------------------------------------------------------
void LueFile_FileClose( LUE_FILEPTR FilePtr )
{
	((IResourceFile*)FilePtr)->Release();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルのサイズを取得
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルのファイルサイズを取得します。
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileGetSize( LUE_FILEPTR FilePtr )
{
	return ((IResourceFile*)FilePtr)->GetFileSize();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルポインタの位置を取得
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ

	オープン中のファイルの現在のファイルポインタの<BR>
	位置を取得します。
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileGetPosition( LUE_FILEPTR FilePtr )
{
	return ((IResourceFile*)FilePtr)->GetFilePosition();
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルの読み込み
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ
	@param pData	[in/out] データ格納先
	@param Size		[in] 読み込みサイズ

	現在のファイルポインタの位置から指定データサイズ分の<BR>
	データを読み込みます。
*/
//------------------------------------------------------------------------------------------------
unsigned int LueFile_FileRead( LUE_FILEPTR FilePtr, void *pData, unsigned int Size )
{
	return ((IResourceFile*)FilePtr)->Read( pData, Size );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイルポインタの移動
	@author 葉迩倭

	@param FilePtr	[in] ファイルポインタ
	@param Offset	[in] ファイルポインタの移動量
	@param Flag		[in] ファイルポインタ基準位置

	オープン中のファイルのファイルポインタを任意の位置に移動します。
*/
//------------------------------------------------------------------------------------------------
int LueFile_FileSeek( LUE_FILEPTR FilePtr, int Offset, eLueSeek Flag )
{
	switch ( Flag )
	{
	case LSEEK_FILE_CURRENT:		///< 現在位置
		return ((IResourceFile*)FilePtr)->Seek( Offset );
	case LSEEK_FILE_START:			///< 先頭位置
		return ((IResourceFile*)FilePtr)->SeekStart( Offset );
	case LSEEK_FILE_END:			///< 終端位置
		return ((IResourceFile*)FilePtr)->SeekEnd( Offset );
	}

	return 0;
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイル読み込みカレントディレクトリ設定
	@author 葉迩倭

	@param pCurrentDir	[in] 検索カレントディレクトリ

	ファイルを検索する際に使われるカレントディレクトリを設定します<BR>
	LueFile_SetLoadPath をルートのパスとして、それ以下のディレクトリを指定します<BR>
	<BR>
	例）Data/Texture/Chara00/Stand.bmp の読み込み<BR>
	LueFile_SetLoadPath で Data を指定し、<BR>
	LueFile_SetCurrentDirectory で Texture/Chara00 を指定します。<BR>
	その後 LueFile_Load で Stand.bmp と指定することで読み込まれます。
*/
//------------------------------------------------------------------------------------------------
void LueFile_SetCurrentDirectory( char *pCurrentDir )
{
	wchar_t wTemp[MAX_PATH] = L"";
	MBCStoWCS( pCurrentDir, wTemp );
	Lue_GetCore()->GetFileMgrPointer()->SetCurrentDirectory( wTemp );
}


//------------------------------------------------------------------------------------------------
/**
	@brief ファイル読み込みパス設定
	@author 葉迩倭

	@param Priority		[in] 読み込み優先度
	@param pRootPath	[in] ルートディレクトリ
	@param pPackFile	[in] パックファイル名

	ファイル読み込みの際に使われるパスを設定します<BR>
	pRootPath と pPackFile は同列に扱われ、<BR>
	pRootPath 内の検索実行後に pPackFile 内の検索を行うようになっています。
*/
//------------------------------------------------------------------------------------------------
void LueFile_SetLoadPath( unsigned int Priority, const char *pRootPath, const char *pPackFile )
{
	wchar_t wTemp0[MAX_PATH] = L"";
	wchar_t wTemp1[MAX_PATH] = L"";
	MBCStoWCS( pRootPath, wTemp0 );
	MBCStoWCS( pPackFile, wTemp1 );
	return Lue_GetCore()->GetFileMgrPointer()->SetLoadPath( Priority, wTemp0, wTemp1 );
}


} // extern "C"

