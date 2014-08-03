#ifndef HEADER_ZN_CONFIG_HPP_INCLUDED
#define HEADER_ZN_CONFIG_HPP_INCLUDED

//
// This header defines global build configuration for the whole framework.
// Note: these #defines can either be active here or in your build commands.
//

// Enables debug code (additionnal checks and messages, may decrease performance)
#define ZN_DEBUG

// Hint to ease SFML integration
// TODO use SFML_API instead?
//#ifdef SFML_API
	#define ZN_SFML
//#endif

// DLL options
#ifdef ZN_DLL
	// This is placed before each element we want to expose to the user of the DLL.
	// (Header-only definitions don't need that)
	#define ZN_API __declspec(dllexport)
#else
	// Not creating a DLL: empty macro
	#define ZN_API
#endif

// C++11 features
#ifdef _MSC_VER
	#define ZN_NOEXCEPT _NOEXCEPT
#else
	#define ZN_NOEXCEPT noexcept
#endif

#endif // HEADER_ZN_CONFIG_HPP_INCLUDED

