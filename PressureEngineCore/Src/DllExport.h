#pragma once

#if defined linux || defined __linux__ || defined __linux
	#define PRESSURE_PLAFORM_LINUX
	#define PRESSURE_PLATFORM_NAME "Linux"
#endif

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
	#define PRESSURE_PLATFORM_WIN32
	#define PRESSURE_PLATFORM_NAME "Windows"
#endif

#if ( defined __MWERKS__ && defined __powerc && !defined macintosh ) || defined __APPLE_CC__ || defined macosx
	#define PRESSURE_PLATFORM_MACOSX
	#define PRESSURE_PLATFORM_NAME "MacOS X"
#endif

#ifdef PRESSURE_PLATFORM_WIN32
	#ifdef PRESSURE_EXPORTS  
		#define PRESSURE_API __declspec(dllexport)   
	#else  
		#define PRESSURE_API __declspec(dllimport)		
	#endif
#else
	#error PressureEngine only supports Win32 for now!
	#ifdef PRESSURE_EXPORTS
		#define PRESSURE_API __attribute__((visibility("default")))	
	#else
		#define PRESSURE_API	
	#endif
#endif

#ifdef PRESSURE_PLATFORM_WIN32
	#pragma warning( disable : 4251 ) // This disables dll interface warnings for stl template classes.
#endif