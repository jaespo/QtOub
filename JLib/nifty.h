#ifndef __NIFTY_H__
#define __NIFTY_H__

#include <new>
#include <type_traits>

//
//	define used in a .h file to declare a global static variable whose construction and
//	destruction or is controlled by a nifty reference counter
//
//	vClass	is the class of the variable
//	vVar	is the name of the variable
//
#define NIFTY_DCL( vClass, vVar )			\
	extern vClass&			vVar;			\
	static struct C##vVar##_Initializer		\
	{										\
		C##vVar##_Initializer();			\
		~C##vVar##_Initializer();			\
	} ##vVar##_Initializer;				

//
//	define used in a .cpp file to construct a global object before its first use
//	and destruct it after all other static objects that use it are destructed
//
//	vNameSpace		is the namespace of the object's class
//	vClass			is the class of the object
//	vVar			is the variable name of the object
//
#define NIFTY_IMPL( vNameSpace, vClass, vVar )									\
	static int vNameSpace##_##vVar##_nifty_counter;								\
	static typename std::aligned_storage<sizeof(vNameSpace##::##vClass),		\
		alignof(vNameSpace##::##vClass)>::type vNameSpace##_##vVar##_buf;		\
	vNameSpace::vClass& vNameSpace##::##vVar =									\
		reinterpret_cast<vNameSpace##::##vClass&>(vNameSpace##_##vVar##_buf);	\
	vNameSpace##::C##vVar##_Initializer::C##vVar##_Initializer()				\
	{																			\
		if (vNameSpace##_##vVar##_nifty_counter++ == 0)							\
			new (&vNameSpace##_##vVar##_buf) vClass();							\
	}																			\
	vNameSpace##::C##vVar##_Initializer::~C##vVar##_Initializer()				\
	{																			\
		if (--vNameSpace##_##vVar##_nifty_counter == 0)							\
			(&vVar)->~vClass();													\
	}
#endif
