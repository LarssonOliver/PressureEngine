#pragma once

#include <unordered_map>
#include <string>
#include "../DllExport.h"

namespace Pressure {

	class PRESSURE_API Properties {

	private: 
		static const std::unordered_map<std::string, std::string> s_Defaults;
		std::unordered_map<std::string, std::string> m_Properties;

	public:
		static std::string get(const char* property);
		// This does not write properties to the property file.
		static void set(const char* property, const char* value);

	protected:
		static Properties* Inst();
		virtual ~Properties();

		Properties();
		Properties(const Properties& p) = delete;
		Properties& operator=(const Properties& p) = delete;

		static Properties* m_Inst;
		bool loadFromFile();
		bool createFileWithDefaults();

	};

}
