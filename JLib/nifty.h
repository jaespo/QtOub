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

//
//	This define is similar to NIFTY_DCL, except that it is used for declaring a 
//	"global" that is static class member.
//
//	vClass	is the class of the variable
//	vVar	is the name of the variable
//
//	Example of use:
//
//	namespace myNameSpace1
//	{
//		class CMyClass1
//		{
//		public:
//			void SayHello();
//		private:
//			static CMyClass1		mgInst;
//		};
//		NIFTY_STATIC_DCL(CMyClass1, mgInst)
//	}
//
#define NIFTY_STATIC_DCL( vClass, vVar )		\
	static vClass	vVar;						\
	static struct C##vVar##_Initializer			\
	{											\
		C##vVar##_Initializer();				\
		~C##vVar##_Initializer();				\
	} vVar##_Initializer;			

//
//	define used in a .cpp file to construct a global object before its first use
//	and destruct it after all other static objects that use it are destructed
//
//	vNameSpace		is the namespace of the object's class
//	vClass			is the class vof the object
//	vVar			is the variable name of the object
//
#define NIFTY_STATIC_IMPL( vNameSpace, vClass, vVar )							\
	static int vNameSpace##_##vVar##_nifty_counter;								\
	static typename std::aligned_storage<sizeof(vNameSpace##::##vClass),		\
		alignof(vNameSpace##::##vClass)>::type									\
			vNameSpace##_##vClass##_##vVar##_buf;								\
	vNameSpace::vClass vNameSpace##::vClass##::##vVar =							\
		reinterpret_cast<vNameSpace##::##vClass&>(								\
			vNameSpace##_##vClass##_##vVar##_buf);								\
	vNameSpace##::vClass::C##vVar##_Initializer::C##vVar##_Initializer()		\
	{																			\
		if (vNameSpace##_##vVar##_nifty_counter++ == 0)							\
			new (&vNameSpace##_##vClass##_##vVar##_buf) vClass();				\
	}																			\
	vNameSpace##::vClass::C##vVar##_Initializer::~C##vVar##_Initializer()		\
	{																			\
		if (--vNameSpace##_##vVar##_nifty_counter == 0)							\
			(&vVar)->~vClass();													\
	}
#endif
