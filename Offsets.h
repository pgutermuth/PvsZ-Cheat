#pragma once

#include <Windows.h>

#include <cstdint>

namespace Offsets {
	constexpr std::uintptr_t add_opcode_offset  = 0x1F4D0;	// popcapgame1.exe + 1F4D0    - 01 80 78550000				- add [eax+00005578],eax

	constexpr std::uintptr_t move_opcode_offset = 0x1F636;	// popcapgame1.exe + 1F636    - 89 BF 78550000				- mov [edi+00005578],edi

	constexpr std::uintptr_t cmp_opcode_offset  = 0x1F4DF;   // popcapgame1.exe + 1F4DF   - 81 F9 06270000				- cmp ecx,00002706 { 9990 }

	constexpr std::uintptr_t cmp2_opcode_offset = 0x1F4E7;   // popcapgame1.exe + 1F4E7   - C7 80 78550000 06270000		- mov [eax+00005578],00002706 { 9990 }
	
	constexpr std::uintptr_t sub_opcode_offset   = 0x9B62A;   // popcapgame1.exe + 9B62A   - 29 41 54						- sub [ecx+54],eax

	constexpr std::uintptr_t add2_opcode_offset  = 0x3478C;   // popcapgame1.exe + 3478C   - 01 48 54						- add [eax+54],ecx

	constexpr std::uintptr_t move2_opcode_offset = 0x958BF;   // popcapgame1.exe + 958BF   - 8B 47 24                       - mov eax,[edi+24]
}
