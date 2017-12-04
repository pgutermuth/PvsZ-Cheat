#include "CCheat.h"

#include "Offsets.h"

#include "CPatch.h"

#include <Psapi.h>

void CCheat::patchMoneyAdd() {

	DWORD dwPatch = this->pProcess->base + Offsets::add_opcode_offset + 1 * sizeof( byte ); // game + 1F4D0 - 01 80 78550000

	if ( !g_pPatch->PatchByte( 0x80, dwPatch ) ) { exit( 0x1 ); }

}

void CCheat::patchMoneyMove() {

	DWORD dwPatch = this->pProcess->base + Offsets::move_opcode_offset + 1 * sizeof( byte ); // game + 1F636 - 89 BF 78550000  

	if ( !g_pPatch->PatchByte( 0xBF, dwPatch ) ) { exit( 0x2 ); }

}

void CCheat::patchMoneyMaximum() {

	DWORD dwPatch = this->pProcess->base + Offsets::cmp_opcode_offset + 2 * sizeof( byte ); // game + 1F4DF - 81 F9 06270000       

	if ( !g_pPatch->PatchByte( 0x17BD, dwPatch ) ) { exit( 0x3 ); }


	dwPatch = this->pProcess->base + Offsets::cmp2_opcode_offset + 6 * sizeof( byte ); // game + 1F4E7 - C7 80 78550000 01000000

	if ( !g_pPatch->PatchByte( 0x17BD, dwPatch ) ) { exit( 0x4 ); }

}

void CCheat::patchShopMoney() {

	DWORD dwPatch = this->pProcess->base + Offsets::sub_opcode_offset; // game + 9B62A - sub [ecx+54],eax      

	if ( !g_pPatch->PatchByte( 0x01, dwPatch ) ) { exit( 0x5 ); }

}

void CCheat::patchMoneyValueByDrop() {

	DWORD dwPatch = this->pProcess->base + Offsets::add2_opcode_offset + 1 * sizeof( byte ); // game + 3478C - add [eax+54],ecx     

	if ( !g_pPatch->PatchByte( 0x40, dwPatch ) ) { exit( 0x6 ); }

}

void CCheat::patchPlantCooldown() {

	DWORD dwPatch = this->pProcess->base + Offsets::move2_opcode_offset + 2 * sizeof( byte ); // game + 958BF - mov eax,[edi+04]

	if ( !g_pPatch->PatchByte( 0x04, dwPatch ) ) { exit( 0x7 ); }

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

	/*------------------------------------------------------------------
	|				Waiting until the base address was found		   */

	while ( !g_pCheat->loadDllInfo() ) { Sleep( 1 ); }

	/*------------------------------------------------------------------*/


	/*--------------------------------------------------------------------
	|							Patching the game						*/

	g_pCheat->patchMoneyMaximum();

	g_pCheat->patchMoneyAdd();

	g_pCheat->patchMoneyMove();

	g_pCheat->patchShopMoney();

	g_pCheat->patchMoneyValueByDrop();

	g_pCheat->patchPlantCooldown();

	/*--------------------------------------------------------------------*/


	HWND hWnd = FindWindowA( 0, "Plants vs. Zombies" ); // Dirty workaround here but I think it is okay to use that in this specific case.
	if ( !hWnd ) { exit( 0x8 ); }

	if ( SetWindowTextA( hWnd, "Plants vs. Zombies - patched" ) == 0 ) { exit( 0x9 ); }

	return;

}

DllInfo* CCheat::pProcess = new DllInfo;

CCheat* g_pCheat = new CCheat();
