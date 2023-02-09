#include "CPatch.h"

#include <assert.h>

bool CPatch::PatchByte( const byte & newByte, const std::uintptr_t & Address ) {
	assert( Address != 0 );

	DWORD dwOldProtection{ 0 };

	if ( VirtualProtect( reinterpret_cast< LPVOID >( Address ), sizeof( byte ), PAGE_EXECUTE_READWRITE, &dwOldProtection ) == 0 ) { return false; }

	*(byte*)( Address ) = newByte;

	if ( VirtualProtect( reinterpret_cast< LPVOID >( Address ), sizeof( byte ), dwOldProtection, &dwOldProtection ) == 0 ) { return false; }

	return true;
}

CPatch* g_pPatch = new CPatch();
