#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "common.h"

#ifndef NO_RCT2

#ifdef __WINDOWS__
	#include <windows.h>
#else
	#include <sys/mman.h>
#endif // __WINDOWS__

#include "hook.h"
#include "platform/platform.h"

void* g_hooktableaddress = 0;
int g_hooktableoffset = 0;
int g_maxhooks = 1000;

// This macro writes a little-endian 4-byte long value into *data
// It is used to avoid type punning.
#define write_address_strictalias(data, addr) \
	*(data + 0) = ((addr) & 0x000000ff) >> 0; \
	*(data + 1) = ((addr) & 0x0000ff00) >> 8; \
	*(data + 2) = ((addr) & 0x00ff0000) >> 16; \
	*(data + 3) = ((addr) & 0xff000000) >> 24;

static void hookfunc(int address, int newaddress, int stacksize, int registerargs[], int registersreturned, int eaxDestinationRegister)
{
	int i = 0;
	char data[100];

	registersreturned |= eaxDestinationRegister;

	int registerssaved = 7;
	int n = registersreturned;
	for (; n; registerssaved--) {
		n &= n - 1;
	}
	int numrargs = 0;
	for (int j = 0; ; j++) {
		if (registerargs[j] != END) {
			numrargs++;
		} else {
			break;
		}
	}

	int rargssize = numrargs * 4;

	if (!(registersreturned & EAX)) {
		data[i++] = 0x50; // push eax
	}
	if (!(registersreturned & EBX)) {
		data[i++] = 0x53; // push ebx
	}
	if (!(registersreturned & ECX)) {
		data[i++] = 0x51; // push ecx
	}
	if (!(registersreturned & EDX)) {
		data[i++] = 0x52; // push edx
	}
	if (!(registersreturned & EBP)) {
		data[i++] = 0x55; // push ebp
	}
	if (!(registersreturned & ESI)) {
		data[i++] = 0x56; // push esi
	}
	if (!(registersreturned & EDI)) {
		data[i++] = 0x57; // push edi
	}

	data[i++] = 0x50; //push eax
	data[i++] = 0x89; //mov eax, esp
	data[i++] = 0xE0;
	data[i++] = 0x83; //sub eax, (0xC + numargs*4) & 0xF
	data[i++] = 0xE8;
	data[i++] = (0xC + numrargs * 4) & 0xF;
	data[i++] = 0x83; //and eax, 0xC
	data[i++] = 0xE0;
	data[i++] = 0x0C;
	data[i++] = 0xA3; //mov [0x9ABDA8], eax
	data[i++] = 0xA8;
	data[i++] = 0xBD;
	data[i++] = 0x9A;
	data[i++] = 0x00;
	data[i++] = 0x58; //pop eax
	data[i++] = 0x2B; //sub esp, [0x9ABDA8]
	data[i++] = 0x25;
	data[i++] = 0xA8;
	data[i++] = 0xBD;
	data[i++] = 0x9A;
	data[i++] = 0x00;

	// work out distance to nearest 0xC
	// (esp - numargs * 4) & 0xC
	// move to align - 4
	// save that amount

	if (numrargs > 0) {
		// push the registers to be on the stack to access as arguments
		for (signed int j = numrargs - 1; j >= 0; j--) {
			switch (registerargs[j]) {
				case EAX: data[i++] = 0x50; break;
				case EBX: data[i++] = 0x53; break;
				case ECX: data[i++] = 0x51; break;
				case EDX: data[i++] = 0x52; break;
				case ESI: data[i++] = 0x56; break;
				case EDI: data[i++] = 0x57; break;
				case EBP: data[i++] = 0x55; break;
			}
		}
	}

	data[i++] = 0xE8; // call

	write_address_strictalias(&data[i], newaddress - address - i - 4);
	i += 4;

	// returnlocation:

	switch (eaxDestinationRegister) {
	case EBX:
		// mov ebx, eax
		data[i++] = 0x8B;
		data[i++] = 0xD8;
		break;
	case ECX:
		// mov ecx, eax
		data[i++] = 0x8B;
		data[i++] = 0xC8;
		break;
	case EDX:
		// mov ecx, eax
		data[i++] = 0x8B;
		data[i++] = 0xD0;
		break;
	case ESI:
		// mov ecx, eax
		data[i++] = 0x8B;
		data[i++] = 0xF0;
		break;
	case EDI:
		// mov ecx, eax
		data[i++] = 0x8B;
		data[i++] = 0xF8;
		break;
	case EBP:
		// mov ecx, eax
		data[i++] = 0x8B;
		data[i++] = 0xE8;
		break;
	}

	data[i++] = 0x83; // sub esp, x
	data[i++] = 0xEC;
	data[i++] = (signed char)(stacksize * -4) - rargssize;

	data[i++] = 0x03; //add esp, [0x9ABDA8]
	data[i++] = 0x25;
	data[i++] = 0xA8;
	data[i++] = 0xBD;
	data[i++] = 0x9A;
	data[i++] = 0x00;

	if (!(registersreturned & EDI)) {
		data[i++] = 0x5F; // pop edi
	}
	if (!(registersreturned & ESI)) {
		data[i++] = 0x5E; // pop esi
	}
	if (!(registersreturned & EBP)) {
		data[i++] = 0x5D; // pop ebp
	}
	if (!(registersreturned & EDX)) {
		data[i++] = 0x5A; // pop edx
	}
	if (!(registersreturned & ECX)) {
		data[i++] = 0x59; // pop ecx
	}
	if (!(registersreturned & EBX)) {
		data[i++] = 0x5B; // pop ebx
	}
	if (!(registersreturned & EAX)) {
		data[i++] = 0x58; // pop eax
	}

	data[i++] = 0xC3; // retn

#ifdef __WINDOWS__
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)address, data, i, 0);
#else
	// We own the pages with PROT_WRITE | PROT_EXEC, we can simply just memcpy the data
	memcpy((void *)address, data, i);
#endif // __WINDOWS__
}

void addhook(int address, int newaddress, int stacksize, int registerargs[], int registersreturned, int eaxDestinationRegister)
{
	if (!g_hooktableaddress) {
		size_t size = g_maxhooks * 100;
#ifdef __WINDOWS__
		g_hooktableaddress = VirtualAllocEx(GetCurrentProcess(), NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
#else
		g_hooktableaddress = mmap(NULL, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (g_hooktableaddress == MAP_FAILED)
		{
			perror("mmap");
			exit(1);
		}
#endif // __WINDOWS__
	}
	if (g_hooktableoffset > g_maxhooks) {
		return;
	}
	unsigned int hookaddress = (unsigned int)g_hooktableaddress + (g_hooktableoffset * 100);
	char data[9];
	int i = 0;
	data[i++] = 0xE9; // jmp

	write_address_strictalias(&data[i], hookaddress - address - i - 4);
	i += 4;

	data[i++] = 0xC3; // retn
#ifdef __WINDOWS__
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)address, data, i, 0);
#else
	// We own the pages with PROT_WRITE | PROT_EXEC, we can simply just memcpy the data
	int err = mprotect((void *)0x401000, 0x8a4000 - 0x401000, PROT_READ | PROT_WRITE);
	if (err != 0)
	{
		perror("mprotect");
	}
	
	memcpy((void *)address, data, i);
	
	err = mprotect((void *)0x401000, 0x8a4000 - 0x401000, PROT_READ | PROT_EXEC);
	if (err != 0)
	{
		perror("mprotect");
	}
#endif // __WINDOWS__
	hookfunc(hookaddress, newaddress, stacksize, registerargs, registersreturned, eaxDestinationRegister);
	g_hooktableoffset++;
}

#endif
