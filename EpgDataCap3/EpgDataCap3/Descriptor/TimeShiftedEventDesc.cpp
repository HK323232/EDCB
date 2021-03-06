#include "StdAfx.h"
#include "TimeShiftedEventDesc.h"

CTimeShiftedEventDesc::CTimeShiftedEventDesc(void)
{
}

CTimeShiftedEventDesc::~CTimeShiftedEventDesc(void)
{
}

BOOL CTimeShiftedEventDesc::Decode( BYTE* data, DWORD dataSize, DWORD* decodeReadSize )
{
	if( data == NULL ){
		return FALSE;
	}

	//////////////////////////////////////////////////////
	//サイズのチェック
	//最低限descriptor_tagとdescriptor_lengthのサイズは必須
	if( dataSize < 2 ){
		return FALSE;
	}
	//->サイズのチェック

	DWORD readSize = 0;
	//////////////////////////////////////////////////////
	//解析処理
	descriptor_tag = data[0];
	descriptor_length = data[1];
	readSize += 2;

	if( descriptor_tag != 0x4F ){
		//タグ値がおかしい
		_OutputDebugString( L"++++CTimeShiftedEventDesc:: descriptor_tag err 0x4F != 0x%02X", descriptor_tag );
		return FALSE;
	}

	if( readSize+descriptor_length > dataSize ){
		//サイズ異常
		_OutputDebugString( L"++++CTimeShiftedEventDesc:: size err %d > %d", readSize+descriptor_length, dataSize );
		return FALSE;
	}
	if( descriptor_length > 0 ){
		reference_service_id = ((WORD)data[readSize])<<8 | data[readSize+1];
		reference_event_id = ((WORD)data[readSize+2])<<8 | data[readSize+3];
		readSize += 4;
	}else{
		return FALSE;
	}
	//->解析処理

	if( decodeReadSize != NULL ){
		*decodeReadSize = 2+descriptor_length;
	}

	return TRUE;
}

