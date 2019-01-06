#pragma once

// Plan is to convert this system to use an in engine console when support for text redering is implemented.

#include <iostream>
#include <ctime>
#include <string>

#include "DllExport.h"

namespace Pressure {

	enum PRESSURE_API LogLevel : unsigned char {
		LOG_FATAL,
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG
	};

	constexpr PRESSURE_API std::ostream& operator<<(std::ostream& os, const LogLevel level) {
		switch (level) {
		case LOG_FATAL:
			os << "FATAL";
			break;
		case LOG_ERROR:
			os << "ERROR";
			break;
		case LOG_WARNING:
			os << "WARNING";
			break;
		case LOG_INFO:
			os << "INFO";
			break;
		case LOG_DEBUG:
			os << "DEBUG";
			break;
		}
		return os;
	}

    class PRESSURE_API Log {

	protected:
		std::ostream& m_os;

	public:
		Log() : m_os(std::cout) { }
		static LogLevel& ReportingLevel() { 
			static LogLevel logLevel = LOG_INFO;
			return logLevel;
		}

		std::ostream& Get(LogLevel level = LOG_INFO) {
            std::time_t timeStamp = std::time(nullptr);
			std::tm time;
            localtime_s(&time, &timeStamp);
			m_os << ">[" << (time.tm_hour < 10 ? "0" : "") << time.tm_hour;
			m_os << ":"  << (time.tm_min < 10 ? "0" : "") << time.tm_min;
			m_os << ":"  << (time.tm_sec < 10 ? "0" : "") << time.tm_sec;

			m_os << "] [" << level << "]: ";
			return m_os;
		}

	private:
		Log(const Log&) = delete;
		Log& operator=(const Log&) = delete;

	};

}
#ifdef PRESSURE_DEBUG
	#define PRESSURE_LOGGING // Used to determine whether or not we should enable logging.
	
	#define PRESSURE_LOG(lvl, msg) \
		if (lvl > Log::ReportingLevel()); \
		else Log().Get(lvl) << msg << std::endl
	
	#define PRESSURE_ASSERT(x, msg) { if(!(x)) { PRESSURE_LOG(LOG_ERROR, std::string("Assertion Failed: ") + msg); __debugbreak(); } }
#else
	#define PRESSURE_LOG(lvl, msg)
	#define PRESSURE_ASSERT(x, msg)
#endif