#ifndef __nifty_h__
#define __nifty_h__

#include <new>
#include <type_traits>

//
//	define used in a .h file to declare a global static variable whose construction and
//	destruction or is controlled by a nifty reference counter
//
//	vClass	is the class of the variable
//	vVar	is the name of the variable
//
//	Example of use:
//
//	namespace myNameSpace
//	{
//		class CMyClass
//		{
//		public:
//			void SayHello();
//		};
//		NIFTY_DCL(CMyClass, gMyGlobal)
//	}
//
#define NIFTY_DCL( vClass, vVar )			\
	extern vClass&			vVar;			\
	static struct C##vVar##_Initializer		\
	{										\
		C##vVar##_Initializer();			\
		~C##vVar##_Initializer();			\
	} vVar##_Initializer;				


//
//	define used in a .cpp file to construct a global object before its first use
//	and destruct it after all other static objects that use it are destructed
//
//	vNameSpace		is the namespace of the object's class
//	vClass			is the class of the object
//	vVar			is the variable name of the object
//	...				are the params to the ctor
//
#define NIFTY_IMPL( vNameSpace, vClass, vVar, ... )								\
	static int vNameSpace##_##vVar##_nifty_counter;								\
	static typename std::aligned_storage<sizeof(vNameSpace::vClass),			\
		alignof(vNameSpace::vClass)>::type vNameSpace##_##vVar##_buf;			\
	vNameSpace::vClass& vNameSpace::vVar =										\
		reinterpret_cast<vNameSpace::vClass&>(vNameSpace##_##vVar##_buf);		\
	vNameSpace::C##vVar##_Initializer::C##vVar##_Initializer()					\
	{																			\
		if (vNameSpace##_##vVar##_nifty_counter++ == 0)							\
			new (&vVar) vClass( __VA_ARGS__ );									\
	}																			\
	vNameSpace::C##vVar##_Initializer::~C##vVar##_Initializer()					\
	{																			\
		if (--vNameSpace##_##vVar##_nifty_counter == 0)							\
			(&vVar)->~vClass();													\
	}

//
//	This define is similar to NIFTY_DCL, except that it is used for declaring a 
//	a static class member.
//
//	vClass		is the class of the static variable being declared
//	vVar		is the name of the variable
//
//	Assumes vVar is declared as follows:
//		static vClass& vVar;
//
#define NIFTY_STATIC_DCL( vEncClass, vClass, vVar )		\
	friend struct vEncClass##_##vVar##_Initializer;		\
	static vClass& vVar;

//
//	This define is similar to NIFTY_DCL, except that it is used for declaring a 
//	a static class member.
//
//	vEncClass		is the class of the static variable being declared
//	vVar		is the name of the variable
//
//	Assumes vVar is declared as follows:
//		static vClass& vVar;
//
#define NIFTY_STATIC_INIT_DCL( vEncClass, vVar )		\
	static struct vEncClass##_##vVar##_Initializer		\
	{													\
		vEncClass##_##vVar##_Initializer();				\
		~vEncClass##_##vVar##_Initializer();			\
	} vEncClass##vVar##_Initializer;

//
//	define used in a .cpp file to construct a global object before its first use
//	and destruct it after all other static objects that use it are destructed
//
//	vNs				is the namespace of the vVar's class
//	vClass			is the class of vVar 
//  vEncNs			is the namespace of the class that vVar is a member of
//	vEncClass		is the class that vVar is a member of
//	vVar			is the member name of the static variable
//	...				are the params to the ctor, enclosed in parens
//
#define NIFTY_STATIC_IMPL( vNs, vClass, vEncNs, vEncClass, vVar, ... )				\
	static int vEncNs##_##vEncClass##_##vVar##_nifty_counter;						\
	static typename std::aligned_storage<sizeof(vNs::vClass),						\
		alignof(vNs::vClass)>::type	vEncNs##_##vEncClass##_##vVar##_buf;			\
	vNs::vClass& vEncNs::vEncClass::vVar =											\
		reinterpret_cast<vNs::vClass&>(												\
			vEncNs##_##vEncClass##_##vVar##_buf );									\
	vEncNs::vEncClass##_##vVar##_Initializer::vEncClass##_##vVar##_Initializer()	\
	{																				\
		if (vEncNs##_##vEncClass##_##vVar##_nifty_counter++ == 0)					\
			new(&vEncNs##_##vEncClass##_##vVar##_buf)vNs::vClass(__VA_ARGS__);		\
	}																				\
	vEncNs::vEncClass##_##vVar##_Initializer::~vEncClass##_##vVar##_Initializer()	\
	{																				\
		if (vEncNs##_##vEncClass##_##vVar##_nifty_counter-- == 0)					\
			(&vEncClass::vVar)->~vClass();											\
	}
#endif
