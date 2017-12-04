#pragma once

#include <Windows.h>

#include <cstdint>

struct DllInfo {

	std::uintptr_t base = 0, size = 0;
};

class CCheat {
	
public:

	void patchMoneyAdd();

	void patchMoneyMove();

	void patchMoneyMaximum();

	void patchShopMoney();

	void patchMoneyValueByDrop();

	void patchPlantCooldown();

	bool loadDllInfo();

	static DllInfo* pProcess;

	static void Action();
};

extern CCheat* g_pCheat;
