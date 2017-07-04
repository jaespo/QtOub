#include "misc.h"
#include "serialize.h"

//
//	ctor of an archive object
//
jlib::CArchive::CArchive()
{
	mqBuf = nullptr;
	mBufLen = 0;
	mCurOffset = 0;
}

//
//	dtor of the archive object
//
jlib::CArchive::~CArchive()
{
}

// 
//	Gets some chars from the archive
//
void jlib::CArchive::GetChars(char* pCh, size_t vLen)
{
	if (mCurOffset + vLen >= mBufLen)
	{
		THROW_ERR(9999, << "GetChars() indexing off the end of the archive buffer")
	}
	memcpy( pCh, mqBuf.get() + mCurOffset, vLen);
	mCurOffset += vLen;
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(uint8_t& vNum)
{
	if (mCurOffset >= mBufLen)
	{
		THROW_ERR(9999, << "unable to get int8_t, at buffer's end");
	}
	vNum = (uint8_t)mqBuf.get()[mCurOffset++];
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(int8_t& vNum)
{
	if (mCurOffset >= mBufLen)
	{
		THROW_ERR(9999, << "unable to get int8_t, at buffer's end");
	}
	vNum = (int8_t)mqBuf.get()[mCurOffset++];
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(uint16_t& vNum)
{
	if (mCurOffset + sizeof( vNum ) > mBufLen)
	{
		THROW_ERR(9999, << "unable to get int16_t, at buffer's end");
	}
	vNum = 0;
	for (int j = 0; j < sizeof(vNum); j++)
	{
		vNum = 256 * vNum + (uint8_t)mqBuf.get()[mCurOffset++];
	}
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(int16_t& vNum)
{
	uint16_t vUnsigned;
	GetNum(vUnsigned);
	vNum = (int16_t)vUnsigned;
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(uint32_t& vNum)
{
	if (mCurOffset + sizeof(vNum) > mBufLen)
	{
		THROW_ERR(9999, << "unable to get int32_t, at buffer's end");
	}
	vNum = 0;
	for (int j = 0; j < sizeof(vNum); j++)
	{
		vNum = 256 * vNum + (uint8_t)mqBuf.get()[mCurOffset++];
	}
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(int32_t& vNum)
{
	uint32_t vUnsigned;
	GetNum(vUnsigned);
	vNum = (int32_t)vUnsigned;
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(uint64_t& vNum)
{
	if (mCurOffset + sizeof(vNum) > mBufLen)
	{
		THROW_ERR(9999, << "unable to get int64_t, at buffer's end");
	}
	vNum = 0;
	for (int j = 0; j < sizeof(vNum); j++)
	{
		vNum = 256 * vNum + (uint8_t)mqBuf.get()[mCurOffset++];
	}
}

// 
//	Gets the number from the archive
//
void jlib::CArchive::GetNum(int64_t& vNum)
{
	uint64_t vUnsigned;
	GetNum(vUnsigned);
	vNum = (int64_t)vUnsigned;
}

// 
//	Gets a string from the archive
//
void jlib::CArchive::GetStr(std::string& rStr)
{
	size_t vLen;
	GetNum(vLen);
	if (mCurOffset + vLen >= mBufLen)
	{
		THROW_ERR( 9999, << "GetStr() indexing off the end of the archive buffer")
	}
	rStr.assign(mqBuf.get() + mCurOffset, vLen);
	mCurOffset += vLen;
}

// 
//	Sets the buffer into the archive
//
void jlib::CArchive::SetBuf(std::shared_ptr<char> qBuf, size_t vBufLen)
{
	mqBuf = qBuf;
	mBufLen = vBufLen;
	mCurOffset = 0;
}

//
//	Puts bytes into a buffer
//
void jlib::CArchive::PutChars(const char* pCh, size_t vLen)
{
	if (mCurOffset + vLen > mBufLen)
	{
		THROW_ERR(9999, << "Not enough room in archive, need " << vLen);
	}
	memcpy( &(mqBuf.get()[mCurOffset]), pCh, vLen);
	mCurOffset += vLen;
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(int8_t vNum)
{
	PutChars( (char*)&vNum, 1);
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(uint8_t vNum)
{
	PutChars((char*)&vNum, 1);
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(int16_t vNum)
{
	PutNum(uint16_t(vNum));
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(uint16_t vNum)
{
	char pNumBuf[sizeof( vNum )];
	int ix = sizeof(vNum);
	for ( int j = 0; j < sizeof(vNum); j++ )
	{
		pNumBuf[ix--] = vNum % 255;
		vNum = vNum / 256;
	}
	PutChars(pNumBuf, sizeof(vNum));
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(int32_t vNum)
{
	PutNum(uint16_t(vNum));
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(uint32_t vNum)
{
	char pNumBuf[sizeof(vNum)];
	int ix = sizeof(vNum);
	for (int j = 0; j < sizeof(vNum); j++)
	{
		pNumBuf[ix--] = vNum % 255 ;
		vNum = vNum / 256;
	}
	PutChars(pNumBuf, sizeof(vNum));
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(int64_t vNum)
{
	PutNum(uint16_t(vNum));
}

//
//	Puts a number into the archive's buffer
//
void jlib::CArchive::PutNum(uint64_t vNum)
{
	char pNumBuf[sizeof(vNum)];
	int ix = sizeof(vNum);
	for (int j = 0; j < sizeof(vNum); j++)
	{
		pNumBuf[ix--] = vNum % 255;
		vNum = vNum / 256;
	}
	PutChars(pNumBuf, sizeof(vNum));
}

//
//	Puts a std string into the archive's buffer
//
void jlib::CArchive::PutStr(const std::string& rStr)
{
	PutNum(rStr.size());
	PutChars(rStr.c_str(), rStr.size());
}
	

