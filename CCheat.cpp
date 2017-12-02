#include "CCheat.h"

#include "Offsets.h"

#include <Psapi.h>

void CCheat::patchMoneyAdd() {

	DWORD dwPatch = this->pProcess->base + Offsets::add_opcode_offset + 1 * sizeof( byte ); // game + 1F4D0 - 01 80 78550000

	DWORD dwOldProtection = 0x0;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), PAGE_EXECUTE_READWRITE, &dwOldProtection );

	*(byte*)( dwPatch ) = 0x80; 

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), dwOldProtection, &dwOldProtection );
}

void CCheat::patchMoneyMove() {

	DWORD dwPatch = this->pProcess->base + Offsets::move_opcode_offset + 1 * sizeof( byte ); // game + 1F636 - 89 BF 78550000  

	DWORD dwOldProtection = 0x0;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), PAGE_EXECUTE_READWRITE, &dwOldProtection );

	*(byte*)( dwPatch ) = 0xBF;      

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), dwOldProtection, &dwOldProtection );
}

void CCheat::patchMoneyMaximum() {

	DWORD dwPatch = this->pProcess->base + Offsets::cmp_opcode_offset + 2 * sizeof( byte ); // game + 1F4DF - 81 F9 06270000       

	DWORD dwOldProtection = 0x0;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), PAGE_EXECUTE_READWRITE, &dwOldProtection );

	*(byte*)( dwPatch ) = 0x17BD;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), dwOldProtection, &dwOldProtection );


	dwPatch = this->pProcess->base + Offsets::cmp2_opcode_offset + 6 * sizeof( byte ); // game + 1F4E7 - C7 80 78550000 01000000

	dwOldProtection = 0x0;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), PAGE_EXECUTE_READWRITE, &dwOldProtection );

	*(byte*)( dwPatch ) = 0x17BD;

	VirtualProtect( reinterpret_cast< LPVOID >( dwPatch ), sizeof( byte ), dwOldProtection, &dwOldProtection );
}

bool CCheat::loadDllInfo() {

	MODULEINFO mInfo;

	memset( &mInfo, 0, sizeof( MODULEINFO ) );

	HMODULE hTemp = GetModuleHandleA( 0 );
	if ( hTemp == NULL ) { return false; }

	if ( !GetModuleInformation( GetCurrentProcess(), hTemp, &mInfo, sizeof( MODULEINFO ) ) ) { return false; }

	this->pProcess->base = reinterpret_cast< uintptr_t >( mInfo.lpBaseOfDll );

	this->pProcess->size = static_cast< size_t >( mInfo.SizeOfImage );

	memset( &mInfo, 0, sizeof( mInfo ) );

	return true;
}

void CCheat::Action() {

	while ( !g_pCheat->loadDllInfo() ) { Sleep( 1 ); }

	g_pCheat->patchMoneyMaximum();

	g_pCheat->patchMoneyAdd();

	g_pCheat->patchMoneyMove();

	MessageBoxA( 0, "Patched everything! Have fun. :)", "Report", MB_OK );

	return;

}

DllInfo* CCheat::pProcess = new DllInfo;

CCheat* g_pCheat = new CCheat();