#pragma once

#include <Windows.h>
#include <cstdint>

class CPatch {
public:
	bool PatchByte( const byte &newByte, const std::uintptr_t &Address = 0 );
};

extern CPatch* g_pPatch;