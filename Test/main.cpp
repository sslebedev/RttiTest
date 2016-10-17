#include <iostream>
#include <windows.h>
#include <psapi.h>

#include "rtti_test.h"

int GetCurrentMemory();

int main()
{
	LARGE_INTEGER frequency,
			counterTotalAlloc,
			counterTotalCast,
			counterTotalFree,
			counterBegin,
			counterEnd;

	const int iterations = 10000000;
	QueryPerformanceFrequency(&frequency);

	// Allocation
	QueryPerformanceCounter(&counterBegin);

	auto pTest = new B[iterations]();

	QueryPerformanceCounter(&counterEnd);
	counterTotalAlloc.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	// Cast
	QueryPerformanceCounter(&counterBegin);

	for (int i = 0; i < iterations; ++i) {
#if defined(COMPILE_CHECK)
		DoDynamicDowncast(&pTest[i]);
#else
		DoCast(&pTest[i]);
#endif
	}

	QueryPerformanceCounter(&counterEnd);
	counterTotalCast.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	// Space
	auto space = GetCurrentMemory();

	// Free
	QueryPerformanceCounter(&counterBegin);

	delete[] (pTest);

	QueryPerformanceCounter(&counterEnd);
	counterTotalAlloc.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	std::cout << "Memory: " << space << std::endl;
	std::cout << "Alloc: " <<  counterTotalAlloc.QuadPart / frequency.QuadPart << std::endl;
	std::cout << "Cast: " << (double)counterTotalCast.QuadPart / frequency.QuadPart << std::endl;
	std::cout << "Free: " << (double)counterTotalFree.QuadPart / frequency.QuadPart << std::endl;

	return 0;
}

int GetCurrentMemory()
{
	PROCESS_MEMORY_COUNTERS pmc;

	auto proc = GetCurrentProcess();
	auto isOk = GetProcessMemoryInfo(proc, &pmc, sizeof(pmc));
	if (!isOk) {
		return -1;
	}
	return pmc.WorkingSetSize;
}