#include <iostream>
//#include <Psapi.h>

#include "rtti_test.h"

int main()
{
	auto pTest = new B();
#if defined(COMPILE_CHECK)
	auto res = DoDynamicDowncast(pTest);
#else
	auto res = DoCast(pTest);
#endif
	std::cout << res << std::endl;
	//PROCESS_MEMORY_COUNTERS pmc;
	//GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	delete (pTest);

	return 0;
}