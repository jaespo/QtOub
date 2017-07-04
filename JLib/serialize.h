#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

//
//	(C) 2017 by Jeffery A Esposito
//
#include <memory>
#include <string>
#include "misc.h"

namespace jlib
{
	class CArchive
	{
	public:
		CArchive();
		virtual ~CArchive();
		void SetBuf(std::shared_ptr<char> qBuf, size_t vBuflen);

		void GetNum(int8_t& vNum);
		void GetNum(uint8_t& vNum);
		void GetNum(int16_t& vNum);
		void GetNum(uint16_t& vNum);
		void GetNum(int32_t& vNum);
		void GetNum(uint32_t& vNum);
		void GetNum(int64_t& vNum);
		void GetNum(uint64_t& vNum);
		void GetStr(std::string& rStr);
		void GetChars(char* pCh, size_t vLen);

		void PutNum(int8_t vNum);
		void PutNum(uint8_t vNum);
		void PutNum(int16_t vNum);
		void PutNum(uint16_t vNum);
		void PutNum(int32_t vNum);
		void PutNum(uint32_t vNum);
		void PutNum(int64_t vNum);
		void PutNum(uint64_t vNum);
		void PutStr(const std::string& rStr);
		void PutChars(const char* pch, size_t vLen);

	private:
		std::shared_ptr<char>	mqBuf;
		size_t					mBufLen;
		size_t					mCurOffset;
	};
};

#endif


