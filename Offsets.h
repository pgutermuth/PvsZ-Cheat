#pragma once

#include <Windows.h>

#include <cstdint>

namespace Offsets {

	constexpr std::uintptr_t add_opcode_offset  = 0x1F4D0;	// popcapgame1.exe + 1F4D0    - 01 80 78550000				- add [eax+00005578],eax

	constexpr std::uintptr_t move_opcode_offset = 0x1F636;	// popcapgame1.exe + 1F636    - 89 BF 78550000				- mov [edi+00005578],edi

	constexpr std::uintptr_t cmp_opcode_offset  = 0x1F4DF;   // popcapgame1.exe + 1F4DF   - 81 F9 06270000				- cmp ecx,00002706 { 9990 }

	constexpr std::uintptr_t cmp2_opcode_offset = 0x1F4E7;   // popcapgame1.exe + 1F4E7   - C7 80 78550000 06270000		- mov [eax+00005578],00002706 { 9990 }

}