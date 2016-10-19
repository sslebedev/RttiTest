#include <typeinfo>
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

B *DoCast(A *ptr)
{
#if defined(PERFORMANCE_DYNAMIC)
	return dynamic_cast<B *>(ptr); // Works only with rtti (downcast)
#else
	return static_cast<B *>(ptr); // Works everywhere
#endif
}

#endif