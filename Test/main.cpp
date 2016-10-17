#include <iostream>
#include <windows.h>
#include <psapi.h>

#include "rtti_test.h"

template<int i>
class Bi : public A
{
public:
	virtual const char *foo()
	{
		return i % 2 == 0 ? "B0" : "B1";
	}

	virtual ~Bi()
	{}
};

const int GeneratorMaxIter = 1000;

template<int i>
class Generator
{
public :
	static_assert(i > 0, "i > 0");
	static_assert(i <= GeneratorMaxIter, "i <= maxIter");

	static void Fill(A **arr)
	{
		arr[i - 1] = new Bi<i - 1>();
		Generator<i - 1>::Fill(arr);
	}

	static void Clear(A **arr)
	{
		delete (arr[i - 1]);
		Generator<i - 1>::Clear(arr);
	}
};

template<>
class Generator<1>
{
public :
	static void Fill(A **arr)
	{
		arr[0] = new B();
	}

	static void Clear(A **arr)
	{
		delete (arr[0]);
	}
};

template<>
class Generator<0>
{
public :
	static void Fill(A **arr)
	{}

	static void Clear(A **arr)
	{}
};

int GetCurrentMemory();
void FillArray(const int iterations, A **pTest);
void DoSomeCasts(const int iterations, A **pTest);
void ClearArray(const int iterations, A **pTest);

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
	auto pTest = new A *[iterations];

	QueryPerformanceCounter(&counterBegin);
	FillArray(iterations, pTest);
	QueryPerformanceCounter(&counterEnd);
	counterTotalAlloc.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	// Cast
	QueryPerformanceCounter(&counterBegin);
	DoSomeCasts(iterations, pTest);
	QueryPerformanceCounter(&counterEnd);
	counterTotalCast.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	// Space
	auto space = GetCurrentMemory();

	// Free
	QueryPerformanceCounter(&counterBegin);
	ClearArray(iterations, pTest);
    QueryPerformanceCounter(&counterEnd);
	counterTotalAlloc.QuadPart = counterEnd.QuadPart - counterBegin.QuadPart;

	delete[](pTest);

	// Log result

	std::cout << std::endl;
	std::cout << "Memory: " << space << std::endl;
	std::cout << "Alloc: " << (double) counterTotalAlloc.QuadPart / frequency.QuadPart << std::endl;
	std::cout << "Cast: " << (double) counterTotalCast.QuadPart / frequency.QuadPart << std::endl;
	std::cout << "Free: " << (double) counterTotalFree.QuadPart / frequency.QuadPart << std::endl;

	return 0;
}

void ClearArray(const int iterations, A **pTest)
{
#ifdef MULTY_TYPE
	for (int i = 0; i < genIterations; ++i) {
		Generator<mi>::Clear(pTest + mi * i);
	}
	if (ri > 0) {
		Generator<ri>::Clear(pTest + mi * genIterations);
	}
#else
	for (int i = 0; i < iterations; ++i) {
		delete(pTest[i]);
	}
#endif

}

void DoSomeCasts(const int iterations, A **pTest)
{
	for (int i = 0; i < iterations; ++i) {
#if defined(COMPILE_CHECK)
		DoDynamicDowncast(pTest[i]);
#else
		DoCast(pTest[i]);
		//std::cout<<pTest[i]->foo();
#endif
	}
}

void FillArray(const int iterations, A **pTest)
{
#ifdef MULTY_TYPE
	const int mi = GeneratorMaxIter;
	const int genIterations = iterations / mi;
	for (int i = 0; i < genIterations; ++i) {
		Generator<mi>::Fill(pTest + mi * i);
	}
	const int ri = iterations % mi;
	if (ri > 0) {
		Generator<ri>::Fill(pTest + mi * genIterations);
	}

#else
	for (int i = 0; i < iterations; ++i) {
		pTest[i] = new B();
	}
#endif

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