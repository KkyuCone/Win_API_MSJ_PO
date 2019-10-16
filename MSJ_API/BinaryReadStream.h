#pragma once
#include "FileStream.h"

class BinaryReadStream : protected FileStream
{
public:
	void Binary_Read(void* _Buffer, int _ByteSize, int _ReadByteSize);

	void Binary_Seek(long _Size, int _Mode = SEEK_SET);

public:
	BinaryReadStream(const wchar_t* _Path);
	~BinaryReadStream();
};

