//
// Created by sslebedev on 15.10.2016.
//

#ifndef PROJECT_NAME_RTTI_TEST_H
#define PROJECT_NAME_RTTI_TEST_H

#include <string>

class A
{
public:
	virtual const char *foo()
	{ return "A"; }

	virtual ~A()
	{}
};

class B : public A
{
public:
	virtual const char *foo()
	{ return "B"; }

	virtual ~B()
	{}
};

#if defined(COMPILE_CHECK)

const char *DoStaticDowncast(A *ptr);

const char *DoDynamicDowncast(A *ptr);

#else

B * DoCast(A *ptr);

#endif

#endif //PROJECT_NAME_RTTI_TEST_H
