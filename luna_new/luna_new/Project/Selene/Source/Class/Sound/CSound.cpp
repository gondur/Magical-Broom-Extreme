

//-----------------------------------------------------------------------------------
// INCLUDE
//-----------------------------------------------------------------------------------
#include "Base.h"		// PCH
#include "Local.h"
#include "Core/CCore.h"
#include "Sound/CSound.h"
#include "File/CFileManager.h"
#include "File/CResourceFile.h"
#include "../Project/Lib/Ayame.h"


//-----------------------------------------------------------------------------------
// PROTOTPE
//-----------------------------------------------------------------------------------
CAyame *Ayame_CreateInstanceFromFileEx( const char *pFileName, unsigned long Start, unsigned long Size, bool IsGlobal );


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
CSound::CSound( CCore *pCore )
	: m_pDriver		( NULL )
{
	pCore->AddChild( this );
}


//-----------------------------------------------------------------------------------
/**
	@brief デストラクタ
	@author 葉迩倭
*/
//-----------------------------------------------------------------------------------
CSound::~CSound( void )
{
	Log_PrintTable( 0xFF0000, 0x000000, L"解放", L"サウンド", m_Name );
	Log_TableLine( 1 );

	SAFE_RELEASE( m_pDriver );
}

//-----------------------------------------------------------------------------------
/**
	@brief サウンド生成
	@author 葉迩倭

	@param pFileName		[in] サウンドファイル名
	@param IsGlobalScope	[in] ウィンドウが非アクティブ化しても再生するかどうか

	@retval false	失敗
	@retval true	成功
*/
//-----------------------------------------------------------------------------------
Bool CSound::CreateFromFile( const wchar_t *pFileName, Bool IsGlobalScope )
{
	CCore *pCore = dynamic_cast<CCore*>(m_pParent);
	CResourceFile *pFile = NULL;

	try
	{
		//--------------------------------------------------------------
		// データの読み込み
		//--------------------------------------------------------------
		pFile = dynamic_cast<CResourceFile*>(pCore->GetFileMgrPointer()->FileOpen( pFileName ));
		if ( pFile == NULL )
		{
			throw L"ファイルが開けませんでした";
		}

		//--------------------------------------------------------------
		// ドライバーの取得
		//--------------------------------------------------------------
		char Temp[MAX_PATH] = "";
		WCStoMBCS( pFile->GetNamePointer(), Temp );

		m_pDriver = Ayame_CreateInstanceFromFileEx( Temp, pFile->GetFileStart(), pFile->GetFileSize(), IsGlobalScope );
		if ( m_pDriver == NULL )
		{
			throw L"ドライバーが取得できませんでした";
		}
	}
	catch ( const wchar_t *pErr )
	{
		Log_PrintStrong( 0xFF0000, pErr );
		m_pDriver = NULL;
	}

	// ファイルクローズ
	SAFE_RELEASE( pFile );

	return m_pDriver != NULL;
}

//-----------------------------------------------------------------------------------
/**
	@brief 再生
	@author 葉迩倭

	@param LoopCount		[in] ループカウント
	@param LoopInSample		[in] ループ後開始位置サンプル数

	読み込んだサウンドデータの再生を開始します。<BR>
	ループ数と、ループ後再生開始位置をサンプル単位で指定できます。
*/
//-----------------------------------------------------------------------------------
void CSound::Play( Uint32 LoopCount, Uint32 LoopInSample )
{
	m_pDriver->Play( LoopCount, LoopInSample );
}

//-----------------------------------------------------------------------------------
/**
	@brief 停止
	@author 葉迩倭

	再生中のサウンドを停止します。
*/
//-----------------------------------------------------------------------------------
void CSound::Stop( void )
{
	m_pDriver->Stop();
}

//-----------------------------------------------------------------------------------
/**
	@brief 一時停止/解除
	@author 葉迩倭

	再生中のサウンドを一時停止、<BR>
	一時停止中のサウンドを再生します。
*/
//-----------------------------------------------------------------------------------
void CSound::Pause( void )
{
	m_pDriver->Pause();
}

//-----------------------------------------------------------------------------------
/**
	@brief ボリューム変更
	@author 葉迩倭

	@param fVolume	[in] ボリューム（0～100）

	ボリュームの変更を行います。
*/
//-----------------------------------------------------------------------------------
void CSound::SetVolume( Float fVolume )
{
	m_pDriver->SetVolume( fVolume );
}

//-----------------------------------------------------------------------------------
/**
	@brief パン移動
	@author 葉迩倭

	@param fVolume	[in] パン（-100～+100）

	パンの移動を行います。
*/
//-----------------------------------------------------------------------------------
void CSound::SetPan( Float fPan )
{
	m_pDriver->SetPan( fPan );
}

//-----------------------------------------------------------------------------------
/**
	@brief 再生チェック
	@author 葉迩倭

	@retval false	再生していない
	@retval true	再生している

	現在再生中のサウンドかどうか調べます。
*/
//-----------------------------------------------------------------------------------
Bool CSound::IsPlay( void )
{
	return m_pDriver->IsPlay();
}

