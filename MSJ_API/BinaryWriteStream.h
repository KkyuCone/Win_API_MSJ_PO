#pragma once
#include "FileStream.h"

class BinaryWriteStream : protected FileStream
{
public:
	void Binary_Wirte(void* _Buffer, int _ByteSize);
public:
	BinaryWriteStream(const wchar_t* _Path);
	~BinaryWriteStream();
};

