//======================================================================================
//======================================================================================
//
//
//			���C�t
//
//
//======================================================================================
//======================================================================================


//======================================================================================
//	include
//======================================================================================
#include "Life.h"
#include "LifeParts.h"


//======================================================================================
//
//	�R���X�g���N�^
//
//======================================================================================
CLIFE::CLIFE( LPCPLAYER p ) : CSPRITE( SORT_NULL )
{
	lpPlayer = p;
	lpPlayer->AddRef();
	Life = p->Life;
	Py = -15;
	bQuake = false;
}

//======================================================================================
//
//	�f�X�g���N�^
//
//======================================================================================
CLIFE::~CLIFE()
{
	lpPlayer->Release();
}

//======================================================================================
//
//	����
//
//======================================================================================
bool CLIFE::Action( void )
{
	RECT dest, src;

	// ���ɉ����肫�����u�Ԃɗh�炷
	if ( bQuake )
	{
		Angle += 384;
		Py = F(LunaMath::Sin( Angle, Scale/10 )) + y1;
		if ( --Scale == 0 ) bQuake = false;
	}
	else
	{
		// ���@�����ʒu����ɂ����烉�C�t�\������ɏグ��
		if ( lpPlayer->Py < 30 )
		{
			Phase = 0;
			Py -= 2;
			if ( Py < -15 ) Py = -15;
		}
		// ����ȊO�͉��ɉ����Â���
		else
		{
			// ���C�t�\�����W���ʒu����ɂ���ꍇ
			if ( Phase == 0 )
			{
				Py += 2;
				// ���ʒu��艺�ɂ͉����Ȃ�
				if ( Py > 5 )
				{
					Py = 5;
					Angle = 0;
					Scale = 50;
					SetQuake( true );
					Phase++;
				}
			}
		}
	}

	//----------------------------------------------------
	// �`��
	//----------------------------------------------------
	SetRect( &dest, 10, (long)Py, 65, (long)Py+15 );
	SetRect( &src, 708, 632, 768, 647 );
	Sprite[7][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );

	SetRect( &src, 708, 647, 758, 662 );
	long life = lpPlayer->Life;
	for ( long i = 0; i < life; i++ )
	{
		SetRect( &dest, 75+i*55, (long)Py, 75+i*55+50, (long)Py+15 );
		Sprite[7][0]->Draw( &dest, D3DCOLOR_XRGB(255,255,255), &src );
	}

	//----------------------------------------------------
	// ���C�t���������Ƃ��͔j�Ђ��΂�
	//----------------------------------------------------
	if ( life < Life )
	{
		for ( long i = 0; i < 32; i++ )
		{
			long x = RAND( 75+life*55, 75+life*55+50 );
			long y = RAND( (long)Py, (long)Py+15 );
			new CLIFEPARTS( F(x), F(y), D3DCOLOR_XRGB(211,146,227) ); 
		}
		SetQuake( true );
	}
	Life = life;

	return bDeath;
}

//======================================================================================
//
//	�h��ݒ�
//
//======================================================================================
void CLIFE::SetQuake( bool flag )
{
	y1 = Py;
	bQuake = flag;
	Scale = 50;
	Angle = 0;
}