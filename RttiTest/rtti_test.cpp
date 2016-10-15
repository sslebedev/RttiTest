#include "rtti_test.h"

#if defined(COMPILE_CHECK)

const char *DoStaticDowncast(A *ptr)
{
	auto pb = static_cast<B *>(ptr);
	return pb != nullptr ? pb->foo() : "null"; // Works everywhere
}

const char *DoDynamicDowncast(A *ptr)
{
	auto pb = dynamic_cast<B *>(ptr);
	return pb != nullptr ? pb->foo() : "null"; // Works only with rtti (downcast)
}

const char *DoUpcast(B *ptr)
{
	return dynamic_cast<A *>(ptr)->foo(); // Works everywhere (upcast)
}

#else

const char *DoCast(A *ptr)
{
#if defined(PERFORMANCE_DYNAMIC)
	auto pb = dynamic_cast<B *>(ptr);
	return pb != nullptr ? pb->foo() : "null"; // Works only with rtti (downcast)
#else
	auto pb = static_cast<B *>(ptr);
	return pb != nullptr ? pb->foo() : "null"; // Works everywhere
#endif
}

#endif