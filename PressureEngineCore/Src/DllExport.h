#pragma once

#ifdef PRESSURE_EXPORTS  
	#define PRESSURE_API __declspec(dllexport)   
#else  
	#define PRESSURE_API __declspec(dllimport)		
#endif 